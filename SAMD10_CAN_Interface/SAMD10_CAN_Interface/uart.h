/*
 * uart.h
 *
 * Created: 19/01/2018 17:50:17
 *  Author: James
 */ 


#ifndef UART_H_
#define UART_H_

#include "main.h"

#define UART ((SercomUsart *)SERCOM0)

void serialSetup();
void serialPrint(char *buffer, uint16_t char_count);
void serialPrintString(char *buffer);
char serialReceive();
command serialReceiveCommand();
void serialWriteByte(uint8_t byte);

#endif /* UART_H_ */