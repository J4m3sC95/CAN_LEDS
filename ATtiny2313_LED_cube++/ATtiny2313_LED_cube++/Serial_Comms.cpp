/*
 * Serial_Comms.cpp
 *
 * Created: 25/10/2017 18:31:05
 *  Author: James
 */ 

#include "Serial_Comms.h"

/*
Relevant registers for SPI using USI:
USISR:
	USIOIF [bit 6] = counter overflow interrupt flag
	USICNT3..0 [bits 3 to 0] = counter
USICR:
	USIOIE [bit 6] = enable interrupt on counter overflow
	USIWM [bits 5 to 4] = wire mode = 01 for SPI
	USICS [bits 3 to 2] = clock source = 00 for software
	USICLK = 1 for software strobe
	USITC = toggle the clock line
	
Process:
	setup outputs
	write data to serial register
	reset counter to zero and clear interrupt flag
	16 clock pulses
	overflow happens here
	do whatever with outputs
	
SPI setup code:
	// set USCK to output
	bitset(DDRB, PB7);
	// set MOSI to output
	bitset(DDRB, PB6);
	//set chip select
	bitset(DDRA, PA0);
	// set usi to spi mode
	USICR = 1<<USIWM0;
	
*/

uint8_t spi(uint8_t input){	
	// write data to register
	USIDR = input;
	
	// reset interrupt flag
	USISR = (1 << USIOIF);
	
	// strobe clock
	while(!(USISR & (1 << USIOIF))){
		USICR = (1<< USIWM0) | (1 << USICS1) | (1 << USICLK) | (1 << USITC);
		_delay_us(2);
	}
	return USIDR;
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

//void MCP2515_rts(uint8_t buffer_number){
	//CHIP_ENABLE();
	//spi(RTS_INST | (1 << buffer_number));
	//CHIP_DISABLE();
//}

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
//void CAN_tx(canmsg input, uint8_t buffer_number){
	//uint8_t n, address;
	//uint8_t data[14];
	//if(input.IDE == 1){
		//data[0] = input.ID >> 21;
		//data[1] = (((input.ID >> 18) & 0x7) << 5) | ((input.ID >> 16) & 0x3) | (1 << 3);
		//data[2] = ((input.ID >> 8) & 0xFF);
		//data[3] = input.ID & 0xFF;
	//}
	//else if(input.IDE == 0){
		//data[0] = (input.ID >> 3) & 0xFF;
		//data[1] = (input.ID & 0x7) << 5;
		//data[2] = 0;
		//data[3] = 0;
	//}
	//
	//data[4] = (input.RTR << 6) | input.DLC;
	//
	//for(n = 5; n < 14; n++){
		//data[n] = input.data[n-5];
	//}
	//
	//address = ((buffer_number + 3) << 4) | 1;
	//
	//MCP2515_write(address, data, 13);
	//
	//MCP2515_rts(buffer_number);
	//
	//// wait while message sends
	//while(!(MCP2515_status() & 8));
	//// clear interrupt flag
	//do{
		//MCP2515_bitmod(0x2C, 0x04, 0x00);
	//}while(MCP2515_status() & 8);
//}

/*
Receiving messages
- 2 receive buffers
- sets RXnIF flag when there is data in the buffer
- can set priority for receiving messages
- can set filters for messages
*/

//void CAN_rx(canmsg output, uint8_t buffer_number){
	//uint8_t address, n;
	//uint32_t temp;
	//uint8_t data[14];
	//
	//// wait for reading of message
	//while(!(MCP2515_status() & 1));
	//
	//address = (6 + buffer_number) << 4;
	//MCP2515_read( address, data, 14);
	//
	//output.IDE = (data[2] & 8) >> 3;
	//if(output.IDE == 1){
		//output.RTR = (data[5] & 0x40) >> 6;
		//temp = data[1];
		//output.ID = (temp << 21);
		//temp = data[2];
		//output.ID |= ((temp & 0xE0) << 13) | ((temp & 2) << 16);
		//temp = data[3];
		//output.ID |= (data[3] << 8) | (data[4]);
	//}
	//else if(output.IDE == 0){
		//output.RTR = (data[2] & 0x10) >> 4;
	//}
	//output.DLC = data[5] & 7;
	//
	//for(n = 6; n < 15; n++){
		//output.data[n-6] = data[n];
	//}
	//// clear read flag
	//do{
		//MCP2515_bitmod(0x2C, 0x01, 0x00);
	//}while(MCP2515_status() & 1);
//}


//// lightweight function to help fit on the 2313 this doesn't really work...
//uint8_t MCP2515_rw(uint8_t op, uint8_t address, uint8_t *data, uint8_t count){
	//uint8_t n, m, p;
	//CHIP_ENABLE();
	//spi(op);
	//m = spi(address);
	//for(n = 0; n < count; n++){
		//// does this line actually work?
		//p = spi(data[n]);
		//data[n] = p;
	//}
	//CHIP_DISABLE();
	//return m;
//}

void CAN_rx_light(uint8_t *output){
	// read 8 bytes of data
	MCP2515_read(0x66, output, 8);
	
	// clear read flag
	do{
		MCP2515_bitmod(0x2C, 0x01, 0x00);
	}while(!bittest(PINA, PA1));
}

// setup function

// config values (CNF3, CNF2, CNF1, CANINTE)
uint8_t config[4] = {0b00000010, 0b11001001, 0x00, 0x01};
// operation mode 0x40 = loopback, 0x00 = normal
//uint8_t mode = 0x40;
uint8_t mode = 0x00;

// only accept ID 0x7FF
uint8_t mask[3] = {0xFF,0xE0};
//uint8_t filter[3] = {0xFF,0xE0};

void MCP2515_setup(){	
	MCP2515_reset();
	// delay to wait for reset
	_delay_us(100);
	
	// set config for 500k
	MCP2515_write(0x28, config, 4);
	//write to acceptance mask RXM0 address 0x20 to 0x21
	MCP2515_write(0x20, mask, 2);
	//write to Acceptance filter RXF0 address 0x00 to 0x01
	MCP2515_write(0x00, mask, 2);
	// set the mode
	MCP2515_write(0x0F, &mode, 1);
}