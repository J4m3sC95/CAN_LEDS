#include "gtk_interface.h"

const char *ledCubeCommands[8] = {"LOAD", "ROTATE","MIRROR", "TRANSLATE", "TRANSLATE CLEAR", "LOOP", "DELAY"};
const char *ledCubeAxisArgs[4] = {"X-Axis", "Y-Axis", "Z-Axis"};
const char *ledCubeDirectionArgs[3] = {"Positive", "Negative"};
const char *ledCubePlaneArgs[4] = {"YZ Plane", "ZX Plane", "XY Plane"};

uint16_t blank_buffer[] = {0,0,0};

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
	ledCubeControlTable = gtk_table_new(1,4,FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(ledCubeControlTable), 6);
	// vbox for labels and buttons in columns 1, 2 and 4
	//column 1 labels
	ledCubeControlTableLabelVbox = gtk_vbox_new(TRUE,1);

	commandLabel = gtk_label_new("      Command");
	arg1Label = gtk_label_new("");
	arg2Label = gtk_label_new("");
	
	commandLabelHalign = gtk_alignment_new(1,0,0,0);
	arg1LabelHalign = gtk_alignment_new(1,0,0,0);
	arg2LabelHalign = gtk_alignment_new(1,0,0,0);
	
	gtk_container_add(GTK_CONTAINER(commandLabelHalign), commandLabel);
	gtk_container_add(GTK_CONTAINER(arg1LabelHalign), arg1Label);
	gtk_container_add(GTK_CONTAINER(arg2LabelHalign), arg2Label);
	
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableLabelVbox), commandLabelHalign, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableLabelVbox), arg1LabelHalign, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ledCubeControlTableLabelVbox), arg2LabelHalign, TRUE, TRUE, 0);
	
	gtk_table_attach(GTK_TABLE(ledCubeControlTable), ledCubeControlTableLabelVbox, 0, 1,0,1, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 6,0) ;
	
	// Column 2 control boxes
	ledCubeControlTableControlVbox = gtk_vbox_new(TRUE,1);
	
	CommandComboBox = gtk_combo_box_new_text();
	for(n=0; n<7;n++){
		gtk_combo_box_append_text(GTK_COMBO_BOX(CommandComboBox), ledCubeCommands[n]);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(CommandComboBox), 0);
	
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
	SerialOutputLabel = gtk_label_new("Received Serial Data:");
	SerialOutputLabelHalign = gtk_alignment_new(0,0,0,0);
	
	gtk_container_add(GTK_CONTAINER(SerialOutputLabelHalign), SerialOutputLabel);
	
	// Serial Output Text Box	
	SerialOutputHbox = gtk_hbox_new(FALSE, 1);
	SerialOutputTextBox = gtk_entry_new();
	SerialOutputClearButton = gtk_button_new_with_label("   Clear   ");
	
	gtk_box_pack_start(GTK_BOX(SerialOutputHbox), SerialOutputTextBox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(SerialOutputHbox), SerialOutputClearButton, FALSE,FALSE, 0);
	
	// Overall Window Layout Table	
	WindowLayoutTable = gtk_table_new(4,1,FALSE);
	
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), SerialHbox, 0,1,0,1, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), controlNotebook, 0,1,1,2, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), SerialOutputLabelHalign, 0,1,2,3, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	gtk_table_attach(GTK_TABLE(WindowLayoutTable), SerialOutputHbox, 0,1,3,4, GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL, 0,3) ;
	
	// add the table to the window	
	gtk_container_add(GTK_CONTAINER(window),WindowLayoutTable);
}

void gtk_run(){
	gtk_widget_show_all(window);  
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
	gtk_main();	
	g_object_unref(icon); 
}

void gtk_set_callbacks(){
	g_signal_connect(SerialConnectButton, "clicked",  G_CALLBACK(SerialConnectCallback), NULL);
	g_signal_connect(CommandComboBox, "changed", G_CALLBACK(CommandComboBox_changed_callback), NULL);
	g_signal_connect(ActivateButton, "clicked", G_CALLBACK(ActivateButton_clicked_callback), NULL);
	g_signal_connect(StartWriteButton, "clicked", G_CALLBACK(StartWriteButton_clicked_callback), NULL);
	g_signal_connect(SendButton, "clicked", G_CALLBACK(SendButton_clicked_callback), NULL);
	g_signal_connect(SerialTestButton, "clicked", G_CALLBACK(SerialTestButton_clicked_callback), NULL);
	g_signal_connect(SerialOutputClearButton, "clicked", G_CALLBACK(SerialOutputClearButton_clicked_callback), NULL);
}

