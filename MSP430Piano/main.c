#include <msp430g2553.h>
#include "touchscreen.h"
#include "initialize.h"
#include "notes.h"

//declare function needed to play sound and display note being played on 7 segment disply
void sound_display(int,int);

//Define global variables to connect the outputs of the touchscreen to the MSP430
#define RED 0x01
#define Xplus 0x02		//X+ is P1.1
#define Xminus 0x04 	//X- is P1.2
#define Yplus 0x08		//Y+ is P1.3
#define Yminus 0x10		//Y- is p1.4

// Global state variables
volatile unsigned int last_button; 	// the state of the button bit at the last interrupt, use for debouncing
volatile unsigned int X=0;			//X coordinate of touch
volatile unsigned int Y =0;			//Y coordinate of touch
volatile unsigned wdt_counter =1;	//Count the number of WDT intervals

void main(void) {
	  init_touchscreen();			//initialize touchscreen
	  init_wdt();					//initialize wdt
	  init_adc();					//initialize ADC
	  init_timer();					//initialize Timer
	  _bis_SR_register(GIE+LPM0_bits);  // enable interrupts and also turn the CPU off
}


/*
 * Within the WDT interrupt handler check whether the screen is touched. If yes, trigger the ADC conversion
 * to read X and Y coordinates.The X and Y coordinates are read on alternate WDT interrupts. The wdt_counter
 * global variable is used to keep track of this.
 */
interrupt void WDT_interval_handler(){
		init_touchscreen();
		unsigned char b;

		b=(P1IN | Xplus)!= (P1IN);			//X+ is 0, if screen is touched
		if(last_button==1 && b==0){			//Screen has not been touched
			P1OUT&=~RED;					//Turn led off
			TA0CCR0=0;						//Do not play any sound
		}

		else if (b==1){						//Screen has been touched
			P1OUT|=RED;						//turn LED on

			if(wdt_counter==1){				//Read Y first
				wdt_counter=2;				//Read X on next interrupt
				init_read_y();				//Initialize GPIO to read Y coordinates
				ADC10CTL0 |= ADC10SC;		//Start ADC conversion
			}
			else  if(wdt_counter==2){		//Read X second
				wdt_counter=1;				//Read Y on the next interrupt
				init_read_x();				//Initialize GPIO to read X coordiantes
				ADC10CTL0 |= ADC10SC;		//Start ADC conversion
			}

		}
		last_button =b;						//store current state of touch screen
}
ISR_VECTOR(WDT_interval_handler, ".int10")

/*
 * The ADC interrupt is called once the X/Y coordinates are read. The handler then calls the functions
 * to reinitialize the touchscreen and play the correct sound.
 */
void interrupt adc_handler(){
	if(wdt_counter==1){						//Currently reading X coordinate
		X=(ADC10MEM/5)+1;					//Scale X to a range of 0-7
	}
	else if(wdt_counter==2){				//Currently reading Y coordinate
		Y=(ADC10MEM/7)+1;					//Scale Y to a range of 0-3
	}
	init_touchscreen();
	sound_display(X,Y);						//Play the correct note based on X and Y and show on 7 segment display
 }
 ISR_VECTOR(adc_handler, ".int05")
