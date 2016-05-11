/*
 * This file contains the functions needed to intialize the 3 main internal peripherals on the
 * MSP430 used in our project. These are ADC, WDT and TimerA. The WDT is set to generate and interrupt
 * at regular intervals and check whether the screen has been touched. If a touch is detected, the ADC
 * is used to first read the X coordinate, then read the Y coordinate. Once both the coordinates are read,
 * the appropriate tone is played by writing into the TACCR0 register to generate a PWM corresponding to
 * note.
 */

asm(" .length 10000");
asm(" .width 132");
#include <msp430g2553.h>

//Global variables to use ADC
#define ADC_INPUT_BIT_MASK_X 0x08		//To read X coordinate read voltage on P1.3
#define ADC_INCH_X INCH_3
#define ADC_INPUT_BIT_MASK_Y 0x02		//To read Y coordinates read voltage on P1.1
#define ADC_INCH_Y INCH_1

//Global variable for the TimerA output pin
#define TA0_BIT 0x20

//Define global variables to connect the outputs of the touchscreen to the MSP430
#define RED 0x01		//red led is P1.0
#define Xplus 0x02		//X+ is P1.1
#define Xminus 0x04 	//X- is P1.2
#define Yplus 0x08		//Y+ is P1.3
#define Yminus 0x10		//Y- is p1.4



// Initialization of the ADC.
void init_adc(){
		ADC10CTL0 &=~ENC;				 //disable ADC before making changes
		ADC10CTL1= ADC_INCH_X	         //input channel 3
					  +SHS_0             //use ADC10SC bit to trigger sampling
					  +ADC10DIV_4        // ADC10 clock/5
					  +ADC10SSEL_0       // Clock Source=ADC10OSC
					  +CONSEQ_0;         // single channel, single conversion
					  ;
	    ADC10AE0=ADC_INPUT_BIT_MASK_X; 	// enable A3 analog input
		ADC10CTL0= SREF_0	     		//reference voltages are Vss and Vcc
					  +ADC10SHT_3 		//64 ADC10 Clocks for sample and hold time (slowest)
					  +ADC10ON			//turn on ADC10
					  +ENC				//enable (but not yet start) conversions
					  +ADC10IE  		//enable interrupts
					  ;

}

/*Initialization and start of WDT. The WDT polls on regular intervals to check whether
 the screen has been touched.*/
void init_wdt(){

	// setup the watchdog timer as an interval timer
 	WDTCTL =(WDTPW +		// (bits 15-8) password
    	                   	// bit 7=0 => watchdog timer on
      	                 	// bit 6=0 => NMI on rising edge (not used here)
                       		// bit 5=0 => RST/NMI pin does a reset (not used here)
          	 WDTTMSEL +     // (bit 4) select interval timer mode
 		     WDTCNTCL  		// (bit 3) clear watchdog timer counter
 		                	// bit 2=0 => SMCLK is the source
 		                	// bits 1-0 = 00 => source/32K
			 );
    IE1 |= WDTIE;			// enable the WDT interrupt (in the system interrupt register IE1)
}


/*
 * Initialize and start of the timer. The timer is used to output the appropriate tone
 * by writing into TACCR0 register.
 */

void init_timer(){
	TA0CTL |= TACLR;            // reset clock
	TA0CTL = TASSEL_2+ID_0+MC_1;// clock source = SMCLK
	                            // clock divider=1
	                            // UP mode
	                            // timer A interrupt off
	TA0CCTL0=OUTMOD_4; 			// compare mode, output mode 0, no interrupt enabled
	TA0CCR0 = 0; 				// in up mode TAR=0... TACCRO-1
	P1SEL|=TA0_BIT; 			// connect timer output to pin
	P1DIR|=TA0_BIT;

}

