#include <msp430.h>
#include "lcdwrite.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    configureP1PinAsButton(BIT1|BIT2|BIT3);
    P1DIR |= BIT0|BIT6;

    char topline[]="Message?";
    char choice[]="Press123";
    char message[] = "ECE382 is my favorite class!";
    char message1[] = "Allonsy! ";
    char message2[] = "Geronimo! ";
    char message3[] = "The oncoming storm ";

    initSPI();  //Sets up LCD
    LCDinit();
    LCDclear();


    cursorToLineOne();
    writeString(topline,8);

    cursorToLineTwo();
    writeString(choice,8);


    while(1){
    	char buttons[] = {BIT1, BIT2, BIT3};
    	char pressedButton = pollP1Buttons(buttons, 3);

    	switch (pressedButton) {
    	case BIT1:
    		LCDclear();
    		cursorToLineOne();
    		writeString(message,8);

    		cursorToLineTwo();
    		writeString(message1,8);

    		_delay_cycles(1000000);

    		scrollString( message, 28);
    		scrollString( message1, 9);

    	break;

    	case BIT2:
    		LCDclear();
    		cursorToLineOne();
    		writeString(message,8);

    		cursorToLineTwo();
    		writeString(message2,8);

    		_delay_cycles(1000000);

    		scrollString( message, 28);
    		scrollString( message2, 10);

    	break;

    	case BIT3:
    		LCDclear();
    		cursorToLineOne();
    		writeString(message,8);

    		cursorToLineTwo();
    		writeString(message3,8);

    		_delay_cycles(1000000);

    		scrollString( message, 28);
    		scrollString( message3, 19);

    	}


    }
	return 0;
}

