/*
 * assign8.cpp
 * Memorial University of Newfoundland
 * Engineering 1020 Intro. to Programming
 * Assignment 8
 *
 * Created on: July 29, 2014
 * Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 * 			rtm773@mun.ca			  f97nis@mun.ca
 * Due date: Aug 4, 2014
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
void followSegment(bool& left, bool& right, bool& straight) { // this function will make the robot
											// go up to the intersection
	straight = false;
	right = false;
	left = false;
	int sens = readSensorsBranches(left, right);

	while (0 < sens && sens < 4000 && !left && !right) { // while the sensor is in between 0 to 4000, and
					// no left or right is detected

		if (sens < 1000) { // it should turn  to the left if sensor detects this reading
			set_motors(0, 75);
		}

		else if (sens < 1900) { // a slow turn when this reading the detected
			set_motors(75/2 , 75);
		}

		else if (sens < 2100) { // if the readings are this, it should drive straight
			set_motors(75, 75);
		}

		else if (sens < 3000) { // turn to right
			set_motors(75, 75/2);
		}

		else // turn more to right
		{
			set_motors(75, 0);
		}

		sens = readSensorsBranches(left, right); // updating the value of sens
	}

	set_motors(75,75); // the motor should keep going straight
	delay_ms(20); // to make it stop at the right place before making any turns for followTrack
	sens = readSensorsBranches(left, right);
	delay_ms(70);
	set_motors(0, 0);
	sens = readLineSensors();
	straight = (sens > 0 && sens < 4000);
}

/** isTarget***
 * this method will return true if the robot is on the black 7x5 square, where all
 * 5 sensors are on the black block.
 * @returns true if the robot is on the black 7x5 square
 */
bool isTarget() {

	unsigned int sensors[5];
	read_line(sensors, IR_EMITTERS_ON);

	return (sensors[0] > 500 && sensors[2] > 500 && sensors[3] > 500 && sensors[4] > 500 && sensors[1] > 500);
}

/** followRoute***
 * this method will make the robot follow a track denoted by a black line
 * until it reaches the end of the track or maxTurns is exceeded
 * @params: turns - the array to hold the sequence of turns the robot takes
 * 			len - the length of the array
 * @returns true if & only if the robot has reached the end of the maze (black square)
 */
bool followRoute(char turns[], int len) {

	int i = 0; // setting turn counter at 0
	bool left = false; // no left to start with
	bool right = false; // no right to start with
	bool straight = false; // no straight to start with

	followSegment(left, right, straight);

	/**while (i < len) {

		if (isTarget()) { return true; }  // exit and return true if black square is found

		if (left) { // if left it will turn left, also increase the counter left by 1

			turnLeft();
			turns[i++] = 'L';
		}

		else if (right) { // if right it will turn right, also increase the counter by 1

			turnRight();
			turns[i++] = 'R';
		}

		followSegment(left, right, straight); // update the left, right and straight counter
	}*/

	for (int i = 0; i <= len; i++) {

		followSegment(left, right, straight);

		if (isTarget()) { return true; }

		if (turns[i] == 'L') { turnLeft(); }

		else if (turns[i] == 'R') { turnRight(); }

		else { followSegment(left, right, straight); }
	}
	set_motors(0, 0); // if it does not detect anything it should stop, or if the number of permissible
					// turns reaches it should stop as well
	return false; // false is returned if no black square is found
}

/** solveMazeBest***
 * this function causes the robot to drive along a track, following a black line
 * and eventually finding the end point or meeting the maximum number of turns
 * allowed for the robot.
 * @params: route - the array which holds the turns the robot takes throughout the
 * 					maze. L for left, R for right, S for straight, or A for 180 turn.
 * 			maxLen - the maximum number of turns the robot can take while traversing
 * 					 the maze.
 * @returns the number of turns the robot takes while in the maze
 */
int solveMazeBest(char route[], int maxLen) {

	int i = 0; // setting turn counter at 0 // i
	bool left = false; // no left to start with
	bool right = false; // no right to start with
	bool straight = false; // no straight to start with

	while ((i < maxLen) && !isTarget()) { // while the counter is less than maximum
									// turns allowed and if it is left or right or straight
		followSegment(left, right, straight); // calling the function followSegment, which goes
												  // up to the intersection
		if (left && right) {

			turnLeft();
			route[i++] = 'L';
		}
		else if (left) { // if left it will turn left, also increase the counter left by 1

			turnLeft();
			route[i++] = 'L';
		}
		else if (straight) {

			set_motors(40,40);
			route[i++]='S';
		}
		else if (right) {

			turnRight();
			route [i++]= 'R';
		}
		else {

			turnLeft();
			route[i++]='L';
			turnLeft();
			route [i++]= 'L';
		}
		left = false;
		right = false;
		straight = false;
	}
	set_motors(0, 0); // if it does not detect anything it should stop, or if the number of permissible
					// turns reaches it should stop as well
	return trimRoute(route, i); // it should return the counter value in form of arrays
}

/** trimRoute***
 * this method will trim the array supplied to remove any redundant or unnecessary turns
 * so that the robot follows a more direct route.
 * @params: route - the array of turns to be modified
 * 			len - the size of the array (route)
 * @modifies: route - the array of turns the robot takes
 * @returns the updated size of the array after being trimmed
 */
int trimRoute(char route[], int len) {

	int l = 90;
	int r = 270;
	int s = 360;
	int a = 180;

	for (int i = len - 2; i > 0; i--) {

		int prev = 0;
		int next = 0;
		if (route[i] == 'A') {

			switch (route[i - 1]) {  // prev

			case 'L':
				prev = l;
				break;

			case 'R':
				prev = r;
				break;
			}

			switch (route[i + 1]) {  // next

			case 'L':
				next = l;
				break;

			case 'R':
				next = r;
				break;
			}

			int sum = prev + next + a;

			switch (sum) {

			case 360:
				route[i - 1] =
			}

		}
	}

}





