/*
 * assign5.cpp
 * Memorial University of Newfoundland
 * Engineering 1020 Intro. to Programming
 * Assignment 5
 *
 * Created on: July 8, 2014
 * Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 * 			rtm773@mun.ca			  f97nis@mun.ca
 * Due date: July 14, 2014
 */

#include <pololu/orangutan.h>
#include <pololu/3pi.h>
#include "util3pi.h"


/** countIntersections ***********
 * this method will make the robot drive along a straight track,
 * following a black line, and will count the branches to the left
 * and right. stops when it reaches the end of the black line.
 *
 * @modifies: left - the variable that counts the left branches
 * 			  right - the variable that counts the right branches
 * @returns: nothing
 */

void countIntersections(int& left, int& right) {

	bool isLeft = false;
	bool isRight = false;

	int sensors = readSensorsBranches(isLeft, isRight);
	while (sensors > 0 && sensors < 4000) {  // line present

		set_motors(60,60);

		if (isLeft) { // left branch

			left++;
		}
		else if (isRight) {  // right branch

			right++;
		}
		else if (isLeft && isRight) { // left and right branch

			left++;
			right++;
		}
		delay_ms(40);
		sensors = readSensorsBranches(isLeft, isRight);  // update the sensor value
	}
	set_motors(0,0);
}




