#ifndef SERIAL_H_
#define SERIAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BAUDRATE B9600  
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1

int fd;
struct termios oldtio,newtio;


void serial_setup();
char serRead(int fd, void *buf, size_t count);
void serWrite(int fd, void *buf, size_t count);
void serial_cleanup();

#endif /* SERIAL_H_ */