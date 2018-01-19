/*
 * neopixel.cpp
 *
 * Created: 16/12/2017 21:17:59
 *  Author: James
 */ 

#include "main.h"
#include "neopixel.h"

/******* HIGH LEVEL EFFECTS *******/

void rainbow(){
	uint8_t pos = 1;
	while(pos){
		set_all_pixels(Wheel(pos, RED), Wheel(pos, GREEN), Wheel(pos, BLUE));
		update_strip();
		_delay_ms(10);
		pos++;
	}
}

void rainbow_pixel(){
	uint8_t n;
	uint8_t pos = 1;
	uint8_t offset = 10;
	while(pos){
		for(n = 0; n < 30; n++){
			set_pixel(n, Wheel(pos + (n*offset), RED), Wheel(pos + (n*offset), GREEN), Wheel(pos + (n*offset), BLUE));
		}
		update_strip();
		_delay_ms(10);
		pos++;
		
	}
}

void single_rainbow_bounce(){
	uint8_t pixel_num = 0;
	for(pixel_num = 0; pixel_num < 60; pixel_num++){
		set_all_pixels(0,0,0);
		if(pixel_num < 30){
			set_pixel(pixel_num, Wheel(pixel_num << 3, RED), Wheel(pixel_num << 3, GREEN), Wheel(pixel_num << 3, BLUE));
		}
		else{
			set_pixel(59 - pixel_num, Wheel((59 - pixel_num) << 3, RED), Wheel((59 - pixel_num) << 3, GREEN), Wheel((59 - pixel_num) << 3, BLUE));
		}
		
		update_strip();
		_delay_ms(100);
	}
}

void smooth_single_rainbow_bounce(){
	uint8_t decreasing = 0;
	uint8_t increasing = 1;
	uint8_t n;
	uint8_t steps = 100;
	uint8_t reverse = 0;
	while (increasing){
		set_all_pixels(0,0,0);
		for(n = 0; n < steps; n++){
			set_pixel(decreasing, (steps - n) * Wheel(decreasing << 3, RED)/steps, (steps - n) * Wheel(decreasing << 3, GREEN)/steps, (steps - n) * Wheel(decreasing << 3, BLUE)/steps);
			set_pixel(increasing, (n) * Wheel(increasing << 3, RED)/steps, (n) * Wheel(increasing << 3, GREEN)/steps, (n) * Wheel(increasing << 3, BLUE)/steps);
			update_strip();
			_delay_us(200);
		}
		if(!reverse){
			increasing++;
			decreasing++;
			if(increasing == 30){
				increasing = 28;
				reverse = 1;
			}
		}
		else{
			increasing--;
			decreasing--;
		}
	}
}



/******** INTERMEDIATE PIXEL CONTROL *******/

uint8_t pixels[91];

uint8_t brightness = 100;

void update_strip(){
	WS2812(pixels, 90);
}

void set_all_pixels(uint8_t red, uint8_t green, uint8_t blue){
	uint16_t n, r, g, b;
	r = (red*brightness) >> 8;
	g = (green*brightness) >> 8;
	b = (blue*brightness) >> 8;
	for(n = 0; n < 30; n++){
		pixels[n*3] = g;
		pixels[(n*3) + 1] = r;
		pixels[(n*3) + 2] = b;		
	}
}

// set pixel with index from 0 to 29
void set_pixel(uint8_t num, uint8_t red, uint8_t green, uint8_t blue){
	uint16_t r, g, b;
	r = (red*brightness) >> 8;
	g = (green*brightness) >> 8;
	b = (blue*brightness) >> 8;
	pixels[num*3] = g;
	pixels[(num*3) + 1] = r;
	pixels[(num*3) + 2] = b;
}

uint8_t Wheel(uint8_t colour_pos, uint8_t colour) {
	uint8_t red,green,blue,WheelPos;
	WheelPos = 255 - colour_pos;
	if(WheelPos < 85) {
		red = 255 - WheelPos * 3;
		green = 0;
		blue =  WheelPos * 3;
	}
	else if(WheelPos < 170) {
		WheelPos -= 85;
		red = 0;
		green =  WheelPos * 3;
		blue = 255 - WheelPos * 3;
	}
	else{
		WheelPos -= 170;
		red = WheelPos * 3;
		green = 255 - WheelPos * 3;
		blue = 0;
	}
	if(colour == RED)	return red;
	if(colour == GREEN) return green;
	if(colour == BLUE)	return blue;	
	return 0;
}

/******** LOW LEVEL NEOPIXEL CONTROL *******/

/* one clock cycle takes 62.5ns @16MHz
the WS2812 protocol has two bit times one for bit = 1 and bit  = 0
whole bit is 1.25us = 20 clocks

- T0H = 0.4us = 5.6 clocks
- T1H = 0.8us = 12.8 clocks
- T0L = 0.85us = 13.6 clocks
- T1L = 0.45us = 7.2 clocks
- RES = >50us = >16 clock
*/

// function from the adafruit code transmits rgb data for pixels
void WS2812(uint8_t *data, uint8_t num) {
	volatile uint16_t
    i   = num; // Loop counter (number of bytes)
	volatile uint8_t
   *ptr = data,   // Pointer to next byte
    b   = *ptr++,   // Current byte value
    hi,             // PORT w/output bit set high
    lo;             // PORT w/output bit set low
	
	
	volatile uint8_t *port = &PORTA;

    volatile uint8_t next, bit;

    hi   = PORTA |  (1<<PA0);
    lo   = PORTA & ~(1<<PA0);
    next = lo;
    bit  = 8;
	
    asm volatile(
     "head20:"                   "\n\t" // Clk  Pseudocode    (T =  0)
      "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
      "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
      "mov  %[next], %[hi]"     "\n\t" // 0-1   next = hi    (T =  4)
      "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
      "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
      "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
      "breq nextbyte20"          "\n\t" // 1-2  if(bit == 0) (from dec above)
      "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
      "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
      "nop"                      "\n\t" // 1    nop           (T = 13)
      "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
      "nop"                      "\n\t" // 1    nop           (T = 16)
      "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
      "rjmp head20"              "\n\t" // 2    -> head20 (next bit out)
     "nextbyte20:"               "\n\t" //                    (T = 10)
      "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
      "ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
      "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
      "nop"                      "\n\t" // 1    nop           (T = 16)
      "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
       "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
      : [port]  "+e" (port),
        [byte]  "+r" (b),
        [bit]   "+r" (bit),
        [next]  "+r" (next),
        [count] "+w" (i)
      : [ptr]    "e" (ptr),
        [hi]     "r" (hi),
        [lo]     "r" (lo));
}