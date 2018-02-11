#include "gtk_interface.h"
#include "Serial.h"

const char *ledCubeCommands[8] = {"LOAD", "ROTATE","MIRROR", "TRANSLATE", "TRANSLATE CLEAR", "LOOP", "DELAY"};

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
	int n,m;
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "CAN Interface");
	gtk_window_set_default_size(GTK_WINDOW(window), 300,200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	
	icon = create_pixbuf("led_red.png");  
	gtk_window_set_icon(GTK_WINDOW(window), icon);
	
	// LED Cube notebook tab
	// four column table
	ledCubeControlTable = gtk_table_new(1,4,TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(ledCubeControlTable), 6);
	// vbox for labels and buttons in columns 1, 2 and 4
	//column 1 labels
	ledCubeControlTableLabelVbox = gtk_vbox_new(TRUE,1);

	commandLabel = gtk_label_new("Command");
	arg1Label = gtk_label_new("");
	arg2Label = gtk_label_new("");
	
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableLabelVbox), commandLabel, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableLabelVbox), arg1Label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableLabelVbox), arg2Label, TRUE, TRUE, 0);
	
	gtk_table_attach(GTK_TABLE(ledCubeControlTable), ledCubeControlTableLabelVbox, 0, 1,0,1, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 6,0) ;
	
	// Column 2 control boxes
	ledCubeControlTableControlVbox = gtk_vbox_new(TRUE,1);
	
	CommandComboBox = gtk_combo_box_new_text();
	for(n=0; n<7;n++){
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(CommandComboBox), ledCubeCommands[n]);
	}
	/*
	gtk_combo_box_append_text(GTK_COMBO_BOX(CommandComboBox), "ROTATE");
	gtk_combo_box_append_text(GTK_COMBO_BOX(CommandComboBox), "MIRROR");
	gtk_combo_box_append_text(GTK_COMBO_BOX(CommandComboBox), "TRANSLATE");
	gtk_combo_box_append_text(GTK_COMBO_BOX(CommandComboBox), "TRANSLATE CLEAR");
	gtk_combo_box_append_text(GTK_COMBO_BOX(CommandComboBox), "LOOP");
	gtk_combo_box_append_text(GTK_COMBO_BOX(CommandComboBox), "DELAY");
	*/
	
	/*
	Arg1SpinButton = gtk_spin_button_new_with_range(0,100,1);
	Arg2SpinButton = gtk_spin_button_new_with_range(0,100,1);
	* */
	
	Arg1Control = gtk_label_new("");
	Arg2Control = gtk_label_new("");	
	
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableControlVbox), CommandComboBox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableControlVbox), Arg1Control, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableControlVbox), Arg2Control, TRUE, TRUE, 0);
	
	gtk_table_attach(GTK_TABLE(ledCubeControlTable), ledCubeControlTableControlVbox, 1, 2,0,1, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 6,0) ;
	
	// Column 3 notebook for selecting which LEDs are on	
	LayerLabel[0] = gtk_label_new("Layer0");
	LayerLabel[1] = gtk_label_new("Layer1");
	LayerLabel[2] = gtk_label_new("Layer2");	
	
	ledNotebook = gtk_notebook_new();
	for(n = 0; n<3; n++){
		ledTabTable[n] = gtk_table_new(3,3,FALSE);
		gtk_notebook_append_page(GTK_NOTEBOOK(ledNotebook), ledTabTable[n], LayerLabel[n]);
	}
		
	char checkLabel[10];
	
	for(n = 0; n < 3; n++){
		for(m = 0; m<9; m++){
			sprintf(checkLabel,"%d", m);
			ledCheckButton[n][m] = gtk_check_button_new_with_label(checkLabel);
			gtk_table_attach_defaults(GTK_TABLE(ledTabTable[n]), ledCheckButton[n][m], m%3, (m%3)+1,2-(m/3),(2-(m/3))+1) ;
		}
	}
	
	gtk_table_attach(GTK_TABLE(ledCubeControlTable), ledNotebook, 2,3,0,1, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 6,0) ;	
	
	// Column 4 for the buttons	
	ledCubeControlTableButtonVbox = gtk_vbox_new(TRUE,1);
	
	ActivateButton = gtk_button_new_with_label("Activate");
	StartWriteButton = gtk_button_new_with_label("Start Write");
	SendButton = gtk_button_new_with_label("Send");
	
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableButtonVbox), ActivateButton, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableButtonVbox), StartWriteButton, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableButtonVbox), SendButton, TRUE, TRUE, 0);
	
	gtk_table_attach(GTK_TABLE(ledCubeControlTable), ledCubeControlTableButtonVbox, 3, 4,0,1, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 6,0) ;
	
	// control notebook for showing the different controls for different devices
	ledCubeControlTabLabel = gtk_label_new("LED Cube");
	
	controlNotebook = gtk_notebook_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(controlNotebook), ledCubeControlTable, ledCubeControlTabLabel);
	
	// Device Connection Stuff	
	SerialConnectButton = gtk_button_new_with_label("Connect");
	SerialStatusLabel = gtk_label_new("Disconnected");
	SerialTestButton = gtk_button_new_with_label("Test");
	
	SerialHbox = gtk_hbox_new(TRUE,1);
	
	gtk_box_pack_start(GTK_BOX(SerialHbox), SerialConnectButton, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(SerialHbox), SerialStatusLabel, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(SerialHbox), SerialTestButton, TRUE, TRUE, 0);
	
	// Serial Output Label	
	SerialOutputLabel = gtk_label_new("SerialOutput");
	SerialOutputLabelHalign = gtk_alignment_new(0,0,0,0);
	
	gtk_container_add(GTK_CONTAINER(SerialOutputLabelHalign), SerialOutputLabel);
	
	// Serial Output Text Box	
	SerialOutputTextBox = gtk_text_view_new();
	
	// Overall Window Layout Table	
	WindowLayoutTable = gtk_table_new(4,1,FALSE);
	
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), SerialHbox, 0,1,0,1, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), controlNotebook, 0,1,1,2, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), SerialOutputLabelHalign, 0,1,2,3, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), SerialOutputTextBox, 0,1,3,4, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	
	// add the table to the window	
	gtk_container_add(GTK_CONTAINER(window),WindowLayoutTable);
}

void gtk_set_callbacks(){
	g_signal_connect(SerialTestButton, "clicked",  G_CALLBACK(send_bytes), NULL);
	g_signal_connect(SerialConnectButton, "clicked",  G_CALLBACK(SerialConnectCallback), NULL);
	g_signal_connect(CommandComboBox, "changed", G_CALLBACK(CommandComboBox_changed_callback), NULL);
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
 
 void SerialConnectCallback(GtkWidget *widget, gpointer window){
	 serial_setup();
 }
 
 void CommandComboBox_changed_callback(GtkWidget *widget, gpointer window){
	 int n, command_index;
	 	 
	 gchar* command_string = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(CommandComboBox));
	 
	 for(n = 0; n<7; n++){
		 if(strcmp(command_string, ledCubeCommands[n]) == 0){
			 command_index = n;
			 n=10;
		 }
	 }
	 printf("Command Selected = %d\n", command_index);
 }
