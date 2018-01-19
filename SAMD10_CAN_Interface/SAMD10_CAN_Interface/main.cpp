/*
 * SAMD10_CAN_Interface.cpp
 *
 * Created: 07/01/2018 17:36:09
 * Author : James
 */ 


#include "main.h"

#include "clock.h"
#include "uart.h"

// Peripherals
static volatile PortGroup *porta = (PortGroup *)PORT;

Uart Serial;

int main(void)
{	
	clock_setup();
	Serial.setup();
		
	// setup led output
	porta->DIR.bit.DIR |= PORT_PA09;
	porta->OUT.bit.OUT |= PORT_PA09;
	
	while (1);
}
