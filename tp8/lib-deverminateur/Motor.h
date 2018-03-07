#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>


class motor
{
public:
	motor(uint8_t direction, uint8_t speed);
	~motor();

	void setDirection(uint8_t direction);
	void setSpeed(uint8_t speed);

	void driveMotors() const;
	
private:
	uint8_t direction_;
	uint8_t speed_;

};

#endif /* MOTOR_H */