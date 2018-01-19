/*
 * neopixel.h
 *
 * Created: 16/12/2017 21:48:26
 *  Author: James
 */ 


#ifndef NEOPIXEL_H_
#define NEOPIXEL_H_

void WS2812(uint8_t *data, uint8_t num);
void update_strip();
void set_all_pixels(uint8_t red, uint8_t green, uint8_t blue);
void set_pixel(uint8_t num, uint8_t red, uint8_t green, uint8_t blue);
uint8_t Wheel(uint8_t WheelPos, uint8_t colour);
void rainbow();
void rainbow_pixel();
void single_rainbow_bounce();
void smooth_single_rainbow_bounce();

#define RED		0
#define GREEN	1
#define BLUE	2


#endif /* NEOPIXEL_H_ */