/*****************************************************************************\
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
Button::Button()
    :  isPressed_(),
       sendState_(){
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
    
    if(PIND & 0x04) {
        _delay_ms(10);     // debounce time
        sendState_ = 0x00; // button is pressed
    } else {
        _delay_ms(10);     // debounce time
        sendState_ = 0x01; // button is not pressed
    }
    return sendState_;
}

/**
 * \brief checks if Button is pressed for obstacle course
 * \return a uint8_t
 */
uint8_t Button::isPressed() {
    
    if(PIND & 0x04) {
        _delay_ms(10);     // debounce time
        isPressed_ = 0x01; // button is pressed
    } else {
        _delay_ms(10);     // debounce time
        isPressed_ = 0x00; // button is not pressed
    }
    return isPressed_;
}

