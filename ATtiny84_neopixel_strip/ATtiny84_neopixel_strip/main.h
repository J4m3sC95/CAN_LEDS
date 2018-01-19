/*
 * main.h
 *
 * Created: 16/12/2017 20:55:03
 *  Author: James
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

// ANSI C REGISTER FUNCTIONS
#define bitset(reg,bitnum) (reg |=(1<<bitnum))
#define bitclear(reg,bitnum) (reg &= ~(1<<bitnum))
#define bittest(reg,bitnum) (reg &(1<<bitnum))
#define bitinvert(reg,bitnum) (reg ^=(1<<bitnum))

#endif /* MAIN_H_ */