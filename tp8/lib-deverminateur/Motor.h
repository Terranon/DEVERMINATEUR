/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Motor.h
 * Description: General use of motors
 * Version: 1.0
\******************************************************************************/

#ifndef MOTOR_H
#define MOTOR_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h> 
const uint8_t FRWD = 0x00; //lorsque direction = 0 lumiere verte
const uint8_t BACK = 0x30; //lorsque direction = 1 lumiere rouge
const uint8_t PORT_SORTIE = 0xff;

class Motor{
public:

	/**
	 * \brief Constuctor  
	 * \return a Motor
	 */
	Motor(uint8_t direction, uint8_t speed);
	
	/**
	 * \brief Default Constructor
	 * \return 
	 */
	Motor();
	
	/**
	 * \brief Destructor 
	 * \return 
	 */
	~Motor();

	/**
	 * \brief function setDirection changes the direction of the motor
	 */
	void setDirection(uint8_t direction);
	
	/**
	 * \brief function setSpeed changes the speed of the motor
	 * the minimum is 0 and the maximum is 255
	 */
	void setSpeed(uint8_t speed);
	
	/**
	 * \brief driveMotors initialise Timer 2 
	 */
	void driveMotors();
	
private:
	uint8_t direction_;
	uint8_t speed_;

};

#endif 
