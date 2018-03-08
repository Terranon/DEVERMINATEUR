/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Motor.h
 * Description: General use of motors able to go forward and backward
 * Version: 1.0
\******************************************************************************/

#ifndef MOTOR_H
#define MOTOR_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h> 
const uint8_t FRWD = 0x00; 
const uint8_t BACK = 0x30; 
const uint8_t PORT_SORTIE = 0xff;

class Motor{
public:

	/**
	* \brief Default Constructor : initialize private attributes of an object from the class Motor
	* by default
	* \return a Motor going forward with a speed of 0
	*/
	Motor();

	/**
	 * \brief Constuctor with parameters : initialize private attributes of an object from the class Motor
	 * by passing a direction FRWD(forward) and BACK(backward), and a speed (between 0 and 255) 
	 * \return a Motor having a direction and a speed decided by the user
	 */
	Motor(uint8_t direction, uint8_t speed);
	
	/**
	 * \brief Destructor : destroy an object from the class motor and reset all its private attributes
	 */
	~Motor();

	/**
	 * \brief function setDirection changes the direction of the motor
	 */
	void setDirection(uint8_t direction);
	
	/**
	 * \brief function setSpeed changes the speed of the motor between 0 and 255
	 */
	void setSpeed(uint8_t speed);
	
	/**
	 * \brief function driveMotors initialize the mechanism of the motors by starting Timer 2 who create
	 * a PWM permitting to have two output activating each motor to a certain speed
	 */
	void driveMotors();
	
private:
	uint8_t direction_;
	uint8_t speed_;

};

#endif 
