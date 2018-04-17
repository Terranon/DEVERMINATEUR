/******************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        USBCommunicator.h
 * Description:	Class that communicates with computer through USB Cable via UART
 * 
 * Version: 1.0
\******************************************************************************/

#ifndef USBCommunicator_H
#define USBCommunicator_H

#include <util/delay.h>

#include "Button.h"
#include "Sensor.h"
#include "Motor.h"
#include "Led.h"
#include "memoire_24.h"

class USBCommunicator {

public:

	/**
	 * \brief constructor for the USBCommunicator; the DDRx register will be set
	 *        to enable output and input on the appropriate pins
	 * \return a USBCommunicator
	 */
	USBCommunicator();

	/**
	 * \brief start the communication protocol
	 */
	void communicate();

private:
    
    /**
	 * \brief transmit data
	 * \param valueTransmitted the data to be sent
	 */
	void transmit(uint8_t data);

	/**
	 * \brief return any unread data in the receive buffer, if any
	 * \return the data if there is unread data in the buffer,
	 *         0 if there is none
	 */
	uint8_t receive();

	

	/**
	 * \brief answer a MSG_WHEEL_L message; catch the operand and change the 
	 *        direction and speed of the left motor accordingly
	 */
	void answerWheelL();

	/**
	 * \brief answer a MSG_WHEEL_R message; catch the operand and change the 
	 *        direction and speed of the right motor accordingly
	 */
	void answerWheelR();

	/**
	 * \brief answer a MSG_LED message; catch the operand and change the color 
	 *        accordingly
	 */
	void answerLed();

	/**
	 * \brief answer a MSG_INFO message; send all info for startup
	 */
	void answerInfo();

	/**
	 * \brief send the robot's name
	 */
	void sendName();

	/**
	 * \brief send the team number
	 */
	void sendTeam();

	/**
	 * \brief send the section number
	 */
	void sendSection();

	/**
	 * \brief send the semester
	 */
	void sendSemester();

	/**
	 * \brief send the base color
	 */
	void sendColor();

	/**
	 * \brief send the state of the button
	 */
	void sendButton();

	/**
	 * \brief send left sensor distance
	 */
	void sendSensorL();

	/**
	 * \brief send right sensor distance
	 */
	void sendSensorR();

	/**
	 * \brief send all dynamic data
	 */
	void updateInfo();

	/**
	 * \brief check if the computer has sent any message; answer if any
	 */
	void checkAndAnswer();

	// Messages from the robot to the computer
	static const uint8_t MSG_NAME = 0xF0;
	static const uint8_t MSG_TEAM = 0xF1;
	static const uint8_t MSG_SECTION = 0xF2;
	static const uint8_t MSG_SEMESTER = 0xF3;
	static const uint8_t MSG_COLOR = 0xF4;
	static const uint8_t MSG_BUTTON = 0xF5;
	static const uint8_t MSG_SENSOR_L = 0xF6;
	static const uint8_t MSG_SENSOR_R = 0xF7;

	// Messages from the computer to the robot
	static const uint8_t MSG_WHEEL_L = 0xF8;
	static const uint8_t MSG_WHEEL_R = 0xF9;
	static const uint8_t MSG_LED = 0xFA;
	static const uint8_t MSG_INFO = 0xFB;

	// Robot base colors
	static const uint8_t BASECOLOR_BLACK = 0x01;
	static const uint8_t BASECOLOR_BLUE = 0x02;
	static const uint8_t BASECOLOR_YELLOW = 0x03;
	static const uint8_t BASECOLOR_GREEN = 0x04;

	// LED colors
	static const uint8_t LEDCOLOR_OFF = 0x00;
	static const uint8_t LEDCOLOR_GREEN = 0x01;
	static const uint8_t LEDCOLOR_RED = 0x02;

	// Button states
	static const uint8_t BUTTON_PRESSED = 0x00;
	static const uint8_t BUTTON_RELEASED = 0x01;

	// # of characters in the robot's name
	static const uint8_t NAMESIZE = 13;

	// # of characters in the team's number
	static const uint8_t NUMBERSIZE = 9;

	// # of characters in the semester code
	static const uint8_t SEMESTERSIZE = 4;
    
	char robotName_[NAMESIZE+1];
	char teamNumber_[NUMBERSIZE+1];
	char sectionNumber_;
	char semester_[SEMESTERSIZE+1];
	uint8_t robotColor_;

	Button button_;
	Sensor sensors_;
	Motor motors_;
	Led led_;
};
#endif

