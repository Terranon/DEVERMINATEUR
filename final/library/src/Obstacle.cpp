/******************************************************************************\
 * Authors: William Chartrand, Jean-Raphael Matte
 * Name: Obstacle.cpp
 * Description: this class manages a log of data recieved from the sensor
 * 
 * Version: 1.0
\******************************************************************************/

#include "Obstacle.h"

Obstacle::Obstacle(uint8_t length):
wallMinLength_(length) {}

void Obstacle::push(uint8_t distance) {
	
	distances_.push(distance);
	
	// Keep track of how many distances have been pushed if it is not enough to
	// to draw conlcusions
	if (numberOfDistances_ < wallMinLength_) {
		numberOfDistances_++;
	}
	
}

uint8_t Obstacle::analyze() {
	
	// Check if enough data has been collected
	if (numberOfDistances_ < wallMinLength_) {
		
		// Not enough data
		return NONE;
		
	} else {
		
		// Check if there is an obstacle in sight right now
		if (distances_.get(0) <= MAX_DISTANCE) {
			
			// Check how long the current obstacle is
			for (uint8_t i = 1; i < wallMinLength_; i++) {
				
				// Check if the beginning of the pole can be found
				if (distances_.get(i) > MAX_DISTANCE) {
					
					// The beginning of the obstacle was found, not long enough
					// to be a wall
					return NONE;
					
				}
				
			}
			
			// Checked WALL_MIN_LENGTH distances and couldn't find the beginning
			// of the obstacle. It is safe to assume this is a wall and not a 
			// pole
			return WALL;
		
		} else {
			
			// Check if there was something in sight on the previous check
			if (distances_.get(1) <= MAX_DISTANCE) {
				
				// End of obstacle detected, this is a pole
				return POLE;
				
			} else {
				
				// There was no obstacle at all
				return NONE;
				
			}
		}
	}
	
}

void Obstacle::clear() {
	numberOfDistances_ = 0;
}
