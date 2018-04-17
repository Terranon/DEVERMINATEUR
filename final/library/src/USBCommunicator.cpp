/******************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        USBCommunicator.cpp
 * Description:	Class that communicates with computer through USB Cable via UART
 * 
 * Version: 2.0
\******************************************************************************/

#include "USBCommunicator.h"

USBCommunicator::USBCommunicator():
robotName_("GucciBot     "),
teamNumber_("93-97    "),
sectionNumber_('5'),
semester_("18-1"),
robotColor_(BASECOLOR_BLACK),
adresseEEPROM_(0),
button_(),
sensors_(),
motors_(Motor::FRWD,0),
led_() {

	UBRR0H = 0;
	UBRR0L = 0xCF;

	// Multi-processor Communication Mode
	UCSR0A = 0x00;

	// Receiver Enable (bit4), Transmitter Enable(bit3)
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Asynchronous USART, non Parity, stop bit(s) 1-bit character size -- 8 bit
	UCSR0C = 0x06;

}

void USBCommunicator::communicate() {

	while(1) {
		checkAndAnswer();
		updateInfo();
	}
	
}

uint8_t USBCommunicator::receive() {

	// Wait for the buffer to be full
	if (UCSR0A & (1 << RXC0)) {
		return UDR0;
	} else {
		return 0;
	}
}

void USBCommunicator::transmit(uint8_t data) {

	// Wait for the buffer to be empty
	while ( !(UCSR0A & (1 << UDRE0)) ) {
	}

	// Put the data into the data buffer register and send
	UDR0 = data;

}

void USBCommunicator::answerWheelL() {

	// catch the operand
	int8_t percentage = receive();
    uint8_t speed;
    
    if(percentage < 0){
        motors_.setDirectionLM(Motor::BACK);
        speed = ((-1) * percentage);
    } else if(percentage > 0) {
        motors_.setDirectionLM(Motor::FRWD);
        speed = percentage;
    } else {
        speed = 0;
    }
    switch(speed) {
        case 0:
            motors_.setSpeedLM(0);
            break;
        case 25:
            motors_.setSpeedLM(100);
            break;
        case 50:
            motors_.setSpeedLM(127);
            break;
        case 75:
            motors_.setSpeedLM(191);
            break;
        case 100:
            motors_.setSpeedLM(255);
            break;
    }
}

void USBCommunicator::answerWheelR() {
	
	// catch the operand
	int8_t percentage = receive();
    uint8_t speed;
    
    if(percentage < 0){
        motors_.setDirectionRM(Motor::BACK);
        speed = ((-1) * percentage);
    } else if(percentage > 0) {
        motors_.setDirectionRM(Motor::FRWD);
        speed = percentage;
    } else {
        speed = 0;
    }
    switch(speed) {
        case 0:
            motors_.setSpeedRM(0);
            break;
        case 25:
            motors_.setSpeedRM(100);
            break;
        case 50:
            motors_.setSpeedRM(127);
            break;
        case 75:
            motors_.setSpeedRM(191);
            break;
        case 100:
            motors_.setSpeedRM(255);
            break;
    }
}

void USBCommunicator::answerLed() {

	// catch the operand
	uint8_t colorData = receive();

	// update the LED
	switch(colorData) {
		case LEDCOLOR_OFF:
			led_.setColor(Led::OFF);
			break;
		case LEDCOLOR_GREEN:
			led_.setColor(Led::GREEN);
			break;
		case LEDCOLOR_RED:
			led_.setColor(Led::RED);
			break;
	}

}

void USBCommunicator::answerInfo() {

	// catch the null operand
	receive();

	sendName();
	sendTeam();
	sendSection();
	sendSemester();
	sendColor();

}

void USBCommunicator::sendName() {
	transmit(MSG_NAME);
	for(uint8_t i = 0; i < NAMESIZE; i++) {
		transmit(robotName_[i]);
	}
}

void USBCommunicator::sendTeam() {
	transmit(MSG_TEAM);
	for(uint8_t i = 0; i < NUMBERSIZE; i++) {
		transmit(teamNumber_[i]);
	}
}

void USBCommunicator::sendSection() {
	transmit(MSG_SECTION);
	transmit(sectionNumber_);
}

void USBCommunicator::sendSemester() {
	transmit(MSG_SEMESTER);
	for(uint8_t i = 0; i < SEMESTERSIZE; i++) {
		transmit(semester_[i]);
	}
}

void USBCommunicator::sendColor() {
	transmit(MSG_COLOR);
	transmit(robotColor_);
}

void USBCommunicator::sendButton() {
	transmit(MSG_BUTTON);
	if (button_.isPressed()) {
		transmit(BUTTON_PRESSED);
	} else {
		transmit(BUTTON_RELEASED);
	}
}

void USBCommunicator::sendSensorL() {
	transmit(MSG_SENSOR_L);
	transmit(sensors_.getDistanceL());
}

void USBCommunicator::sendSensorR() {
	transmit(MSG_SENSOR_R);
	transmit(sensors_.getDistanceR());
}

void USBCommunicator::updateInfo() {
	sendSensorL();
    sendSensorR();
    sendButton();
}

void USBCommunicator::checkAndAnswer() {
	uint8_t message = receive();
	if (message != 0) {
		switch(message) {
			case MSG_LED:
				answerLed();
				break;
			case MSG_WHEEL_L:
				answerWheelL();
				break;
			case MSG_WHEEL_R:
				answerWheelR();
				break;
			case MSG_INFO:
				answerInfo();
				break;
		}
	}
}
