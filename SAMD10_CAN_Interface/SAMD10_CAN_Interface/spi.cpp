/*
 * spi.cpp
 *
 * Created: 18/02/2018 14:03:56
 *  Author: James
 */ 

#include "spi.h"

static volatile PortGroup *porta = (PortGroup *)PORT;
static volatile SercomSpi *spi = (SercomSpi *)SERCOM1;

void spiSetup(){
	//setup MOSI, SCK and SS pins to output
	porta->DIR.bit.DIR |= MOSI_PORT | SCK_PORT | SS_PORT;
	
	CHIP_DISABLE();	
	
	//setup pin multiplexers
	porta->PINCFG[MOSI_PIN].bit.PMUXEN=1;
	porta->PINCFG[SCK_PIN].bit.PMUXEN=1;
	porta->PINCFG[MISO_PIN].bit.PMUXEN=1;
	porta->PINCFG[MISO_PIN].bit.INEN=1;
	
	porta->PMUX[SCK_PIN/2].bit.PMUXO=PORT_PMUX_PMUXO_C_Val;
	porta->PMUX[MOSI_PIN/2].bit.PMUXE=PORT_PMUX_PMUXE_C_Val;
	porta->PMUX[MISO_PIN/2].bit.PMUXE=PORT_PMUX_PMUXE_C_Val;
	
	// spi configuration
	// master/slave mode (0x3 = master/0x2 = slave)
	spi->CTRLA.bit.MODE = 3;
	// transfer mode (use mode 1 for MCP2515)
	spi->CTRLA.bit.CPOL = 0;
	spi->CTRLA.bit.CPHA = 1;
	// select frame format (0 = no frame format)
	//spi->CTRLA.bit.FORM = 0;
	// select input/output pads
	spi->CTRLA.bit.DIPO = 2;
	spi->CTRLA.bit.DOPO = 3;
	// select char size (default = 0: 8bits)
	//spi->CTRLB.bit.CHSIZE = 0;
	// select data direction (default = 0, MSB first)
	//spi->CTRLA.bit.DORD = 0;
	// setup 1MHZ BAUD = (8MHz/(2*1MHz)) - 1 = 3
	//spi->BAUD.bit.BAUD = 3;
	// setup 0.1MHZ BAUD = (8MHz/(2*0.1MHz)) - 1 = 3
	spi->BAUD.bit.BAUD = 39;	
	// hardware SS pin (disable = 0)
	//spi->CTRLB.bit.MSSEN = 0;
	// enable receiver
	spi->CTRLB.bit.RXEN = 1;
	while(spi->SYNCBUSY.bit.CTRLB);
	// enable spi
	spi->CTRLA.bit.ENABLE = 1;
	while(spi->SYNCBUSY.bit.CTRLB);
}

uint8_t spiTransfer(uint8_t data){
	spi->DATA.bit.DATA = data;
	while(!spi->INTFLAG.bit.RXC);
	return spi->DATA.bit.DATA;
}