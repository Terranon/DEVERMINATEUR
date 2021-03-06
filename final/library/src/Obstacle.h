/******************************************************************************\
 * Authors: William Chartrand, Jean-Raphael Matte
 * Name: Obstacle.h
 * Description: this class manages a log of data recieved from the sensor
 * 
 * Version: 1.0
\******************************************************************************/

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <avr/io.h>
#include "Queue.h"

class Obstacle {
public:
	
	/**
	 * \brief constructor
	 * \param length Minimum wall length
	 * \return an Obstacle
	 */
	Obstacle(uint8_t length);
	
	/**
	 * \brief Add a distance to the data log
	 * \param distance the distance to push
	 */
	void push(uint8_t distance);
	
	/**
	 * \brief Analyze the accumulated data to see if an obstacle is detected
	 * \return Obstacle::NONE if no obstacle is detected,
	 *         Obstacle::POLE if the end of a pole is detected,
	 *         Obstacle::WALL if a wall is detected
	 */
	uint8_t analyze();

	/**
	 * \brief reset numberOfDistances_
	 */
	void clear();
	
	static const uint8_t NONE = 0;
	static const uint8_t POLE = 1;
	static const uint8_t WALL = 2;

private:
	
	// Data structure for the data log
	Queue distances_;
	
	// Number of distances stored so far
	// (will stop incrementing if >= WALL_MIN_LENGTH)
	uint8_t numberOfDistances_;
	
	// Number of consecutive readings before it is concluded that the obstacle
	// is a wall and not a pole
	uint8_t wallMinLength_;

	// Max range
	static const uint8_t MAX_DISTANCE = 60;
	
};

#endif // OBSTACLE_H
