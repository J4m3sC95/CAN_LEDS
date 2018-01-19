/*
 * LED_Cube.h
 *
 * Created: 15/09/2017 20:48:21
 *  Author: James
 */ 

/* Pin Mapping:
	LED column numbering: 0 = bottom left, rest of numbers = left to right bottom to top
	Port D 0 to 6 = led columns 0 to 6
	Port B 0 to 1 = led columns 7 to 8
	Port B 2 to 4 = led layers bottom (0) to top (2)
*/

#ifndef LED_CUBE_H_
#define LED_CUBE_H_

#include "main.h"

// Constant definitions
#define POSITIVE 1
#define NEGATIVE -1
#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2
#define YZPLANE 0
#define ZXPLANE 1
#define XYPLANE 2

// Function Declarations
void cube_setup();
void layer_out(uint16_t layer);
//void static_cube_display(uint16_t layer0, uint16_t layer1, uint16_t layer2);
void update_buffer(uint16_t *layer);
void update_cube();
void transform(uint16_t *input_buffer, void (*funct)(uint8_t, int8_t, int8_t, int8_t*), int8_t arg1, int8_t arg2, int8_t arg3);
void rotate_point(uint8_t axis, int8_t direction, int8_t arg3, int8_t *point);
void mirror_point(uint8_t plane, int8_t arg2, int8_t arg3, int8_t *point);
void translate_point(uint8_t axis, int8_t direction, int8_t offset, int8_t *point);
void composite(uint16_t *buffer1, uint16_t *buffer2);

// display class declaration
class display{
	/* this class should do the following:
	- take in one or two cube patterns
	- convert the coordinates to xyz (if necessary?)
	- one function per translation/rotation/effect
	- function to continue translation/rotation/effect once setup by previous function
	- function to stop translation/rotation/effect
	- clear everything?
	*/
		
	// public member functions and variables
	public:
	// member variables
	uint16_t output_buffer[4];
	uint8_t translate_distance;
	
	// initialise variables
	display(void);
	// public functions
	void load_buffer(uint16_t *input_buffer);
	void rotate(int8_t axis, int8_t direction);
	void mirror(int8_t plane);
	void translate(int8_t axis, int8_t direction, uint16_t *replacement);
	void send_to_cube(void);
	
};

#define EEPROM_READ		1
#define EEPROM_WRITE	0

#endif /* LED_CUBE_H_ */