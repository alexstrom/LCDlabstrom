/*
 * lcdwrite.h
 *
 *  Created on: Oct 22, 2013
 *      Author: C15Alex.Strom
 */
#include <msp430.h>
#ifndef _LCDWRITE_H_
#define _LCDWRITE_H_

void initSPI();

void LCDinit();

void LCDclear();

void cursorToLineTwo();

void cursorToLineOne();

void writeChar(char asciiChar);

void writeString(char string[], char length);

void scrollString( char string[], int stringLength );

//void writeCommandNibble();

//void writeCommandByte();

//void SPI_send();


#endif /* LCDWRITE_H_ */
