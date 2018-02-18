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

// Peripherals
static volatile PortGroup *porta = (PortGroup *)PORT;

command cmd;

int main(void)
{	
	int n;
	uint8_t data = 0;
	
	clockSetup();
	serialSetup();
	spiSetup();
		
	// setup led output
	porta->DIR.bit.DIR |= LED_PORT;
	porta->OUT.bit.OUT |= LED_PORT;
	
	while (1){
		//cmd = serialReceiveCommand();
		CHIP_ENABLE();
		data = spiTransfer(data) + 1;
		CHIP_DISABLE();
		for(n = 0; n<100; n++);
	}
}
