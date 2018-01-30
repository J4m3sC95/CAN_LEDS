#include "gtk_interface.h"
#include "Serial.h"

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

void gtk_initialise(int argc, char *argv[]){
	gtk_init(&argc, &argv);
}

void gtk_build_window(){
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "CAN Interface");
	gtk_window_set_default_size(GTK_WINDOW(window), 300,200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	
	icon = create_pixbuf("led_red.png");  
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	
	// Button 1
	button = gtk_button_new_with_label("Button");
	halign = gtk_alignment_new(0, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(halign), button);
	gtk_container_add(GTK_CONTAINER(window), halign);  
}

void gtk_set_callbacks(){
	g_signal_connect(button, "clicked",  G_CALLBACK(send_bytes), NULL);
}

void gtk_run(){
	gtk_widget_show_all(window);  
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
	gtk_main();	
	g_object_unref(icon); 
}

void send_bytes(GtkWidget *widget, gpointer window){
	buf[0] = 'a';
	buf[1] = 'b';
	buf[2] = '\n';
	serWrite(buf, 3);
	res = serRead(buf,255); 
	buf[res]=0;
	printf("%s", buf);
 }
