/*
 * main.h
 *
 * Created: 19/01/2018 17:14:21
 *  Author: James
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "sam.h"
#include <inttypes.h>
#include <stdbool.h>

// Definitions for xplained mini connections
#define LED_PORT	PORT_PA09
#define LED_PIN		PIN_PA09
#define RX_PIN		PIN_PA11
#define RX_PORT		PORT_PA11
#define TX_PIN		PIN_PA10
#define TX_PORT		PORT_PA10
#define CLK_IN_PORT		PORT_PA08
#define CLK_IN_PIN		PIN_PA08
#define BUTTON_PORT		PORT_PA25
#define BUTTON_PIN		PIN_PA25
#define QTOUCH_PORT		PORT_PA07
#define QTOUCH_PIN		PIN_PA07
#define MOSI_PORT		PORT_PA16
#define MOSI_PIN		PIN_PA16
#define SCK_PORT		PORT_PA17
#define SCK_PIN			PIN_PA17
#define MISO_PORT		PORT_PA30
#define MISO_PIN		PIN_PA30
#define SS_PORT			PORT_PA27
#define SS_PIN			PIN_PA27

typedef union{
	struct{
		uint8_t commandID;
		uint8_t arg1:4;
		uint8_t arg2:4;
		uint16_t led_buff[4];
	}raw;
	uint8_t CANdata[9];
} command;


#endif /* MAIN_H_ */