void SerialTestButton_clicked_callback(GtkWidget *widget, gpointer window){
	if(serial_connected){
		buf[0] = '<';
		buf[1] = '>';
		buf[2] = '\n';
		serWrite(buf, 3);
		res = serRead(buf,255); 
		buf[res-1]=0;
		printf("%s\n", buf);
		gtk_entry_set_text(GTK_ENTRY(SerialOutputTextBox), buf);
	}
	else{
		printf("Serial port not open!\n");
	}		
 }
 
 void SerialConnectCallback(GtkWidget *widget, gpointer window){
	 if(!serial_connected){
		 serial_setup();
		 gtk_label_set_text(GTK_LABEL(SerialStatusLabel), "Connected");
		 gtk_button_set_label(GTK_BUTTON(SerialConnectButton), "Disconnect");
		 printf("Connected\n");
	 }
	 else
	 {
		 serial_cleanup();
		 gtk_label_set_text(GTK_LABEL(SerialStatusLabel), "Disconnected");
		 gtk_button_set_label(GTK_BUTTON(SerialConnectButton), "Connect");
		 printf("Disconnected\n");
	 }	 
 }
 
 void CommandComboBox_changed_callback(GtkWidget *widget, gpointer window){
	 int n;
	 
	 gint command_index = gtk_combo_box_get_active(GTK_COMBO_BOX(CommandComboBox));	 
	 printf("Command Selected = %d: %s\n", command_index, ledCubeCommands[command_index]);
	 
	 gtk_widget_destroy(Arg1Control);
	 gtk_widget_destroy(Arg2Control);
	 
	 switch(command_index){
		 case LOAD_CMD :
		 case TRANSLATE_CLEAR_CMD:
		 {
			 gtk_label_set_text(GTK_LABEL(arg1Label),"");
			 gtk_label_set_text(GTK_LABEL(arg2Label),"");			
			 Arg1Control = gtk_label_new("");
			 Arg2Control = gtk_label_new("");
		 }
		 break;
		 case ROTATE_CMD:
		 case TRANSLATE_CMD:
		 {
			 gtk_label_set_text(GTK_LABEL(arg1Label),"Axis");
			 gtk_label_set_text(GTK_LABEL(arg2Label),"Direction");
			 Arg1Control = gtk_combo_box_new_text();
			 for(n = 0; n<3; n++){
				 gtk_combo_box_append_text(GTK_COMBO_BOX(Arg1Control), ledCubeAxisArgs[n]);
			 }
			 gtk_combo_box_set_active(GTK_COMBO_BOX(Arg1Control), 0);
			 Arg2Control = gtk_combo_box_new_text();
			 for(n = 0; n<2; n++){
				 gtk_combo_box_append_text(GTK_COMBO_BOX(Arg2Control), ledCubeDirectionArgs[n]);
			 }
			 gtk_combo_box_set_active(GTK_COMBO_BOX(Arg2Control), 0);			 
		 }
		 break;
		 case MIRROR_CMD:
		 {
			 gtk_label_set_text(GTK_LABEL(arg1Label),"Plane");
			 gtk_label_set_text(GTK_LABEL(arg2Label),"");
			 Arg1Control = gtk_combo_box_new_text();
			 for(n = 0; n<3; n++){
				 gtk_combo_box_append_text(GTK_COMBO_BOX(Arg1Control), ledCubePlaneArgs[n]);
			 }
			 gtk_combo_box_set_active(GTK_COMBO_BOX(Arg1Control), 0);
			 Arg2Control = gtk_label_new("");
		 }
		 break;
		 case (LOOP_CMD - 4):
		 {
			 gtk_label_set_text(GTK_LABEL(arg1Label),"Instructions");
			 gtk_label_set_text(GTK_LABEL(arg2Label),"Loops");
			 Arg1Control = gtk_spin_button_new_with_range(0,255,1);
			 Arg2Control = gtk_spin_button_new_with_range(0,255,1);
		 }
		 break;
		 case (DELAY_CMD - 4):
		 {
			 gtk_label_set_text(GTK_LABEL(arg1Label),"Time [ms]");
			 gtk_label_set_text(GTK_LABEL(arg2Label),"");
			 Arg1Control = gtk_spin_button_new_with_range(0,255,1);
			 Arg2Control = gtk_label_new("");
		 }
		 break;
	 }
	 
	 gtk_box_pack_start(GTK_BOX(ledCubeControlTableControlVbox), Arg1Control, TRUE, TRUE, 0);
	 gtk_box_pack_start(GTK_BOX(ledCubeControlTableControlVbox), Arg2Control, TRUE, TRUE, 0);
	 gtk_widget_show(Arg1Control);
	 gtk_widget_show(Arg2Control);	 
 }

