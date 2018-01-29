#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gtk/gtk.h>

#define BAUDRATE B9600  
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1

volatile int STOP=FALSE; 

int fd, res;
	struct termios oldtio,newtio;
	char buf[255];

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

GdkPixbuf *create_pixbuf(const gchar * filename) {
    
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   
   if (!pixbuf) {
       
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

void send_bytes(GtkWidget *widget, gpointer window){
	buf[0] = 'a';
	buf[1] = 'b';
	 buf[2] = '\n';
	 write(fd, buf, 2);
	 res = read(fd,buf,255); 
	buf[res]=0;
	printf("%s", buf);
 }

int main(int argc, char *argv[])
{
	serial_setup();
	
	GtkWidget *window;
	GtkWidget *halign;
	GtkWidget *button;
	GdkPixbuf *icon;
	
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "CAN Interface");
	gtk_window_set_default_size(GTK_WINDOW(window), 300,200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	icon = create_pixbuf("led_red.png");  
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	
	button = gtk_button_new_with_label("Button");
	
	halign = gtk_alignment_new(0, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(halign), button);
	gtk_container_add(GTK_CONTAINER(window), halign);  
	
	g_signal_connect(button, "clicked",  G_CALLBACK(send_bytes), NULL); 
	
	gtk_widget_show_all(window);
  
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
	

	gtk_main();
	
	g_object_unref(icon);    	
	
	 char data = 'b';

	 while (STOP==FALSE) {		 
		 buf[0] = data;
		 buf[1] = '\n';
		 write(fd, buf, 2);
		 data++;
		res = read(fd,buf,255); 
		buf[res]=0;
		printf("%s", buf);
		if (buf[0]=='z') STOP=TRUE;
	 }
	 // restore the old port settings
	 tcsetattr(fd,TCSANOW,&oldtio);
	 
	 return 0;
}
