/*
 * clock.cpp
 *
 * Created: 19/01/2018 17:16:13
 *  Author: James
 */ 

#include "system.h"

// Peripherals
static volatile PortGroup *porta = (PortGroup *)PORT;

void systemSetup(){
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
	
	//setup interrupt for button to reset (EXTINT[5])
	PORTA->PINCFG[BUTTON_PIN].bit.INEN = 1;
	PORTA->PINCFG[BUTTON_PIN].bit.PMUXEN = 1;
	PORTA->PMUX[BUTTON_PIN/2].bit.PMUXO=PORT_PMUX_PMUXO_A_Val;
	// enable generic clock for EIC
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID_EIC;
	// write config registers
	EIC->INTENSET.bit.EXTINT5=1;
	EIC->CONFIG[0].reg = EIC_CONFIG_FILTEN5 | EIC_CONFIG_SENSE5_FALL;
	// enable EIC
	EIC->CTRL.bit.ENABLE = 1;
	NVIC_EnableIRQ(EIC_IRQn);
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

void EIC_Handler(){
	uint32_t n = 0;
	n |= (0x05FA << SCB_AIRCR_VECTKEY_Pos);
	n |= (1 << SCB_AIRCR_SYSRESETREQ_Pos);
	SCB->AIRCR = n;
}
