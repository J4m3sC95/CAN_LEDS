/*
 * LED_Cube.c
 *
 * Created: 15/09/2017 20:49:47
 *  Author: James
 */ 

#include "LED_Cube.h"

// Global Variables
volatile uint8_t interrupt_layer;
volatile uint16_t *display_buffer[3];
volatile uint16_t buffer0[4];
volatile uint16_t buffer1[4];
volatile uint8_t active_buffer;

void cube_setup(){
	uint8_t n;
	//turn outputs on
	DDRD = 0x7F;
	DDRB = 0xDF;
	DDRA = 0x01;
	
	// setup spi mode (not needed)
	// USICR = 1<<USIWM0;
	// disable chip
	bitset(PORTA, PA0);
	
	// initialise buffers
	for(n = 0; n < 3; n++){
		buffer0[n] = 0x1FF;
	}
	for(n = 0; n < 3; n++){
		buffer1[n] = 0;
	}
	display_buffer[0] = buffer0;
	display_buffer[1] = buffer1;
		
	active_buffer = 0;
	
	// setup timer
	interrupt_layer = 2;
	// normal mode
	TCCR0A = (0<<WGM01) | (0<<WGM00);
		
	// set clock prescaler to /64 to give 2ms interval
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);
		
	// set clock prescaler to /1024 to give 30ms interval
	//TCCR0B = (1<<CS02) | (0<CS01) | (1<<CS00);
		
	// enable overflow interrupt
	bitset(TIMSK, TOIE0);
		
	// enable global interrupts
	sei();

	// wait a bit then update the cube
	_delay_ms(1000);
	update_cube();
}

void layer_out(uint16_t layer){
	PORTD = (PORTD & 0x80) | (layer & 0x7F);
	PORTB = (PORTB & 0xFC) | ((layer >> 7) & 0x03);
}

void update_buffer(uint16_t layer[4]){
	uint8_t n;
	for(n = 0; n< 3; n++){
		display_buffer[1-active_buffer][n] = layer[n];
	}
}

void update_cube(){
	active_buffer = 1 - active_buffer;
	// delay to allow ISR to update itself (is this needed??)
	//_delay_ms(10);
}

ISR(TIMER0_OVF_vect){
	// clear previous active layer
	bitclear(PORTB, interrupt_layer);
	// increment and check for "overflow"
	interrupt_layer++;
	if(interrupt_layer == 5){
		interrupt_layer = 2;
	}
	// load new column array
	layer_out(display_buffer[active_buffer][interrupt_layer - 2]);
	// set new active layer
	bitset(PORTB, interrupt_layer);
}

// display class functions
display::display(void){
	translate_distance = 0;
	//int8_t n;
	//for(n = 0; n<3; n++){
		//output_buffer[n] = 0;
	//}
}

void display::load_buffer(uint16_t *input_buffer){
	uint8_t n;
	for(n = 0; n< 3; n++){
		output_buffer[n] = input_buffer[n];
	}
}

void display::rotate(int8_t axis, int8_t direction){
	transform(output_buffer, rotate_point, axis, direction, 0);	
}

void display::mirror(int8_t plane){
	transform(output_buffer, mirror_point, plane, 0, 0);
}

void display::translate(int8_t axis, int8_t direction, uint16_t *replacement){
	uint8_t n;
	uint16_t temp_buffer[4];
	for(n=0; n< 3; n++){
		temp_buffer[n] = replacement[n];
	}
	// translate existing buffer
	transform(output_buffer, translate_point, axis, direction, 1);
	// translate new buffer with an offset
	transform(temp_buffer, translate_point, axis, direction, translate_distance - 2);
	// combine the two and set to output
	for(n=0; n< 3; n++){
		output_buffer[n] |= temp_buffer[n];
	}
	
	translate_distance++;
}

void display::send_to_cube(){
	update_buffer(output_buffer);
	update_cube();
}

void transform(uint16_t *input_buffer, void (*funct)(uint8_t, int8_t, int8_t, int8_t*), int8_t arg1, int8_t arg2, int8_t arg3){
	uint8_t n,m;
	int8_t point[7];
	uint16_t buffer[4];
	/*
	x0 = point[0]
	y0 = point[1]
	z0 = point[2]
	x1 = point[3]
	y1 = point[4]
	z1 = point[5]
	*/
	// clear output buffer
	for(n = 0; n<3; n++){
		buffer[n] = 0;
	}
	// loop through layers (z axis 0 to 2)
	for(n = 0; n < 3; n++){
		// loop through bits to find 1s
		for(m = 0; m < 9; m++){
			if(input_buffer[n] & (1<<m)){
				// when a 1 is found transform it to new location
				point[0] = (m%3) - 1;;
				point[1] = (m/3) - 1;
				point[2] = n - 1;
						
				/*** PERFORM TRANSLATION****/
				funct(arg1, arg2, arg3, point);
								
				//check if the value is ok
				if(!((point[arg1+3] > 1) || (point[arg1+3] < -1))){
					point[3]++;
					point[4]++;
					point[5]++;
					
					// put new data in output buffer
					buffer[point[5]] |= 1 << (point[3] + (point[4]*3));
				}
			}
		}
	}
	for(n = 0; n< 3; n++){
		input_buffer[n] = buffer[n];
	}
}

// rotate 90°
/*
void rotate_point(uint8_t axis, int8_t direction, int8_t *point){
	switch(axis){
		case XAXIS:
		{
			point[3] = point[0];
			point[4] = -1*direction*point[2];
			point[5] = direction*point[1];
		}
		break;
		case YAXIS:
		{
			point[4] = point[1];
			point[5] = -1*direction*point[0];
			point[3] = direction*point[2];
		}
		break;
		case ZAXIS:
		{
			point[5] = point[2];
			point[3] = -1*direction*point[1];
			point[4] = direction*point[0];
		}
		break;
	}
}
*/

// rotate 45°
void rotate_point(uint8_t axis, int8_t direction, int8_t arg3, int8_t *point){
	uint8_t n;
	switch(axis){
		case XAXIS:
		{
			point[3] = point[0];
			point[4] = point[1] - (direction*point[2]);
			point[5] = direction*point[1] + point[2];
		}
		break;
		case YAXIS:
		{
			point[4] = point[1];
			point[5] = point[2] - (direction*point[0]);
			point[3] = direction*point[2] + point[0];
		}
		break;
		case ZAXIS:
		{
			point[5] = point[2];
			point[3] = point[0] - (direction*point[1]);
			point[4] = direction*point[0] + point[1];
		}
		break;
	}
	for(n = 3; n<6; n++){
		if((point[n] > 1) || (point[n] < -1)){
			point[n] = point[n] >> 1;
		}
	}
}

void mirror_point(uint8_t plane, int8_t arg2, int8_t arg3, int8_t *point){
	point[3] = point[0];
	point[4] = point[1];
	point[5] = point[2];
	
	point[plane+3] = -point[plane];
}

void translate_point(uint8_t axis, int8_t direction, int8_t offset, int8_t *point){
	point[3] = point[0];
	point[4] = point[1];
	point[5] = point[2];
		
	point[axis+3] = point[axis] + (direction*offset);
}

void composite(uint16_t *buffer1, uint16_t *buffer2){
	uint16_t buffer[4];
	uint8_t n;
	for(n = 0; n < 3; n++){
		buffer[n] = buffer1[n] | buffer2[n];
	}
	update_buffer(buffer);
	update_cube();
}

