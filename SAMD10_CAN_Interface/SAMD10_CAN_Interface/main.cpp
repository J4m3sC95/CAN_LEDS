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

command cmd;

int main(void)
{				
	clockSetup();	
	serialSetup();
	spiSetup();
	CAN_setup();	
	
	while (1){
		cmd = serialReceiveCommand();
		led_cube(cmd.raw.commandID, cmd.raw.arg1, cmd.raw.arg2, cmd.raw.led_buff);
	}
}

/* Notes
- The control of the led cube is possible
- there appears to be a problem with writing to EEPROM, possibly an issue with the delay and loop arguments being truncated by the typedef-union
