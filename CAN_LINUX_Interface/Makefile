CC=gcc
CFLAGS=-Wall

all: CAN_Interface.exe
	cp CAN_Interface.exe ~/bin/CAN
	cp led_red.png ~/bin/led_red.png

CAN_Interface.exe:  CAN_Interface.c Serial.o gtk_interface.o
	$(CC) -o CAN_Interface.exe CAN_Interface.c Serial.o gtk_interface.o $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` 

Serial.o: Serial.c Serial.h
	$(CC) -c -o Serial.o Serial.c $(CFLAGS)
	
gtk_interface.o: gtk_interface.c gtk_interface.h
	$(CC) -c -o gtk_interface.o gtk_interface.c $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` 
