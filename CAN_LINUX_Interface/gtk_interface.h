#ifndef GTK_H_
#define GTK_H_

#include <gtk/gtk.h>

// Objects
GtkWidget *window;
GtkWidget *halign;
GtkWidget *button;
GdkPixbuf *icon;

// function prototypes
GdkPixbuf *create_pixbuf(const gchar * filename) ;
void gtk_initialise(int argc, char *argv[]);
void gtk_build_window();
void gtk_set_callbacks();
void gtk_run();
void send_bytes(GtkWidget *widget, gpointer window);

#endif /* SERIAL_H_ */
