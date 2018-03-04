/*
 * CAN.h
 *
 * Created: 22/02/2018 15:15:22
 *  Author: James
 */ 

#ifndef CAN_H_
#define CAN_H_

#ifdef ARDUINO
#include <SPI.h>

// macros to make life easy
#define CHIP_ENABLE() digitalWrite(SS_PIN, LOW)
#define CHIP_DISABLE() digitalWrite(SS_PIN, HIGH)
#define spi(x) SPI.transfer(x);

#define SS_PIN  53

#else

#include "main.h"
#include "spi.h"

#define spi(x)	spiTransfer(x)
#define delay(x)	ddDelay_ms(x)
#define delayMicroseconds(x)	ddDelay_us(x)

#endif

// Constant definitions
#define POSITIVE 1
#define NEGATIVE -1
#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2
#define YZPLANE 0
#define ZXPLANE 1
#define XYPLANE 2

// can message struct
struct canmsg{
  uint32_t ID:29;
  uint32_t IDE:1;
  uint32_t RTR:1;
  uint8_t DLC:4;
  uint8_t data[9];
};

// defines for MCP2515 comms
#define RST_INST    0b11000000
#define READ_INST   0b00000011
#define WRITE_INST    0b00000010
#define READ_STATUS   0b10100000
#define RX_STATUS   0b10110000
#define BIT_MODIFY    0b00000101
#define RTS_INST    0b10000000

// function decelerations
void MCP2515_write(uint8_t address, uint8_t *data, uint8_t count);
void MCP2515_read(uint8_t address, uint8_t *data, uint8_t count);
void MCP2515_reset();
void MCP2515_rts(uint8_t buffer_number);
void MCP2515_bitmod(uint8_t address, uint8_t mask, uint8_t data);
uint8_t MCP2515_status();
void CAN_tx(canmsg input, uint8_t buffer_number);
void CAN_rx(canmsg output, uint8_t buffer_number);
void CAN_setup();
void led_cube(uint8_t instruction, uint16_t arg1, uint8_t arg2, uint16_t *buffer);
void led_cube_test();


/*
CAN led cube controls:
8 byte data format:
- byte 0 = command
- byte 1 = argument 1 (axis) and argument 2 (direction + 1) = arg1 | (arg2 << 4)
- bytes 2 to 7 = data
*/

// defines for different effect functions
#define LOAD          0
#define ROTATE          1
#define MIRROR          2
#define TRANSLATE       3
#define TRANSLATE_CLEAR     4
#define EEPROM_WRITE_BEGIN    5
#define EEPROM_WRITE_END    6
#define ACTIVATE        7
#define DEACTIVATE        8
#define LOOP          9
#define DELAY         10

// Stuff from the Arduino sketch

// Definitions for setting the led cube config
#define WRITE_TIME 100

#define eeprom_write(n) led_cube(n, 0, 0, blank_buffer);delay(WRITE_TIME)
#define load_buffer(x) led_cube(LOAD, 0, 0, x); delay(WRITE_TIME)
#define cube_delay(x) led_cube(DELAY, (x & 0xFF00) >> 8, x & 0xFF, blank_buffer); delay(WRITE_TIME)
#define cube_rotate(ax, dir) led_cube(ROTATE, ax, dir, blank_buffer); delay(WRITE_TIME)
#define cube_loop(inst, cnt) led_cube(LOOP, inst, cnt, blank_buffer);delay(WRITE_TIME)
#define cube_mirror(plane) led_cube(MIRROR, plane, 0, blank_buffer);delay(WRITE_TIME)
#define clear_tanslate() led_cube(TRANSLATE_CLEAR, 0, 0, blank_buffer);delay(WRITE_TIME)
#define cube_translate(ax, dir, buf) led_cube(TRANSLATE, ax, dir, buf);delay(WRITE_TIME)
#define cube_activate() led_cube(ACTIVATE, 0, 0, blank_buffer);delay(WRITE_TIME)
#define cube_deactivate() led_cube(DEACTIVATE, 0, 0, blank_buffer);delay(WRITE_TIME)

#endif /* CAN_H_ */
