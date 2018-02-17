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

command cmd;

int main(void)
{	
	clockSetup();
	serialSetup();
		
	// setup led output
	porta->DIR.bit.DIR |= LED_PORT;
	porta->OUT.bit.OUT |= LED_PORT;
	
	while (1){
		cmd = serialReceiveCommand();
	}
}
