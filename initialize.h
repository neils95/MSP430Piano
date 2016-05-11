/* This header file contains the declarations of the functions needed to intialize the 3 main internal
 * peripherals on the MSP430 used in our project. These are ADC, WDT and TimerA. The WDT is set to generate
 * and interrupt at regular intervals and check whether the screen has been touched. If a touch is detected,
 * the ADC is used to first read the X coordinate, then read the Y coordinate. Once both the coordinates are
 * read,the appropriate tone is played by writing into the TACCR0 register to generate a PWM corresponding to
 * note.
 */
void init_adc(void);
void init_wdt(void);
void init_timer(void);
