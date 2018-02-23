/*
 * SAMD10_CAN_Interface.cpp
 *
 * Created: 07/01/2018 17:36:09
 * Author : James
 */ 

#include "main.h"

#include "clock.h"
#include "uart.h"
#include "spi.h"
#include "CAN.h"

// Peripherals
static volatile PortGroup *porta = (PortGroup *)PORT;

command cmd;

int main(void)
{	
	//int n;
	//uint8_t data = 0;
	
	clockSetup();
	serialSetup();
	spiSetup();
	CAN_setup();
		
	// setup led output
	porta->DIR.bit.DIR |= LED_PORT;
	porta->OUT.bit.OUT |= LED_PORT;
	
	while (1){
		cmd = serialReceiveCommand();
		led_cube(cmd.raw.commandID, cmd.raw.arg1, cmd.raw.arg2, cmd.raw.led_buff);
	}
}
