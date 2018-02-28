/*
 * clock.cpp
 *
 * Created: 19/01/2018 17:16:13
 *  Author: James
 */ 

#include "clock.h"

// Peripherals
static volatile PortGroup *porta = (PortGroup *)PORT;

void clockSetup(){
	//setup external 8MHz clock from ATmega32u4 (mEDBG)
	porta->PINCFG[CLK_IN_PIN].bit.PMUXEN=1;
	porta->PINCFG[CLK_IN_PIN].bit.INEN=1;
	porta->PMUX[CLK_IN_PIN/2].bit.PMUXE = PORT_PMUX_PMUXE_H_Val;
	GCLK->GENCTRL.reg = GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_GCLKIN;
	
	//enable clock for sercom 0&1 and PAC2 in power management registers	
	PM->APBCMASK.bit.PAC2_=1;
	PM->APBCMASK.bit.SERCOM0_=1;
	PM->APBCMASK.bit.SERCOM1_=1;
	
	// setup generic clock0 for the sercoms 0 & 1
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM0_CORE;
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_SERCOM1_CORE;
}

void watchdogSetup(){
	// watchdog clock
	// watchdog period = 16384 clock cycle ~ 0.5 secs
	//watchdog->CONFIG.bit.PER = 0xB;
	//watchdog->CONFIG.bit.WINDOW = 0xB;
	// enable watchdog
	WDT->CTRL.bit.ENABLE = 1;
}

void watchdogClear(){
	WDT->CLEAR.bit.CLEAR = 0xA5;
}
