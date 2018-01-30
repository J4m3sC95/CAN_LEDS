CC=gcc
CFLAGS=-Wall

all: CAN_Interface.exe

CAN_Interface.exe:  CAN_Interface.c Serial.o
	$(CC) -o CAN_Interface.exe CAN_Interface.c Serial.o $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` 

Serial.o: Serial.c Serial.h
	$(CC) -c -o Serial.o Serial.c $(CFLAGS)
