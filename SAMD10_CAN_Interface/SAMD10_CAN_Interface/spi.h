/*
 * spi.h
 *
 * Created: 18/02/2018 14:04:09
 *  Author: James
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "main.h"

#define CHIP_ENABLE()	porta->OUTCLR.reg = SS_PORT
#define CHIP_DISABLE()	porta->OUTSET.reg = SS_PORT;

void spiSetup();
uint8_t spiTransfer(uint8_t data);

#endif /* SPI_H_ */