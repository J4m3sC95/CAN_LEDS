/*
 * Integration.h
 *
 * Created: 08/11/2017 18:32:27
 *  Author: James
 */ 


#ifndef INTEGRATION_H_
#define INTEGRATION_H_

#include "main.h"
#include "Serial_Comms.h"
#include "LED_Cube.h"

void setup();
uint8_t eeprom(uint8_t rw, uint8_t address, uint8_t data);
void eeprom_command(uint8_t *output_command, uint8_t count);
void parse(uint8_t *input_command);
void display_main();

/*
CAN led cube controls:
8 byte data format:
- byte 0 = command
- byte 1 = argument 1 (axis) and argument 2 (direction + 1) = arg1 | (arg2 << 4)
- bytes 2 to 7 = data
- for the loop byte 2 is the number of commands to loop, byte 3 is the number of loops to complete
- for the delay byte 2 and 3 are the 16bit delay in ms (command[2] << 8) | command[3] (max 4096)
*/

// defines for different effect functions
#define LOAD					0
#define ROTATE					1
#define MIRROR					2
#define TRANSLATE				3
#define TRANSLATE_CLEAR			4
#define EEPROM_WRITE_BEGIN		5
#define EEPROM_WRITE_END		6
#define ACTIVATE				7
#define DEACTIVATE				8
#define LOOP					9
#define DELAY					10

#endif /* INTEGRATION_H_ */