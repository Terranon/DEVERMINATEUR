#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h> 

#include "Queue.h"

class Obstacle {
public:
	Obstacle();
	void push(uint8_t distance);
	uint8_t detectionObstacle();

private:
	Queue distances_;
	uint8_t numberOfDistances_;
};

#endif // OBSTACLE_H
