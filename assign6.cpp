/*
 * assign6.cpp
 * Memorial University of Newfoundland
 * Engineering 1020 Intro. to Programming
 * Assignment 6
 *
 * Created on: July 17, 2014
 * Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 * 			rtm773@mun.ca			  f97nis@mun.ca
 * Due date: July 21, 2014
 */

#include <pololu/orangutan.h>
#include <pololu/3pi.h>
#include "util3pi.h"

/** turnLeft***
 * a simple method to make the 3pi robot to make a 90 degree left turn
 * @returns nothing
 */
void turnLeft() {

	const int TURN_SPEED=40; // speed at which robot turns
	const unsigned long TURN_RATE=4738; // turn rate for 90 degree
	int delay= 90*TURN_RATE/1000; //formula for delay/ time for turning
	set_motors(-TURN_SPEED, TURN_SPEED); // speed of the motors for turning
	delay_ms (delay); // time for turning
	set_motors(0,0); // halts after turning
}

/** turnRight***
 * simply makes the robot turn right 90 degrees
 * @returns nothing
 */
void turnRight() {

	const int TURN_SPEED=40;  // this is the speed at which we want the robot to turn
	const unsigned long TURN_RATE=4738; // this is our turn rate for 90 degree
	int delay= 90*TURN_RATE/1000; // this is our formula for how long it should turn
	set_motors(TURN_SPEED, -TURN_SPEED);
	delay_ms (delay); // how long it should turn
	set_motors(0,0); // after the delay it should come to a stop
}

/**followSegment***
 * this method will drive the robot along a straight path until it reaches a branch in
 * the path. It will detect and print the branch direction to screen as L or R.
 * @modifies: left -
 * 			  right -
 * 			  straight -
 * @returns nothing
 */
void followSegment(bool& left, bool& right, bool& straight) {

	bool isLeft = false;
	bool isRight = false;
	int sensors = readSensorsBranches(isLeft, isRight);

	while (!isLeft && !isRight && sensors > 0 && sensors < 4000) { // black line

		set_motors(50,50);
		delay_ms(180);
		sensors = readSensorsBranches(isLeft, isRight);
	}
	set_motors(0,0);

	if (isLeft) {

		left = 1;
		turnLeft();
	}
	else if (isRight) {

		right = 1;
		turnRight();
	}
	else if (sensors >= 1931 && sensors <= 2081) {

		straight = 1;
	}
	isLeft = false;
	isRight = false;
}

/** followTrack***
 * this method will make the robot follow a track denoted by a black line
 * until it reaches the end of the track or maxTurns is exceeded
 * @params: turns - the array to hold the sequence of turns the robot takes
 * 			maxTurns - the maximum number of turns the robot is allowed to make
 * @returns the number of left and right turns the robot makes
 */
int followTrack(char turns[], int maxTurns) {

	bool isLeft = false;
	bool isRight = false;
	int numTurns = 0;
	bool l = false;
	bool r = false;
	bool s = false;
	int sensors = readSensorsBranches(isLeft, isRight);

	while (numTurns <= maxTurns || (sensors > 0 && sensors < 4000)) {

		followSegment(l, r, s);
		if (isLeft) {

			turns[numTurns] = 'L';
			numTurns++;
		}
		else if (isRight) {

			turns[numTurns] = 'R';
			numTurns++;
		}
		l = false;
		r = false;
		s = false;
		isLeft = false;
		isRight = false;
		sensors = readSensorsBranches(isLeft, isRight);
	}

	return numTurns;
}








