/*
 * uart.h
 *
 * Created: 19/01/2018 17:50:17
 *  Author: James
 */ 


#ifndef UART_H_
#define UART_H_

#include "main.h"
#include <stdio.h>

typedef union{
	struct{
		uint8_t commandID;
		uint8_t arg1:4;
		uint8_t arg2:4;
		uint16_t led_buff[4];
	}raw;
	uint8_t CANdata[9];
} command;

void serialSetup();
void serialPrint(char *buffer, uint16_t char_count);
void serialPrintString(char *buffer);
char serialReceive();
command serialReceiveCommand();
void serialWriteByte(uint8_t byte);

#endif /* UART_H_ */