void ActivateButton_clicked_callback(GtkWidget *widget, gpointer window){
	uint8_t command;
	const gchar *button_label = gtk_button_get_label(GTK_BUTTON(ActivateButton));
	printf("%s\n", button_label);
	if(strcmp(button_label, "Activate") == 0){
		gtk_button_set_label(GTK_BUTTON(ActivateButton), "Deactivate");
		command = ACTIVATE_CMD;
	}
	else{
		gtk_button_set_label(GTK_BUTTON(ActivateButton), "Activate");
		command = DEACTIVATE_CMD;
	}
	
	if(serWriteCommand(command, 0,0,blank_buffer)){
		gtk_entry_set_text(GTK_ENTRY(SerialOutputTextBox), buf);
	}
}

void StartWriteButton_clicked_callback(GtkWidget *widget, gpointer window){	
	uint8_t command;
	const gchar *button_label = gtk_button_get_label(GTK_BUTTON(StartWriteButton));
	printf("%s\n", button_label);
	if(strcmp(button_label, "Start Write") == 0){
		gtk_button_set_label(GTK_BUTTON(StartWriteButton), "Stop Write");
		command = EEPROM_WRITE_BEGIN_CMD;
	}
	else{
		gtk_button_set_label(GTK_BUTTON(StartWriteButton), "Start Write");
		command = EEPROM_WRITE_END_CMD;
	}
	
	if(serWriteCommand(command, 0,0,blank_buffer)){
		gtk_entry_set_text(GTK_ENTRY(SerialOutputTextBox), buf);
	}
}

void SendButton_clicked_callback(GtkWidget *widget, gpointer window){
	int n, m;
	uint8_t command_index = 0;
	uint8_t arg1 = 0;
	uint8_t arg2 = 0;
	uint16_t cube_buffer[] = {0,0,0};
	
	// get the led number data
	for(n = 0; n<3; n++){
		for(m = 0; m< 9; m++){
			if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ledCheckButton[n][m]))){
				cube_buffer[n] |= (1<<m);
			}
		}
	}
	
	// determine which command index is selected
	command_index = gtk_combo_box_get_active(GTK_COMBO_BOX(CommandComboBox));
	 
	 // switch case to get arg1 and arg2
	 switch(command_index){
		 case ROTATE_CMD:
		 case TRANSLATE_CMD:
		 {
			 arg2 = gtk_combo_box_get_active(GTK_COMBO_BOX(Arg2Control));
		 }			 
		 case MIRROR_CMD:
		 {
			 arg1 = gtk_combo_box_get_active(GTK_COMBO_BOX(Arg1Control));
		 }
		 break;
		 case (LOOP_CMD - 4):
		 {
			 arg2 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Arg2Control));
		 }
		 case (DELAY_CMD - 4):
		 {
			 arg1 = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Arg1Control));
		 }
		 break;
	 }
	 
	 if(serWriteCommand(command_index, arg1, arg2, cube_buffer)){
		 gtk_entry_set_text(GTK_ENTRY(SerialOutputTextBox), buf);
	 }
}

void SerialOutputClearButton_clicked_callback(GtkWidget *widget, gpointer window){
	gtk_entry_set_text(GTK_ENTRY(SerialOutputTextBox), "");
}
