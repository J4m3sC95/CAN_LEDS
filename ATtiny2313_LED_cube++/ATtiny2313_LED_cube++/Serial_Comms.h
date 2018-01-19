/*
 * Serial_Comms.h
 *
 * Created: 25/10/2017 19:35:48
 *  Author: James
 */ 


#ifndef SERIAL_COMMS_H_
#define SERIAL_COMMS_H_

#include "main.h"

// macros to make life easy
#define CHIP_ENABLE() bitclear(PORTA, PA0)
#define CHIP_DISABLE() bitset(PORTA, PA0)

// can message struct
struct canmsg{
	uint32_t ID;
	uint8_t IDE;
	uint8_t RTR;
	uint8_t DLC;
	uint8_t data[9];
};

// function decelerations
uint8_t spi(uint8_t input);
void MCP2515_write(uint8_t address, uint8_t *data, uint8_t count);
void MCP2515_read(uint8_t address, uint8_t *data, uint8_t count);
void MCP2515_reset();
//void MCP2515_rts(uint8_t buffer_number);
void MCP2515_bitmod(uint8_t address, uint8_t mask, uint8_t data);
uint8_t MCP2515_status();
//void CAN_tx(canmsg input, uint8_t buffer_number);
//void CAN_rx(canmsg output, uint8_t buffer_number);
// lightweight functions
//uint8_t MCP2515_rw(uint8_t op, uint8_t address, uint8_t *data, uint8_t count);
void CAN_rx_light(uint8_t *output);
void MCP2515_setup();

// defines for MCP2515 comms
#define RST_INST		0b11000000
#define READ_INST		0b00000011
#define WRITE_INST		0b00000010
#define READ_STATUS		0b10100000
#define RX_STATUS		0b10110000
#define BIT_MODIFY		0b00000101
#define RTS_INST		0b10000000

#endif /* SERIAL_COMMS_H_ */