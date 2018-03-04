/*
 * Integration.cpp
 *
 * Created: 08/11/2017 18:30:56
 *  Author: James
 */ 

#include "Integration.h"

uint8_t record_eeprom = 0;
uint8_t eeprom_count = 0;
uint8_t active = 1;
uint8_t loop_count = 0;

uint16_t delay_counter = 0;
uint16_t delay_time = 0;

uint8_t current_command = 0;

uint8_t command[9];
uint16_t temp_buffer[4];

display test;

void setup(){
	cube_setup();
	MCP2515_setup();
	
	eeprom_count = eeprom(EEPROM_READ, 0xFF,0);
}

uint8_t eeprom(uint8_t rw, uint8_t address, uint8_t data){
	// turn off interrupts
	cli();
	// wait for completion of previous operation
	while(EECR);
	
	// set registers
	EEAR = address;
	if(rw){
		// read
		EECR = (1<<EERE);
	}
	else{
		// write
		EEDR = data;
		
		// write data
		EECR |= (1<<EEMPE);
		EECR |= (1<<EEPE);
	}

	//enable interrupts
	sei();
	
	return EEDR;
}

void eeprom_command(uint8_t *output_command, uint8_t count){
	uint8_t n;
	for(n = 0; n < 8; n++){
		output_command[n] = eeprom(EEPROM_READ, (count << 3) + n, 0);
	}
}

void parse(uint8_t *input_command){
	uint8_t n, arg1, arg2;
	for(n = 0; n < 3; n++){
		temp_buffer[n] = (input_command[(n << 1) + 2] << 8) | input_command[(n << 1) + 3];
	}
	arg1 = input_command[1] & 0xF;
	arg2 = ((input_command[1] & 0xF0) >> 4) - 1;
	switch(input_command[0]){
		case LOAD:
		{
			test.load_buffer(temp_buffer);
		}
		break;
		case ROTATE:
		{
			test.rotate(arg1, arg2);
		}
		break;
		case MIRROR:
		{
			test.mirror(arg1);
		}
		break;
		case TRANSLATE:
		{
			test.translate(arg1, arg2, temp_buffer);
		}
		break;
		case TRANSLATE_CLEAR:
		{
			test.translate_distance = 0;
		}
		break;
		case EEPROM_WRITE_BEGIN:
		{
			record_eeprom = 1;
			eeprom_count = 0;
			active = 0;
		}
		break;
		case EEPROM_WRITE_END:
		{
			eeprom(EEPROM_WRITE, 0xFF, eeprom_count);
			record_eeprom = 0;
			active = 1;
			current_command = 0;
			delay_counter = 0;
			loop_count = 0;
		}
		break;
		case ACTIVATE:
		{
			current_command = 0;
			active = 1;
			delay_counter = 0;
			loop_count = 0;
		}
		break;
		case DEACTIVATE:
		{
			test.load_buffer(temp_buffer);
			active = 0;
		}
		break;
		case LOOP:
		{
			if(loop_count == command[3]){
				loop_count = 0;
			}
			else{
				// go back the number of commands to loop plus the one command that is incremented afterwards
				current_command -= (command[2] + 1);
				loop_count++;
			}
		}
		break;
		case DELAY:
		{
			/*
			- a delay cycle is approximately 74us
			- multiplying the ms value by 16 uses a delay cycle of 62.5us
			- maximum delay with 16bit integer = 4096ms	
			*/	
			delay_counter++;
			delay_time = ((command[2] << 8) | command[3]) << 4;
			if(delay_counter == delay_time){
				delay_counter = 0;
			}
		}
		break;
	}
	test.send_to_cube();
}

void display_main(){
	uint8_t n;
	
	// if message waiting
	if(!bittest(PINA, PA1)){
		CAN_rx_light(command);
		if(record_eeprom && (command[0] != EEPROM_WRITE_END)){
			for(n = 0; n < 8; n++){
				eeprom(EEPROM_WRITE, (eeprom_count << 3) + n, command[n]);
			}
			eeprom_count++;
		}
		else{
			parse(command);
		}
	}
	else if((!record_eeprom) && active){
		eeprom_command(command, current_command);
		parse(command);
		
		if(!delay_counter){
			if(current_command == (eeprom_count-1)){
				current_command = 0;
			}
			else{
				current_command++;
			}
		}
	}
}