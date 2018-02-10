#ifndef GTK_INTERFACE_H_
#define GTK_INTERFACE_H_

#include <gtk/gtk.h>

// Objects
GtkWidget *window;
GdkPixbuf *icon;
GtkWidget *controlNotebook;
GtkWidget *ledCubeControlTable;
GtkWidget *ledCubeControlTableLabelVbox;	
GtkWidget *commandLabel;
GtkWidget *arg1Label;
GtkWidget *arg2Label;
GtkWidget *ledCubeControlTableControlVbox;
GtkWidget *CommandComboBox;
GtkWidget *Arg1ComboBox;
GtkWidget *Arg1SpinButton;
GtkWidget *Arg2ComboBox;
GtkWidget *Arg2SpinButton;
GtkWidget *ledNotebook;
GtkWidget *ledTabTable[3];
GtkWidget *ledCheckButton[3][10];
GtkWidget *LayerLabel[3];
GtkWidget *ledCubeControlTableButtonVbox;
GtkWidget *ActivateButton;
GtkWidget *StartWriteButton;
GtkWidget *SendButton;
GtkWidget *ledCubeControlTabLabel;
GtkWidget *SerialConnectButton;
GtkWidget *SerialStatusLabel;
GtkWidget *SerialTestButton;
GtkWidget *SerialHbox;
GtkWidget *SerialOutputLabel;
GtkWidget *SerialOutputLabelHalign;
GtkWidget *SerialOutputTextBox;
GtkWidget *WindowLayoutTable;


// function prototypes
GdkPixbuf *create_pixbuf(const gchar * filename) ;
void gtk_initialise(int argc, char *argv[]);
void gtk_build_window();
void gtk_set_callbacks();
void gtk_run();
void send_bytes(GtkWidget *widget, gpointer window);
void SerialConnectCallback(GtkWidget *widget, gpointer window);

#endif /* GTK_INTERFACE_H_ */
