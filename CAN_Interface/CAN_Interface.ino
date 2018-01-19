#include "CAN.h"

// Definitions for setting the led cube config
#define WRITE_TIME 100

#define eeprom_write(n) led_cube(n, 0, 0, blank_buffer);delay(WRITE_TIME) 
#define load_buffer(x) led_cube(LOAD, 0, 0, x); delay(WRITE_TIME)
#define cube_delay(x) led_cube(DELAY, x, 0, blank_buffer); delay(WRITE_TIME)
#define cube_rotate(ax, dir) led_cube(ROTATE, ax, dir, blank_buffer); delay(WRITE_TIME)
#define cube_loop(inst, cnt) led_cube(LOOP, inst, cnt, blank_buffer);delay(WRITE_TIME)
#define cube_mirror(plane) led_cube(MIRROR, plane, 0, blank_buffer);delay(WRITE_TIME)
#define clear_tanslate() led_cube(TRANSLATE_CLEAR, 0, 0, blank_buffer);delay(WRITE_TIME)
#define cube_translate(ax, dir, buf) led_cube(TRANSLATE, ax, dir, buf);delay(WRITE_TIME)
#define cube_activate() led_cube(ACTIVATE, 0, 0, blank_buffer);delay(WRITE_TIME)
#define cube_deactivate() led_cube(DEACTIVATE, 0, 0, blank_buffer);delay(WRITE_TIME)

// buffers for storing cube patterns
uint16_t test_buffer[4] = {0x1F0, 0x1F0, 0x1F0};
uint16_t test_buffer1[4] = {0x0145, 0x00, 0x0145};
uint16_t blank_buffer[4] = {0,0,0};

void setup() {  
  // setup onboard LED for status indication
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // setup can
  CAN_setup();
  //indicate when the can is setup
  digitalWrite(LED_BUILTIN, HIGH);

  // write effects to LED cube eeprom
  eeprom_write(EEPROM_WRITE_BEGIN);
  // load buffer
  load_buffer(test_buffer);
  cube_delay(1000);
  //rotate 20 times
  cube_rotate(ZAXIS, NEGATIVE);
  cube_delay(100);
  cube_loop(2, 19);
  cube_delay(2000);
  // mirror 10 times
  cube_mirror(YZPLANE);
  cube_delay(100);
  cube_loop(2,9);
  cube_delay(2000);
  // translate a new buffer in
  clear_tanslate();
  cube_translate(XAXIS, POSITIVE, test_buffer1);
  cube_delay(1000);
  cube_loop(2,2);
  cube_delay(1000);
  eeprom_write(EEPROM_WRITE_END);

  // indicate write has finished
  digitalWrite(LED_BUILTIN, LOW);  
}

void loop();


