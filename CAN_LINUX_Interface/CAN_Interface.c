#include <stdio.h>

#include "Serial.h"
#include "gtk_interface.h"

char buf[255];
int res;

volatile int STOP=FALSE; 

int main(int argc, char *argv[])
{
	gtk_initialise(argc, argv);
	gtk_build_window();
	gtk_set_callbacks();	
	gtk_run();   	
	
	/*
	char data = 'b';

	while (STOP==FALSE) {
		buf[0] = data;
		buf[1] = '\n';
		serWrite(buf, 2);
		data++;
		res = serRead(buf,255); 
		buf[res]=0;
		printf("%s", buf);
		if (buf[0]=='z') STOP=TRUE;
	}
	*/
	 
	serial_cleanup();
	 
	return 0;
}
