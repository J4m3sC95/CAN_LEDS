/*
 * spi.h
 *
 * Created: 18/02/2018 14:04:09
 *  Author: James
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "main.h"

#define CHIP_ENABLE()	PORTA->OUTCLR.reg = SS_PORT
#define CHIP_DISABLE()	PORTA->OUTSET.reg = SS_PORT;

#define SPI ((SercomSpi *)SERCOM1)

void spiSetup();
uint8_t spiTransfer(uint8_t data);

#endif /* SPI_H_ */