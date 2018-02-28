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
#define RX_PORT		PORT_PA11
#define RX_PIN		PIN_PA11
#define TX_PORT		PORT_PA10
#define TX_PIN		PIN_PA10
#define CLK_IN_PORT		PORT_PA08
#define CLK_IN_PIN		PIN_PA08
#define BUTTON_PORT		PORT_PA25
#define BUTTON_PIN		PIN_PA25
#define QTOUCH_PORT		PORT_PA07
#define QTOUCH_PIN		PIN_PA07
#define SWCLK_PORT		PORT_PA30
#define SWCLK_PIN		PIN_PA30
#define SWDIO_PORT		PORT_PA31
#define SWDIO_PIN		PIN_PA31
#define MOSI_PORT		PORT_PA22
#define MOSI_PIN		PIN_PA22
#define SCK_PORT		LED_PORT
#define SCK_PIN			LED_PIN
#define MISO_PORT		PORT_PA24
#define MISO_PIN		PIN_PA24
#define SS_PORT			PORT_PA23
#define SS_PIN			PIN_PA23

typedef union{
	struct{
		uint8_t commandID;
		uint8_t arg1:4;
		uint8_t arg2:4;
		uint16_t led_buff[4];
	}raw;
	uint8_t CANdata[9];
} command;


// delay macros
#define F_CPU	8000000UL
#define _CyclesPerDelayLoop  6
#define _LoopCount_ms(ms)  (uint32_t)(((F_CPU / 1000UL) * (ms)) / _CyclesPerDelayLoop)
#define _LoopCount_us(us)  (uint32_t)(((F_CPU / 1000000UL) * (us)) / _CyclesPerDelayLoop)
#define ddDelay_ms(ms)   _ddCycleDelay(_LoopCount_ms(ms))
#define ddDelay_us(us)   _ddCycleDelay(_LoopCount_us(us))

inline void _ddCycleDelay(volatile uint32_t count) {
	asm volatile (
	"mov r0, %0 \n"  // Get the loop count
	"loop%=:    \n"  // Loop start label
	"DMB        \n"  // Data Memory Barrier (3 cycles)
	"sub r0, #1 \n"  // Decrement count     (1 cycle)
	"bne loop%= \n"  // Branch back to loop (2 cycles)
	:     // Nothing output from assembly
	: "r" (count)  // Register input for count
	: "r0", "cc"  // Clobber list
	);
}

#endif /* MAIN_H_ */