/*
 * This file contains the declarations of functions required to use the touchscreen. A resistive
 * touscreen has four output wires: X+,X-,Y+ and Y-. These are conected to the MSP430 GPIO pins and
 * the pins need to be configured differently for the three main functions required to interface the
 * touchscreen:
 *  1.init_touchscreen(): This function initializes the GPIO pin to detect touch.
 *  2.init_read_y(): This function initilzies the GPIO pin to read the Y coordinate
 *  2. init_read_x(): This function initializes the GPIO pins to read the X coordinate.
 *
 *  The order of operation is:
 *  Initialize touchscreen-> if touch is detected then init_read_y()-> init_read_x()->Initialize touchscreen(reset)
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

void init_touchscreen(void);
void init_read_x(void);
void init_read_y(void);

#endif
