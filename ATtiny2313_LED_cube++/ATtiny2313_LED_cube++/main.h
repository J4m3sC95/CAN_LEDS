/*
 * main.h
 *
 * Created: 25/10/2017 19:34:03
 *  Author: James
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <inttypes.h>

// INCLUDE AVR LIBRARIES
#include <avr/io.h>
#include <avr/interrupt.h>
// delay library setup
#define F_CPU 8000000UL
#include <util/delay.h>

// ANSI C REGISTER FUNCTIONS
#define bitset(reg,bitnum) (reg |=(1<<bitnum))
#define bitclear(reg,bitnum) (reg &= ~(1<<bitnum))
#define bittest(reg,bitnum) (reg &(1<<bitnum))

#endif /* MAIN_H_ */