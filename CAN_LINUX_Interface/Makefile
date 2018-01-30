CC=gcc
CFLAGS=-Wall

all: CAN_Interface

CAN_Interface:  CAN_Interface.c Serial.c Serial.h
	$(CC) -o CAN_Interface CAN_Interface.c Serial.c $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` 

clean:
	rm -f CAN_Interface
