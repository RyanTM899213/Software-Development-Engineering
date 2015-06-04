/*
 * assign7.cpp
 * Memorial University of Newfoundland
 * Engineering 1020 Intro. to Programming
 * Assignment 7
 *
 * Created on: July 22, 2014
 * Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 * 			rtm773@mun.ca			  f97nis@mun.ca
 * Due date: July 28, 2014
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

/** isTarget***
 * this method will return true if the robot is on the black 7x5 square, where all
 * 5 sensors are on the black block.
 * @returns true if the robot is on the black 7x5 square
 */
/**bool isTarget() {

	unsigned int sensors[5];
	read_line(sensors, IR_EMITTERS_ON);
	bool isLeft = sensors[0] > 500;
	bool isRight = sensors[4] > 500;
	bool sOne = sensors[1] > 500;
	bool sTwo = sensors[2] > 500;
	bool sThree = sensors[3] > 500;

	return isLeft && isRight && sOne && sTwo && sThree;
}

/**followSegment***
 * this method will drive the robot along a straight path until it reaches a branch in
 * the path. It will detect and print the branch direction to screen as L or R.
 * @modifies: left -
 * 			  right -
 * 			  straight -
 * @returns nothing
 */
/**void followSegment(bool& left, bool& right, bool& straight) { // this function will make the robot
											// go up to the intersection
	straight = false;
	right = false;
	left = false;
	int sens = readSensorsBranches(left, right);

	while (0 < sens && sens < 4000 && !left && !right && !isTarget()) { // while the sensor is in between 0 to 4000, and
					// no left or right is detected

		if (sens < 1000) { // it should turn  to the left if sensor detects this reading
			set_motors(0, 40);
		}

		else if (sens < 1900) { // a slow turn when this reading the detected
			set_motors(20 , 40);
		}

		else if (sens < 2100) { // if the readings are this, it should drive straight
			set_motors(40, 40);
		}

		else if (sens < 3000) { // turn to right
			set_motors(40, 20);
		}

		else // turn more to right
		{
			set_motors(40, 0);
		}

		sens = readSensorsBranches(left, right); // updating the value of sens
	}
	set_motors(40,40); // the motor should keep going straight
	delay_ms(200); // to make it stop at the right place before making any turns for followTrack
	set_motors(0, 0);
	straight = (sens > 0 && sens < 4000);
}

/** followTrack***
 * this method will make the robot follow a track denoted by a black line
 * until it reaches the end of the track or maxTurns is exceeded
 * @params: turns - the array to hold the sequence of turns the robot takes
 * 			maxTurns - the maximum number of turns the robot is allowed to make
 * @returns the number of left and right turns the robot makes
 */
/**int followTrack(char turns[], int maxTurns) {
	int i = 0; // setting turn counter at 0
	bool left = false; // no left to start with
	bool right = false; // no right to start with
	bool straight = false; // no straight to start with

	followSegment(left, right, straight); // calling the function followSegment, which goes
										  // up to the intersection

	while ((i < maxTurns) && (left || right || straight) && !isTarget()) { // while the counter is less than maximum
									// turns allowed and if it is left or right or straight

		if (left) { // if left it will turn left, also increase the counter left by 1
			turnLeft();
			turns[i++] = 'L';
		}

		else if (right) { // if right it will turn right, also increase the counter by 1
			turnRight();
			turns[i++] = 'R';
		}
		followSegment(left, right, straight); // update the left, right and straight counter
	}
	set_motors(0, 0); // if it does not detect anything it should stop, or if the number of permissible
					// turns reaches it should stop as well
	return i; // it should return the counter value in form of arrays
}

/** solveMaze***
 * this function causes the robot to drive along a track, following a black line
 * and eventually finding the end point or meeting the maximum number of turns
 * allowed for the robot.
 * @params: route - the array which holds the turns the robot takes throughout the
 * 					maze. L for left, R for right, S for straight, or A for 180 turn.
 * 			maxLen - the maximum number of turns the robot can take while traversing
 * 					 the maze.
 * @returns the number of turns the robot takes while in the maze
 */
