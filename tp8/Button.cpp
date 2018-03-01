/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of a button
 * Version: 1.0
\******************************************************************************/

#include "Button.h"

/**
 * \brief constructor for the Button; the DDRx register will be set to enable
 *        input on the appropriate pins. 
 *        The EIMSK register will be set to enable corresponding INTx_VECT 
 *        to make external interrupts. 
 *        The EICRA register is set to control the behavior of the interrupt 
 *        vector. Value 01 corresponds to any logical change generating an 
 *        interrupt request.
 * \param intxVect            the interrupt vector that is to be initialized,
 *                            value between 0-2
 * \param valueWhenButtonOpen the value of the pin connected to the button
 *                            while button is open (not pressed),
 *                            value between 0-1
 * \return a Button
 */
namespace {
    uint8_t isPressed;
}

Button::button(uint8_t intxVect, uint8_t valueWhenButtonOpen)
    : xVect_(intxVect),
      openValue_(valueWhenButtonOpen) {
      
    switch(xVect_) {
        case 0 :                        // corresponds to INT0_VECT
            DDRD  &= ~(0 << DDD2); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC00);
            EICRA &= ~(0 << ISC01);
            
            break;
        case 1 :                        // corresponds to INT1_VECT
            DDRD  &= ~(0 << DDD3); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC10);
            EICRA &= ~(0 << ISC11);
            
            break;
        case 2 :                        // corresponds to INT2_VECT
            DDRB  &= ~(0 << DDB2); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC20);
            EICRA &= ~(0 << ISC21); 
            
            break;
    }
    
}

/**
 * \brief Getter for isPressed.
 * \return isPressed;
 */

uint8_t isPressed() {
    return isPressed;
}

/**
 * \brief The three ISRs each correspond to an interrupt vector. Setting 
 *        variable isPressed to appropriate value.
 */

ISR (INT0_VECT) {
    
    if (openValue_) {
        
        if (PIND & (1 << PIND2)) {
            isPressed = 0;
        } 
        else {
            isPressed = 1;
        }
    }
    else {
        if (PIND & (1 << PIND2)) {
            isPressed = 1;
        } 
        else {
            isPressed = 0;
        }
    }
}

ISR (INT1_VECT){
    
    if (openValue_) {
        
        if (PIND & (1 << PIND3)) {
            isPressed = 0;
        } 
        else {
            isPressed = 1;
        }
    }
    else {
        if (PIND & (1 << PIND3)) {
            isPressed = 1;
        } 
        else {
            isPressed = 0;
        }
    }
}

ISR (INT2_VECT){
    
    if (openValue_) {
        
        if (PIND & (1 << PINB2)) {
            isPressed = 0;
        } 
        else {
            isPressed = 1;
        }
    }
    else {
        if (PIND & (1 << PINB2)) {
            isPressed = 1;
        } 
        else {
            isPressed = 0;
        }
    }
}
