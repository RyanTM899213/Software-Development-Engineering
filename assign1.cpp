/*  assign1.cpp
 *
 *  Created on: May 27, 2014
 *      Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 */

#include "assign1.h"
#include <pololu/orangutan.h>
#include <pololu/3pi.h>

/** This is the function implementation that is stated
 *  in the assign1.h header file. Prints the battery
 *  power remaining as a percentage. Code is commented
 *  at each line below.
 */
void displayBattery() {  // the function we are implementing that
						 // is called from main

	clear();  // clear the screen

	double milliV = read_battery_millivolts();  // our millivolt value returned from
												// the read_battery_millivolts function
	double volts = milliV / 1000.0;  // convert to volts from millivolts
	double percentage = (volts / 6.0) * 100.0; // convert to percentage
	print_long(percentage);  // print the percentage
	print("%");  // print percent sign
	lcd_goto_xy(0,1);  // go to the next line on the screen
	print("Press B");  // "press B" on the second line
	waitForB();  // wait for user to press the B button
}


