#ifndef GTK_INTERFACE_H_
#define GTK_INTERFACE_H_

#include <gtk/gtk.h>
#include <string.h>
#include "Serial.h"

// defines for different effect functions
#define LOAD_CMD					0
#define ROTATE_CMD					1
#define MIRROR_CMD					2
#define TRANSLATE_CMD				3
#define TRANSLATE_CLEAR_CMD			4
#define EEPROM_WRITE_BEGIN_CMD		5
#define EEPROM_WRITE_END_CMD		6
#define ACTIVATE_CMD				7
#define DEACTIVATE_CMD				8
#define LOOP_CMD					9
#define DELAY_CMD					10

// Objects
GtkWidget *window;
GdkPixbuf *icon;
GtkWidget *controlNotebook;
GtkWidget *ledCubeControlTable;
GtkWidget *ledCubeControlTableLabelVbox;	
GtkWidget *commandLabel;
GtkWidget *arg1Label;
GtkWidget *arg2Label;
GtkWidget *commandLabelHalign;
GtkWidget *arg1LabelHalign;
GtkWidget *arg2LabelHalign;
GtkWidget *ledCubeControlTableControlVbox;
GtkWidget *CommandComboBox;
GtkWidget *Arg1Control;
GtkWidget *Arg2Control;
GtkWidget *ledNotebook;
GtkWidget *ledTabTable[4];
GtkWidget *ledCheckButton[4][10];
GtkWidget *LayerLabel[4];
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
void SerialConnectCallback(GtkWidget *widget, gpointer window);
void CommandComboBox_changed_callback(GtkWidget *widget, gpointer window);
void ActivateButton_clicked_callback(GtkWidget *widget, gpointer window);
void StartWriteButton_clicked_callback(GtkWidget *widget, gpointer window);
void SendButton_clicked_callback(GtkWidget *widget, gpointer window);
void SerialTestButton_clicked_callback(GtkWidget *widget, gpointer window);

#endif /* GTK_INTERFACE_H_ */
