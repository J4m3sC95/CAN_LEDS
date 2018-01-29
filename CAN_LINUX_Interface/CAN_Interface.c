#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* baudrate settings are defined in <asm/termbits.h>, which is
included by <termios.h> */
#define BAUDRATE B9600  
/* change this definition for the correct port */
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE; 

int main()
{
	int fd, res;
	struct termios oldtio,newtio;
	char buf[255];
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
	 char data = 'a';

	 while (STOP==FALSE) {		 
		 buf[0] = data;
		 buf[1] = '\n';
		 write(fd, buf, 2);
		 data++;
		res = read(fd,buf,255); 
		buf[res]=0;             /* set end of string, so we can printf */
		printf("%s", buf);
		if (buf[0]=='z') STOP=TRUE;
	 }
	 /* restore the old port settings */
	 tcsetattr(fd,TCSANOW,&oldtio);
	 
	 return 0;
}
