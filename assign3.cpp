/*
 * assign3.cpp
 * Memorial University of Newfoundland
 * Engineering 1020 Intro. to Programming
 * Assignment 3
 *
 * Created on: June 10, 2014
 * Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 * 			rtm773@mun.ca			  f97nis@mun.ca
 * Due date: June 16, 2014
 */

#include <pololu/orangutan.h>
#include <pololu/3pi.h>
#include "util3pi.h"

/** this is the implementation for the turnRight function.
 * This method will turn the robot at 90 degrees to the right.
 */
void turnRight() {

	set_motors(38,0);  // set the right wheel to turn
	delay_ms(1000);  // move for 1 sec
	set_motors(0,0);  // then stop the robot
}

/** this method implementation tells the robot to turn right
 *  at 90 degrees to the left.
 */
void turnLeft() {

	set_motors(0,38);  // set the left wheel to turn
	delay_ms(1000);  // move for 1 sec
	set_motors(0,0);  // then stop the robot
}

/** this method (implementation) tells the robot to move ahead
 *  with the given distance (as an argument).
 */
void driveAhead(double distance) {

	// double feet = distance * 3.28084; // convert meters to feet
	// double delay = feet / 0.625;
	set_motors(45,45);
	delay_ms(3200);  // replace 3200 with delay * 1000 to get ms
	set_motors(0,0);

	/** it went 2 ft. at 45/255 speed in 3200ms.
	 *  so, v = 2 ft. / 3.2 sec. = 0.625 ft/s. therefore for the
	 *  future, we can use this value to calculate time.
	 *
	 *  t = distance / 0.625
	 */
}

/** This function waits for any of the three buttons to be pressed, and
 *  will respond differently to each of the three button presses.
 *  A will turn left
 *  B will drive ahead one foot, and
 *  C will turn right.
 */
void testMotion() {

	char button = waitForAnyButton();  // get the button that is pressed
	if (button == BUTTON_A) {  // and comparisons below

		turnLeft();
	}
	else if (button == BUTTON_B) {

		driveAhead(1.0);
	}
	else if (button == BUTTON_C) {

		turnRight();
	}
	else {

		print("what?");
	}
}





