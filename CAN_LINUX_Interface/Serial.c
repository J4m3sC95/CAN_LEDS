#include "Serial.h"

void serial_setup(){
	//  Open modem device for reading and writing and not as controlling tty  because we don't want to get killed if linenoise sends CTRL-C.
	 fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY ); 
	 if (fd <0) {perror(MODEMDEVICE); exit(-1); }
	 
	 // save current port settings to reinstate later and clear struct for new settings
	 tcgetattr(fd,&oldtio); 
	 memset(&newtio, 0, sizeof(newtio)); 

	 //CS8 (8bit,no parity,1 stopbit) CLOCAL (local connection, no modem contol) CREAD (enable receiving characters)
	 newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
	 
	// IGNPAR  : ignore bytes with parity errors,  ICRNL   : map CarriageReturn to NewLine
	 newtio.c_iflag = IGNPAR | ICRNL;
	 
	 //ICANON  : enable canonical input disable all echo functionality, and don't send signals to calling program
	 newtio.c_lflag = ICANON;
	 
	// initialize all control characters  default values can be found in /usr/include/termios.h, and are given in the comments, but we don't need them here
	 newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
	 newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */

	// now clean the modem line and activate the settings for the port
	 tcflush(fd, TCIFLUSH);
	 tcsetattr(fd,TCSANOW,&newtio);
 }
 
 char serRead(void *buf, size_t count){
	 return read(fd, buf, count);
 }
 
 void serWrite(void *buf, size_t count){
	 write(fd, buf, count);
 }
 
 void serial_cleanup(){
	// restore the old port settings
	tcsetattr(fd,TCSANOW,&oldtio);
 }