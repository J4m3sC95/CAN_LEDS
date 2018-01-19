/*
 * SAMD10_CAN_Interface.cpp
 *
 * Created: 07/01/2018 17:36:09
 * Author : James
 */ 

#include "sam.h"
#include <inttypes.h>

// Definitions for useful stuff
#define LED_PORT	PORT_PA09
#define LED_PIN		PIN_PA09
#define RX_PIN		PIN_PA11
#define RX_PORT		PORT_PA11
#define TX_PIN		PIN_PA10
#define TX_PORT		PORT_PA10
#define CLK_IN_PORT		PORT_PA08
#define CLK_IN_PIN		PIN_PA08
#define SWITCH_PORT		PORT_PA25
#define SWITCH_PIN		PIN_PA25

// Peripherals
volatile PortGroup *porta = (PortGroup *)PORT;
volatile SercomUsart *uart = (SercomUsart *)SERCOM0;
volatile Pm *power = (Pm *)PM;
volatile Gclk *genclk = (Gclk *)GCLK;

int main(void)
{
    uint32_t n;
	
	/* Initialize the SAM system */
    SystemInit();
	
	//setup external 8MHz clock from ATmega32u4 (mEDBG)
	porta->PINCFG[CLK_IN_PIN].bit.PMUXEN=1;
	porta->PINCFG[CLK_IN_PIN].bit.INEN=1;
	porta->PMUX[CLK_IN_PIN/2].bit.PMUXE = PORT_PMUX_PMUXE_H_Val;
	genclk->GENCTRL.reg = GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_GCLKIN;
		
	// setup led output
	porta->DIR.bit.DIR |= PORT_PA09;
	porta->OUT.bit.OUT |= PORT_PA09;
	
	//enable clock for sercom0 and PAC2
	power->APBCMASK.bit.PAC2_=1;
	power->APBCMASK.bit.SERCOM0_=1;	
	
	// setup generic clock0 for the sercom
	genclk->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM0_CORE;
	
	/*
	//check if gclk is enabled
	genclk->CLKCTRL.bit.ID = GCLK_CLKCTRL_ID_SERCOM0_CORE;	
	while(!genclk->CLKCTRL.bit.CLKEN);	
	*/
	
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
	
	while (1)
	{
		porta->OUTTGL.reg = PORT_PA09;
		uart->DATA.bit.DATA = 'a';
		while(!uart->INTFLAG.bit.DRE);
		uart->DATA.bit.DATA = '\n';
		while(!uart->INTFLAG.bit.DRE);
		uart->DATA.bit.DATA = '\r';
		while(!uart->INTFLAG.bit.DRE);
		for(n = 0; n<1000000; n++);
				
	}
}
