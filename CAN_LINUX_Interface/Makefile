CC=gcc
CFLAGS=-Wall

all: CAN_Interface.exe

CAN_Interface.exe:  CAN_Interface.c Serial.o gtk.o
	$(CC) -o CAN_Interface.exe CAN_Interface.c Serial.o gtk.o $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` 

Serial.o: Serial.c Serial.h
	$(CC) -c -o Serial.o Serial.c $(CFLAGS)
	
gtk.o: gtk.c gtk.h
	$(CC) -c -o gtk.o gtk.c $(CFLAGS)
