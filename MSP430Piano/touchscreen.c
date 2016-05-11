/*
 * This file contains all the functions required to use the touchscreen. A resistive touscreen has four output
 * wires: X+,X-,Y+ and Y-. These are conected to the MSP430 GPIO pins and the pins need to be configured differently
 * for the three main functions required to interface the touchscreen:
 *  1.init_touchscreen(): This function initializes the GPIO pin to detect touch.
 *  2.init_read_y(): This function initilzies the GPIO pin to read the Y coordinate
 *  2. init_read_x(): This function initializes the GPIO pins to read the X coordinate.
 *
 *  The order of operation is:
 *  Initialize touchscreen-> if touch is detected then init_read_y()-> init_read_x()->Initialize touchscreen(reset)
 */

asm(" .length 10000");
asm(" .width 132");
#include <msp430g2553.h>

//Define global variables to connect the outputs of the touchscreen to the MSP430
#define RED 0x01		//red led is P1.0
#define Xplus 0x02		//X+ is P1.1
#define Xminus 0x04 	//X- is P1.2
#define Yplus 0x08		//Y+ is P1.3
#define Yminus 0x10		//Y- is p1.4


void init_touchscreen(){
	//This function initializes the GPIO pins to be able to detect touch.

	P1DIR|=Yminus;							//set Y- to output
	P1OUT&=~Yminus;							//Y- is output 0

	P1DIR &= ~Xplus;						// X+ is an input
	P1REN |= Xplus;							// Activate pullup resistors on X+ Pin

	P1DIR &= ~Yplus;						// Y+ is an input
	P1OUT |= Yplus;

	P1DIR &= ~Xminus;						// X- is an input
	P1OUT |= Xminus;
}

void init_read_x(){
	//This function initializes the GPIO pins to read the X coordinate

	P1DIR|=Xplus;							//set X+ to output
	P1OUT|=Xplus;							//X+ is output 1

	P1DIR |= Xminus;						// X- is an output
	P1OUT &= ~Xminus;

	P1DIR &= ~Yminus;						// Y- is an input
	P1OUT |= Yminus;

	P1DIR &= ~Yplus;						// Y+ is ADC input
	P1OUT |= Yplus;
}

void init_read_y(){
	//This function initializes the GPIO pins to be able to read the Y coordinate of touch.

	P1DIR|=Yplus;							//set Y+ to output
	P1OUT|=Yplus;							//Y+ is output 1

	P1DIR |= Yminus;						// Y- is an output
	P1OUT &= ~Yminus;

	P1DIR &= ~Xminus;						// X- is an input
	P1OUT |= Xminus;

	P1DIR &= ~Xplus;						// X+ is ADC input
	P1OUT |= Xplus;
}


