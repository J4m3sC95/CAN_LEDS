/*
 * ATtiny84_neopixel_strip.cpp
 *
 * Created: 16/12/2017 19:39:34
 * Author : James
 */ 

#include "main.h"
#include "neopixel.h"

int main(void)
{
    bitset(DDRA, PA0);
	while (1){
		//rainbow();
		rainbow_pixel();
		//single_rainbow_bounce();
		//smooth_single_rainbow_bounce();
	}
}



