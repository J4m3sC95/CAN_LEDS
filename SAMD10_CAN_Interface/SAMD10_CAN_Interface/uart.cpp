/*
 * uart.cpp
 *
 * Created: 19/01/2018 17:50:41
 *  Author: James
 */ 

#include "uart.h"

static volatile PortGroup *porta = (PortGroup *)PORT;
static volatile SercomUsart *uart = (SercomUsart *)SERCOM0;

volatile bool commandReady = false;
volatile bool receivingCommand = false;
volatile int commandCount = 0;
volatile int buff[10];

char rxString[] = "Accepted!\n";
char rxFailString[] = "Command Rejected\n";

void serialSetup(){
	//setup tx pin to output
	porta->DIR.bit.DIR |= TX_PORT;
	
	//setup rx/tx pin multiplexers
	porta->PINCFG[TX_PIN].bit.PMUXEN=1;
	porta->PINCFG[RX_PIN].bit.PMUXEN=1;
	porta->PINCFG[RX_PIN].bit.INEN=1;
	
	porta->PMUX[RX_PIN/2].bit.PMUXO=PORT_PMUX_PMUXO_C_Val;
	porta->PMUX[TX_PIN/2].bit.PMUXE=PORT_PMUX_PMUXE_C_Val;
	
	//uart setup
	// select correct clock mode either external (0x0 default) or internal (0x1)
	uart->CTRLA.bit.MODE = 1;
	// select comms mode (asynchronous (default or synchronous))
	//uart->CTRLA.bit.CMODE = 0;
	// select sercom pads for rx and tx
	uart->CTRLA.bit.RXPO=3;
	uart->CTRLA.bit.TXPO=1;
	// select character size (8 = default)
	//uart->CTRLB.bit.CHSIZE = 0;
	// choose data order (MSB first = default)
	uart->CTRLA.bit.DORD = 1;
	// choose parity (none = default)
	// choose stop bit numbers (1 = default)
	//uart->CTRLB.bit.SBMODE = 0;
	// configure baud rate for 8MHz clock (9600)
	// BAUD = 65536*(1-(16*baud/8MHz))
	uart->BAUD.bit.BAUD = 64278;
	// enable transmitter/receiver
	uart->CTRLB.reg |= SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN;
	while(uart->SYNCBUSY.bit.CTRLB);
	// enable UART
	uart->CTRLA.bit.ENABLE = 1;
	while(uart->SYNCBUSY.bit.ENABLE);
	
	//enable interrupts
	uart->INTENSET.bit.RXC = 1;
	NVIC_EnableIRQ(SERCOM0_IRQn);
}

void serialWriteByte(uint8_t byte){
	uart->DATA.bit.DATA = byte;
	while(!uart->INTFLAG.bit.DRE);
}

void serialPrint(char *buffer, uint16_t char_count){
	uint16_t n;
	for(n = 0; n <char_count; n++){
		serialWriteByte(buffer[n]);
	} 
}

void serialPrintString(char *buffer){
	uint16_t n = 0;
	while(buffer[n] != 0){
		serialWriteByte(buffer[n]);
		n++;
	}
}

// function for receiving data through polling
char serialReceive(){
	while(!uart->INTFLAG.bit.RXC);
	return uart->DATA.bit.DATA;
}

command serialReceiveCommand(){
	int n, temparg1, temparg2;
	command output;
	while(!commandReady);
	output.raw.commandID = buff[0];
	output.raw.arg1 = buff[1];
	output.raw.arg2 = buff[2];
	for(n = 0; n< 6; n++){
		output.CANdata[n+2] = buff[n+3];
	}
	
	temparg1 = output.raw.arg1;
	temparg2 = output.raw.arg2;
	
	serialPrintString((char *)"Command=");
	serialWriteByte(output.raw.commandID + 48);
	serialPrintString((char *)", Arg1=");
	serialWriteByte(temparg1 + 48);
	serialPrintString((char *)", Arg2=");
	serialWriteByte(temparg2 + 48);
	
	serialPrintString((char *)", LED Layers=");
	
	for(n = 0; n< 3; n++){
		serialWriteByte((output.raw.led_buff[n] / 100) + 48);
		serialWriteByte(((output.raw.led_buff[n] / 10)%10)+48);
		serialWriteByte((output.raw.led_buff[n] % 10)+48);
		if(n == 2){
			serialPrintString((char *)": ");
		}
		else{
			serialWriteByte((uint8_t)',');
		}
	}
	
	serialPrintString(rxString);
	
	commandReady = false;
	
	return output;	
}

// interrupt handler for receiving data
void SERCOM0_Handler(){
	uint8_t data = uart->DATA.bit.DATA;
	//serialWriteByte(data);
	porta->OUTTGL.reg = LED_PORT;
	if(!commandReady){		
		if((!receivingCommand) && (data == '<')){
			receivingCommand = true;
			commandCount = 0;
		}
		else if(receivingCommand && (data == '>')){
			receivingCommand = false;
			if(commandCount == 9){
				commandReady = true;
			}
			else{
				commandReady = false;
				serialPrintString(rxFailString);
			}			
		}
		else if(receivingCommand && (data != ',')){
			buff[commandCount] = data;
			commandCount++;
		}
	}	
}
