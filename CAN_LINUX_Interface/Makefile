CC=gcc
CFLAGS=-Wall

all: CAN_Interface

CAN_Interface:  CAN_Interface.c
	$(CC) -o CAN_Interface CAN_Interface.c $(CFLAGS)
# this is for future use when gtk+ is used
#$(CC) -o CAN_Interface CAN_Interface.c $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` 

clean:
	rm -f CAN_Interface
