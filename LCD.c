/*
 * LCD.c
 *
 *  Created on: Oct 22, 2013
 *      Author: C15Alex.Strom
 */
#include <msp430.h>
#include "lcdwrite.h"

#define RS_MASK 0x40

void writeDataByte(char dataByte);
void writeCommandNibble(char commandNibble);
void writeCommandByte(char commandByte);
void SPI_send(char byteToSend);
void delayMICRO();
void delayMilli();
void LCD_write_4(char byteToSend);
void LCD_write_8(char byteToSend);

char LCDCON = 0;

void delayMicro(){
	_delay_cycles(42);
}

void delayMilli(){
	_delay_cycles(1648);
}

void set_SS_hi(){
	//P1DIR |= BIT0;
	P1OUT |= BIT0;}

void set_SS_lo(){
	//P1DIR |= BIT0;
	P1OUT &= ~BIT0;}

void initSPI(){
	UCB0CTL1 |=UCSWRST;

	UCB0CTL0|= UCCKPL|UCMSB|UCMST|UCSYNC;

	UCB0CTL1 |= UCSSEL1;

	P1DIR |=BIT0;

	set_SS_hi();

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;

	P1SEL |= BIT6;
	P1SEL2 |= BIT6;

	UCB0CTL1 &= ~UCSWRST;
}

void LCDinit()
{
    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x03);

    writeCommandNibble(0x02);

    writeCommandByte(0x28);

    writeCommandByte(0x0C);

    writeCommandByte(0x01);

    writeCommandByte(0x06);

    writeCommandByte(0x01);

    writeCommandByte(0x02);

    SPI_send(0);
    delayMicro();
}


void LCDclear()
{
    writeCommandByte(1);
}

void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCD_write_4(commandNibble);
    delayMilli();
}

void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCD_write_8(commandByte);
    delayMilli();
}


void SPI_send(char byteToSend)
{
    volatile char readByte;

    set_SS_lo();

    UCB0TXBUF = byteToSend;

    while(!(UCB0RXIFG & IFG2))
    {
        // wait until you've received a byte
    }

    readByte = UCB0RXBUF;

    set_SS_hi();
}


void LCD_write_8(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0xF0;

    sendByte = sendByte >> 4;               // rotate to the right 4 times

    LCD_write_4(sendByte);

    sendByte = byteToSend;

    sendByte &= 0x0F;

    LCD_write_4(sendByte);
}


void LCD_write_4(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0x7F;

    sendByte |=LCDCON;

    SPI_send(sendByte);

    delayMicro();

    sendByte |= 0X80;

    SPI_send(sendByte);

    delayMicro();

    sendByte &= 0x7F;

    SPI_send(sendByte);

    delayMicro();
}


void cursorToLineTwo(){
		writeCommandByte(0XC0);
}

void cursorToLineOne(){
		writeCommandByte(0x80);
}
void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCD_write_8(dataByte);
    delayMilli();
}

void writeString(char string[], char length){
	char i = 0;
	for(i = 0; i < length; i++){
		writeDataByte(string[i]);
	}
}

void scrollString( char string[], int stringLength ){
	int i = 0;
	int tempChar = string[0];
	for( i=0; i < stringLength; i++ )
	{
		string[i] = string[i+1];
	}
	string[stringLength-1] = tempChar;
}
