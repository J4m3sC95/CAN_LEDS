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

class Uart{
	public:
	void setup();
	void print(char *buffer, uint16_t char_count);
	char receive();
	};



#endif /* UART_H_ */