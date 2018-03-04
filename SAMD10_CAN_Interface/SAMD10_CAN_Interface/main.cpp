/*
 * SAMD10_CAN_Interface.cpp
 *
 * Created: 07/01/2018 17:36:09
 * Author : James
 */ 

#include "main.h"

#include "system.h"
#include "uart.h"
#include "spi.h"
#include "CAN.h"

command cmd;

int main(void)
{				
	systemSetup();	
	serialSetup();
	spiSetup();
	CAN_setup();	
	
	//led_cube_test();
	
	while (1){
		cmd = serialReceiveCommand();
		led_cube(cmd.raw.commandID, cmd.raw.arg1, cmd.raw.arg2, cmd.raw.led_buff);
	}
}


