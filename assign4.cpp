/*
 * assign4.cpp
 * Memorial University of Newfoundland
 * Engineering 1020 Intro. to Programming
 * Assignment 4
 *
 * Created on: June 17, 2014
 * Authors: Ryan Martin (201039054) & Nazrul Shikon (200688497)
 * 			rtm773@mun.ca			  f97nis@mun.ca
 * Due date: June 26, 2014
 */

#include <pololu/orangutan.h>
#include <pololu/3pi.h>
#include "util3pi.h"

void driveAhead(double distance) {  // distance in meters

	set_motors(50,50);
	delay_ms(100);
}

/** This method will make the robot follow a track denoted by
 * black tape using its sensor. the integer count argument is
 * used as the number of laps to complete.
 * @param laps the number of laps for the robot to complete
 */
void followLineLaps(int laps) {

		for (int i = 0; i < laps; i++) {

			int sensorReading = readLineSensors();  // collect sensor reading
			while (sensorReading != 4000 && sensorReading != 0) {  // no line

				if (sensorReading >= 1931 && sensorReading <= 2081) {  // straight ahead

					driveAhead(1.0);
				}
				else if (sensorReading >= 1 && sensorReading <= 1930) { // left

					set_motors(30,50);  // set the left wheel to turn
				}
				else if (sensorReading >= 2051 && sensorReading <= 3999) {  // right

					set_motors(50,30);  // set the right wheel to turn
				}
				sensorReading = readLineSensors();  // update the sensor value
			}
			play_from_program_space(success);
			set_motors(50,50);
			delay_ms(300);
			set_motors(0,0);
		}
}






