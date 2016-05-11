/*
 * This file has the function needed to play the note based on X and Y coordinates.
 * It also has the display function which displays the current note on the 7 segment display.
 */
asm(" .length 10000");
asm(" .width 132");
#include <msp430g2553.h>
#include "notes.h"

void display(char);

void sound_display(int X, int Y){

	if (X == 1)
	{
		display('A');
		if (Y ==1)
			TA0CCR0 = C5 - 1;

		else if (Y ==2)
			TA0CCR0 = C4 - 1;

		else if (Y ==3)
			TA0CCR0 = C3 - 1;
	}

	else if (X==2)
	{

		display('B');
		if (Y ==1)
			TA0CCR0 = D5 - 1;

		else if (Y ==2)
			TA0CCR0 = D4 - 1;

		else if (Y ==3)
			TA0CCR0 = D3 - 1;
	}
	else if (X==3)
	{

		display('C');
		if (Y ==1)
			TA0CCR0 = E5 - 1;

		else if (Y ==2)
			TA0CCR0 = E4 - 1;

		else if (Y ==3)
			TA0CCR0 = E3 - 1;
	}
	else if (X==4)
	{

		display('D');
		if (Y ==1)
			TA0CCR0 = F5 - 1;

		else if (Y ==2)
			TA0CCR0 = F4 - 1;

		else if (Y ==3)
			TA0CCR0 = F3 - 1;
	}
	else if (X==5)
	{

		display('E');
		if (Y ==1)
			TA0CCR0 = G5 - 1;

		else if (Y ==2)
			TA0CCR0 = G4 - 1;

		else if (Y ==3)
			TA0CCR0 = G3 - 1;
	}
	else if (X==6)
	{

		display('F');
		if (Y ==1)
			TA0CCR0 = A5 - 1;

		else if (Y ==2)
			TA0CCR0 = A4 - 1;

		else if (Y ==3)
			TA0CCR0 = A3 - 1;
	}
	else if (X==7)
	{

		display('G');
		if (Y ==1)
			TA0CCR0 = B5 - 1;

		else if (Y ==2)
			TA0CCR0 = B4 - 1;

		else if (Y ==3)
			TA0CCR0 = B3 - 1;
	}
}



#define A  0x3B
#define B  0x3F
#define C  0x3C
#define D  0x3F
#define E  0x3C
#define F  0x38
#define G  0x3E

//This function displays the note on the 7 segment display using P2 port and P1.7 pin
void display (char s)
{
	P2DIR = 0xFF;
	P1DIR|= 0x80;
	switch (s)
	{
		case 'A':
			P2OUT |= A;
			P1OUT |= 0x80;
			break;
		case 'B':
			P2OUT |= B;
			P1OUT |= 0x80;
			break;
		case 'C':
			P2OUT |= C;
			P1OUT &= ~0x80;
			break;
		case 'D':
			P2OUT |= D;
			P1OUT &= ~0x80;
			break;
		case 'E':
			P2OUT |= E;
			P1OUT |= 0x80;
			break;

		case 'F':
			P2OUT |= F;
			P1OUT |= 0x80;
			break;

		case 'G':
			P2OUT |= G;
			P1OUT |= 0x80;
			break;
		case 'X':
			P2OUT&=0x00;
			P1OUT&=~0x80;
	}
}




