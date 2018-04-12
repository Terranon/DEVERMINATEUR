/******************************************************************************\
 * Authors:     Maximilien Bianchi
 * Name:        Button.cpp
 * Description: Simplify the use of a button
 * Version: 2.0
\******************************************************************************/

#include "Button.h"

/**
 * \brief constructor for the Button; the DDRx register will be set to enable
 *        input on the appropriate pin
 * \return a Button
 */
Button::Button() {
	DDRD &= ~(1 << DDD2);
}

/**
 * \brief destructor for Button
 */
Button::~Button(){
}

/**
 * \brief checks if Button is pressed for diagnostic
 * \return a uint8_t
 */
uint8_t Button::sendState() {
	
	// debounce time
	_delay_ms(10);
	
	uint8_t state;
	if(PIND & 0x04) {
		// button is pressed
	    state = 0x00;
	} else {
		// button is not pressed
	    state = 0x01;
	}
	return state;
	
}

/**
 * \brief checks if Button is pressed for obstacle course
 * \return a uint8_t
 */
uint8_t Button::isPressed() {
	
	// debounce time
	_delay_ms(10);
	
	uint8_t isPressed;
	if(PIND & 0x04) {
		// button is pressed
	    isPressed = 0x01;
	} else {
		// button is not pressed
	    isPressed = 0x00;
	}
	return isPressed;
}

