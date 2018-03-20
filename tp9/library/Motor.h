/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Motor.h
 * Description: General use of motors able to set a speed between 0 and 255, and a 
 * 							direction FRWD or BACK to the bot  
 * 						Using 
 * 						JM1D : 
 * 						JM1E : 
 * 						JM2D : 
 * 						JM2E : 
 * Version: 1.0
\******************************************************************************/

#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h> 

class Motor {
public:
      
	static const uint8_t FRWD = 0; 
	static const uint8_t BACK = 1; 

	/**
	* \brief Default Constructor : initialize private attributes of an object from the class Motor
	* by default
	* \return a Motor going forward with a speed of 0
	*/
	Motor();

	/**
	 * \brief Constuctor with parameters : initialize private attributes of an object from the class Motor
	 * by passing a direction, FRWD(forward) or BACK(backward), and a speed (between 0 and 255) 
	 * \return a Motor having a direction and a speed decided by the user
	 */
	Motor(uint8_t direction, uint8_t speed);
	
	/**
	 * \brief Destructor : destroy an object from the class motor and resets all its private attributes
	 * \param direction and speed 
	 */
	~Motor();

	/**
	 * \brief set functions set the direction or the speed of a motor
	 * \param direction or speed
	 */
	void setDirectionLM(uint8_t direction);
	void setDirectionRM(uint8_t direction);
	void setSpeedLM(uint8_t speed);
	void setSpeedRM(uint8_t speed);
	
	/**
	 * \brief get functions get the direction or the speed of a motor
	 * \return direction or speed
	 */
	uint8_t getDirectionLM();
	uint8_t getDirectionRM();
	uint8_t getSpeedLM();
	uint8_t getSpeedRM();


	/**
	 * \brief function setSpeed changes the speed of the motor between 0 and 255
	 * \param speed
	 */
	void turnLeft();
	void turnRight();
	void goFRWD(uint8_t speed);
	void goBACK(uint8_t speed);
	/**
	 * \brief function driveMotors initializes the mechanism of the motors by starting Timer 2 that creates
	 * a PWM permitting to have two output activating each motor to a certain speed
	 */
	void driveMotors();
	void stopMotors();
	
	
private:
	uint8_t directionLM_;
	uint8_t directionRM_;
	uint8_t speedLM_;
	uint8_t speedRM_;

};

#endif 
