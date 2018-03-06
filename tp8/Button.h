/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of a button
 * Version: 1.0
\******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef BUTTON_H
#define BUTTON_H

class Button {
public:
    
    Button(uint8_t intxVect, uint8_t valueWhenButtonOpen);
    
    uint8_t isPressed();
    
private:

    xVect_;
    openValue_;
};

#endif // BUTTON_H
