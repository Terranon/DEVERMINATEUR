/*****************************************************************************\
 * Authors:     Maximilien Bianchi
 * Name:        Button.h
 * Description: Simplify the use of a button
 * Version: 2.0
\******************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <util/delay.h>

class Button {
public:
    
    /**
    * \brief constructor for the Button; the DDRx register will be set to enable
    *        input on the appropriate pins
    * \return a Button
    */
    Button();
    
    /**
    * \brief destructor for Button
    */
    ~Button();
    
    /**
    * \brief checks if Button is pressed for diagnostic
    * \return a uint8_t
    */
    uint8_t sendState();
    
    /**
    * \brief checks if Button is pressed
    * \return a uint8_t
    */
    uint8_t isPressed();
    
private:
    
    uint8_t isPressed_;
};

#endif // BUTTON_H