/**int solveMaze(char route[], int maxLen) {

	int turns = 0;
	bool left = false;
	bool right = false;
	bool straight = false;
	char prev = 'l';  // default is left
	int sensors = readLineSensors();

	while (turns < maxLen && !isTarget()) {

		followSegment(left, right, straight);

		if (turns == 0 || left) {

			turnLeft();
			route[turns] = 'L';
			prev = 'l';
			turns++;
		}
		else if (right) {

			turnRight();
			route[turns] = 'R';
			prev = 'r';
			turns++;
		}
		else if (left && right) {

			if (prev == 'l') {

				turnRight();
				route[turns] = 'R';
				prev = 'r';
			}
			else {

				turnLeft();
				route[turns] = 'L';
				prev = 'l';
			}
			turns++;
		}
		else if (sensors == 4000) {  // no black line

			set_motors(0,0);
			turnRight();
			turnRight();  // twice for 190 degree turn
			route[turns] = 'A';
			turns++;
		}
		sensors = readLineSensors();  // update!!
		left = false;
		right = false;
		straight = false;  // reset values
	}
	set_motors(0,0);
	return turns;
}
int solveMaze(char route[], int maxLen) {
	int i = 0; // setting turn counter at 0
	bool left = false; // no left to start with
	bool right = false; // no right to start with
	bool straight = false; // no straight to start with

	followSegment(left, right, straight); // calling the function followsegment, which goes
										  // up to the intersection

	while ((i < maxLen) && !isTarget()) { // while the counter is less than maximum
									// turns allowed and if it is left or right or straight

		if (left == true) { // if left it will turn left, also increase the counter left by 1
			turnLeft();
			route[i++] = 'L';
		}

		else if (straight == true)
		{
			set_motors(40,40);
			route[i++]='S';
		}

		else if (right == true)
		{
			turnRight();
			route [i++]= 'R';
		}



		else
		{
			turnLeft();
			route[i++]='L';
			turnLeft();
			route [i++]= 'L';

		}

		followSegment(left, right, straight); // update the left, right and straight counter
	}
	set_motors(0, 0); // if it does not detect anything it should stop, or if the number of permissible
					// turns reaches it should stop as well
	return i; // it should return the counter value in form of arrays
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
			set_motors(0, 40);
		}

		else if (sens < 1900) { // a slow turn when this reading the detected
			set_motors(20 , 40);
		}

		else if (sens < 2100) { // if the readings are this, it should drive straight
			set_motors(40, 40);
		}

		else if (sens < 3000) { // turn to right
			set_motors(40, 20);
		}

		else // turn more to right
		{
			set_motors(40, 0);
		}

		sens = readSensorsBranches(left, right); // updating the value of sens
	}

	set_motors(40,40); // the motor should keep going straight
	delay_ms(100); // to make it stop at the right place before making any turns for followTrack


	delay_ms(100);
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

	bool end= false;
	unsigned int sensors[5];
	read_line(sensors, IR_EMITTERS_ON);

	if (sensors[0] > 500 && sensors[2] > 500 && sensors[3] > 500 && sensors[4] > 500 && sensors[1] > 500)
	{
		end = true;
	}

	else
	{
		end = false;
	}

	return end;

}

int solveMaze(char route[], int maxLen) {
	int i = 0; // setting turn counter at 0 // i
	bool left = false; // no left to start with
	bool right = false; // no right to start with
	bool straight = false; // no straight to start with

	while ((i < maxLen) && !isTarget()) { // while the counter is less than maximum
									// turns allowed and if it is left or right or straight
		followSegment(left, right, straight); // calling the function followsegment, which goes
												  // up to the intersection
		if (left && right) {

			turnLeft();
			route[i++] = 'L';
		}
		else if (left == true) { // if left it will turn left, also increase the counter left by 1
			turnLeft();
			route[i++] = 'L';
		}
		else if (right == true)
		{
			turnRight();
			route [i++]= 'R';
		}
		else if (straight == true)
		{
			set_motors(40,40);
			route[i++]='S';
		}
		else
		{
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
	return i; // it should return the counter value in form of arrays
}



