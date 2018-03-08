/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 1.2
\******************************************************************************/

#include "Led.h"

/**
 * \brief constructor for the Led; the DDRx register will be set to enable
 *        output on the appropriate pins
 * \return an Led
 */
Led::Led()
    : color_(OFF) {
          
        DDRC |= (1 << DDC2); // sets PORTC2 to output
        DDRC |= (1 << DDC3); // sets PORTC3 to output

    }
    
}

/**
 * \brief destructor for the Led
 */
Led::~Led() {
}

/**
 * \brief changes the color of the LED
 * \param color color of the LED, can be Led::OFF, Led::GREEN or Led::RED
 */
void Led::setColor(uint8_t color) {
    
    color_ = color;
    
    PORTC |= (color << DDC2);
}

/**
 * \brief toggles the color of the LED (green becomes red and vice versa).
 *        Has no effect if the LED is off.
 */
void Led::toggleColor() {
    
    if (color_ == RED) {
        setColor(GREEN);
    } else if (color_ == GREEN) {
        setColor(RED);
    }
    
}
