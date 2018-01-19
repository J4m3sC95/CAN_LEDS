/*
 * uart.cpp
 *
 * Created: 19/01/2018 17:50:41
 *  Author: James
 */ 

#include "uart.h"

static volatile PortGroup *porta = (PortGroup *)PORT;
static volatile SercomUsart *uart = (SercomUsart *)SERCOM0;

void Uart::setup(){
	//setup tx pin to output
	porta->DIR.bit.DIR |= TX_PORT;
	
	//setup rx/tx pin multiplexers
	porta->PINCFG[TX_PIN].bit.PMUXEN=1;
	porta->PINCFG[RX_PIN].bit.PMUXEN=1;
	porta->PINCFG[RX_PIN].bit.INEN=1;
	
	porta->PMUX[RX_PIN/2].bit.PMUXO=PORT_PMUX_PMUXO_C_Val;
	porta->PMUX[TX_PIN/2].bit.PMUXE=PORT_PMUX_PMUXE_C_Val;
	
	//uart setup
	// select correct clock mode either external (0x0 default) or internal (0x1)
	uart->CTRLA.bit.MODE = 1;
	// select comms mode (asynchronous (default or synchronous))
	//uart->CTRLA.bit.CMODE = 0;
	// select sercom pads for rx and tx
	uart->CTRLA.bit.RXPO=3;
	uart->CTRLA.bit.TXPO=1;
	// select character size (8 = default)
	//uart->CTRLB.bit.CHSIZE = 0;
	// choose data order (MSB first = default)
	uart->CTRLA.bit.DORD = 1;
	// choose parity (none = default)
	// choose stop bit numbers (1 = default)
	//uart->CTRLB.bit.SBMODE = 0;
	// configure baud rate for 8MHz clock (9600)
	// BAUD = 65536*(1-(16*baud/8MHz))
	uart->BAUD.bit.BAUD = 64278;
	// enable transmitter/receiver
	uart->CTRLB.reg |= SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN;
	while(uart->SYNCBUSY.bit.CTRLB);
	// enable UART
	uart->CTRLA.bit.ENABLE = 1;
	while(uart->SYNCBUSY.bit.ENABLE);
	
	//enable interrupts
	uart->INTENSET.bit.RXC = 1;
	NVIC_EnableIRQ(SERCOM0_IRQn);
}

void Uart::print(char *buffer, uint16_t char_count){
	uint16_t n;
	for(n = 0; n <char_count; n++){
		uart->DATA.bit.DATA = buffer[n];
		while(!uart->INTFLAG.bit.DRE);
	} 
}

// function for receiving data through polling
char Uart::receive(){
	while(!uart->INTFLAG.bit.RXC);
	return uart->DATA.bit.DATA;
}

// interrupt handler for receiving data
void SERCOM0_Handler(){
	uint8_t data = uart->DATA.bit.DATA;
	uart->DATA.bit.DATA = data;
	porta->OUTTGL.reg = PORT_PA09;
}
