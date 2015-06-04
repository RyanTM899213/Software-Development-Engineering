/*
 * assign2.cpp
 * Memorial University of Newfoundland
 * Engineering 1020 Intro. to Programming
 * Assignment 2
 *
 * Created on: Jun 3, 2014
 * Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 * 			rtm773@mun.ca			  f97nis@mun.ca
 * Due date: June 9/2014
 */

#include <pololu/orangutan.h>
#include <pololu/3pi.h>
#include "util3pi.h"

/** this is the implementation for the turnRight function.
 * This method will turn the robot approx. 90 degrees to the right.
 */
void turnRight() {

	set_motors(33,0);  // set the left wheel to turn
	delay_ms(1000);  // move for 1 sec (or 0, doesn't matter)
	set_motors(0,0);  // then stop the robot
}

/** this method (implementation) tells the robot to move ahead
 *  with the given distance (as an argument).
 */
void driveAhead(double distance) {

	// double delay = distance / 0.625;
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

/** makeBox makes the robot travel a square by making it
 * take a 90 degree right turn then moves ahead 2 ft. does
 * four times to complete the square.
 */
void makeBox() {

	for (int i = 0; i <= 3; i++) {

		driveAhead(2.0);  // drive ahead 2 feet
		delay_ms(500);
		turnRight();
		delay_ms(500);
	}
}





