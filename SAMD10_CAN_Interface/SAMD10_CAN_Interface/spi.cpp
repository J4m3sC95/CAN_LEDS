/*
 * spi.cpp
 *
 * Created: 18/02/2018 14:03:56
 *  Author: James
 */ 

#include "spi.h"

void spiSetup(){
	//setup MOSI, SCK and SS pins to output
	PORTA->DIR.bit.DIR |= MOSI_PORT | SCK_PORT | SS_PORT;
	
	CHIP_DISABLE();	
	
	//setup pin multiplexers
	PORTA->PINCFG[MOSI_PIN].bit.PMUXEN=1;
	PORTA->PINCFG[SCK_PIN].bit.PMUXEN=1;
	PORTA->PINCFG[MISO_PIN].bit.PMUXEN=1;
	PORTA->PINCFG[MISO_PIN].bit.INEN=1;
	
	PORTA->PMUX[SCK_PIN/2].bit.PMUXO=PORT_PMUX_PMUXO_C_Val;
	PORTA->PMUX[MOSI_PIN/2].bit.PMUXE=PORT_PMUX_PMUXE_C_Val;
	PORTA->PMUX[MISO_PIN/2].bit.PMUXE=PORT_PMUX_PMUXE_C_Val;
	
	// spi configuration
	// master/slave mode (0x3 = master/0x2 = slave)
	SPI->CTRLA.bit.MODE = 3;
	// transfer mode (use mode 1 for MCP2515)
	SPI->CTRLA.bit.CPOL = 0;
	SPI->CTRLA.bit.CPHA = 1;
	// select frame format (0 = no frame format)
	//SPI->CTRLA.bit.FORM = 0;
	// select input/output pads
	SPI->CTRLA.bit.DIPO = 2;
	SPI->CTRLA.bit.DOPO = 3;
	// select char size (default = 0: 8bits)
	//SPI->CTRLB.bit.CHSIZE = 0;
	// select data direction (default = 0, MSB first)
	//SPI->CTRLA.bit.DORD = 0;
	// setup 0.1MHZ BAUD = (8MHz/(2*0.1MHz)) - 1 = 3
	SPI->BAUD.bit.BAUD = 39;	
	// hardware SS pin (disable = 0)
	//SPI->CTRLB.bit.MSSEN = 0;
	// enable receiver
	SPI->CTRLB.bit.RXEN = 1;
	while(SPI->SYNCBUSY.bit.CTRLB);
	// enable spi
	SPI->CTRLA.bit.ENABLE = 1;
	while(SPI->SYNCBUSY.bit.CTRLB);
}

uint8_t spiTransfer(uint8_t data){
	SPI->DATA.bit.DATA = data;
	while(!SPI->INTFLAG.bit.RXC);
	return SPI->DATA.bit.DATA;
}