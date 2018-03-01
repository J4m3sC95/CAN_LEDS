/*
 * CAN.cpp
 *
 * Created: 22/02/2018 15:15:22
 *  Author: James
 */ 

#include "CAN.h"

// config values (CNF3, CNF2. CNF1)
uint8_t config[4] = {0b00000010, 0b11001001, 0x00};
// operation mode 0x40 = loopback
//uint8_t mode = 0x40;
uint8_t mode = 0x00;
uint8_t filters_off = 0x60;

// top level functions
void CAN_setup(){
	
#ifdef ARDUINO
	pinMode(SS_PIN, OUTPUT);
	CHIP_DISABLE();

	SPI.begin();
#endif
 
  MCP2515_reset();
  delayMicroseconds(20);

  // set config for 500k
  MCP2515_write(0x28, config, 3);   
  // put into loopback mode
  MCP2515_write(0x0F, &mode, 1);
  // turn off receive mask/filters
  MCP2515_write(0x60, &filters_off, 1);

  delay(2000);
}

void led_cube(uint8_t instruction, uint16_t arg1, uint8_t arg2, uint16_t *buffer){
  uint8_t n;
  canmsg test;

  test.ID = 0x7FF;
  test.DLC = 8;
  test.IDE = 0;
  test.RTR = 0;
  
  test.data[0] = instruction;
  if(instruction == LOOP){
    test.data[2] = arg1;
    test.data[3] = arg2;
  }
  else if(instruction == DELAY){
    test.data[2] = (arg1 & 0xFF00) >> 8;
    test.data[3] = arg1 & 0xFF;
  }
  else{
    test.data[1] = arg1 | ((arg2 + 1) << 4);

    for(n = 0; n < 3; n++){
      test.data[(n << 1) + 3] = buffer[n] & 0xFF;
      test.data[(n << 1) + 2] = (buffer[n] & 0xFF00) >> 8;
    }
  }

  CAN_tx(test,0);
}

/*
Sending CAN message
- 3 transmit buffers of 14 bytes:
  - first byte is control byte
  - 5 bytes for ID and other arbitration info
  - final 8 bytes = data
  - TXREQ bit must be clear before writing to the buffer (not transmitting)
  - transmission is initiated by setting TXREQ bit or by sending the rts spi command
  - once sent the TXREQ bit is cleared and the TXnIF is set
  - transmission can be aborted by clearing the TXREQ bit
  - can set priority for sending messages
*/

// send can message from buffer #buffer_number
void CAN_tx(canmsg input, uint8_t buffer_number){
  uint8_t n, address;
  uint8_t data[14];
  if(input.IDE == 1){
    data[0] = input.ID >> 21;
    data[1] = (((input.ID >> 18) & 0x7) << 5) | ((input.ID >> 16) & 0x3) | (1 << 3);
    data[2] = ((input.ID >> 8) & 0xFF);
    data[3] = input.ID & 0xFF;
  }
  else if(input.IDE == 0){
    data[0] = (input.ID >> 3) & 0xFF;
    data[1] = (input.ID & 0x7) << 5;
    data[2] = 0;
    data[3] = 0;
  }
  
  data[4] = (input.RTR << 6) | input.DLC;
  
  for(n = 5; n < 14; n++){
    data[n] = input.data[n-5];
  }
  
  address = ((buffer_number + 3) << 4) | 1;
  
  MCP2515_write(address, data, 13);
  
  MCP2515_rts(buffer_number);
  
  // wait while message sends
  while(!(MCP2515_status() & 8));
  // clear interrupt flag
  do{
    MCP2515_bitmod(0x2C, 0x04, 0x00);
  }while(MCP2515_status() & 8);
}

/*
Receiving messages
- 2 receive buffers
- sets RXnIF flag when there is data in the buffer
- can set priority for receiving messages
- can set filters for messages
*/

void CAN_rx(canmsg output, uint8_t buffer_number){
  uint8_t address, n;
  uint32_t temp;
  uint8_t data[14];
  
  // wait for reading of message
  while(!(MCP2515_status() & 1));
  
  address = (6 + buffer_number) << 4;
  MCP2515_read(address, data, 14);
  
  output.IDE = (data[2] & 8) >> 3;
  if(output.IDE == 1){
    output.RTR = (data[5] & 0x40) >> 6;
    temp = data[1];
    output.ID = (temp << 21);
    temp = data[2];
    output.ID |= ((temp & 0xE0) << 13) | ((temp & 2) << 16);
    temp = data[3];
    output.ID |= (data[3] << 8) | (data[4]);
  }
  else if(output.IDE == 0){
    output.RTR = (data[2] & 0x10) >> 4;
  }
  output.DLC = data[5] & 7;
  
  for(n = 6; n < 15; n++){
    output.data[n-6] = data[n];
  }
  // clear read flag
  do{
    MCP2515_bitmod(0x2C, 0x01, 0x00);
  }while(MCP2515_status() & 1);
}


/*
MCP2515 SPI Interface
- do not try comms before 128 clock cycles have passed (16us)
- first byte after CS is lowered = instruction/command byte
- comms format: CS low, instruction, address, data
- comms types:
  - reset - recommended at start-up
  - read - instruction, address then data, reads endlessly until CS Raised
  - write = same as read but writing data
  - read status = read 8 bits of status (over and over if clock continues)
  - rx status
  - bit modify = command, address, mask, data
*/

// maybe make functions for ease of use
void MCP2515_reset(){
  CHIP_ENABLE();
  spi(RST_INST);
  CHIP_DISABLE();
}

void MCP2515_write(uint8_t address, uint8_t *data, uint8_t count){
  uint8_t n;
  CHIP_ENABLE();
  spi(WRITE_INST);
  spi(address);
  for(n = 0; n < count; n++){
    spi(data[n]);
  }
  CHIP_DISABLE();
}

void MCP2515_read(uint8_t address, uint8_t *data, uint8_t count){
  uint8_t n;
  CHIP_ENABLE();
  spi(READ_INST);
  spi(address);
  for(n = 0; n < count; n++){
    data[n] = spi(0x00);
  }
  CHIP_DISABLE();
}

void MCP2515_rts(uint8_t buffer_number){
  CHIP_ENABLE();
  spi(RTS_INST | (1 << buffer_number));
  CHIP_DISABLE();
}

uint8_t MCP2515_status(){
  uint8_t status;
  CHIP_ENABLE();
  spi(READ_STATUS);
  status = spi(0);
  CHIP_DISABLE();
  return status;
}

void MCP2515_bitmod(uint8_t address, uint8_t mask, uint8_t data){
  CHIP_ENABLE();
  spi(BIT_MODIFY);
  spi(address);
  spi(mask);
  spi(data);
  CHIP_DISABLE();
}

