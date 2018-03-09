/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Button.h
 * Description: Simplify the use of a button
 * Version: 1.1
\******************************************************************************/

#include "Button.h"

/**
 * \brief constructor for the Button; the DDRx register will be set to enable
 *        input on the appropriate pins. 
 *        The EIMSK register will be set to enable corresponding intxVect 
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
Button::Button(uint8_t intxVect, uint8_t valueWhenButtonOpen)
    : xVect_(intxVect),
      openValue_(valueWhenButtonOpen) {
      
    switch(xVect_) {
        case 0 :                        // corresponds to INT0_VECT
            DDRD  &= ~(1 << DDD2); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC00);
            EICRA &= ~(1 << ISC01);
            
            break;
        case 1 :                        // corresponds to INT1_VECT
            DDRD  &= ~(1 << DDD3); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC10);
            EICRA &= ~(1 << ISC11);
            
            break;
        case 2 :                        // corresponds to INT2_VECT
            DDRB  &= ~(1 << DDB2); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC20);
            EICRA &= ~(1 << ISC21); 
            
            break;
    }
    
}

/**
 * \brief destructor for Button
 */
Button::~Button(){
}

/**
 * \brief checks if Button is pressed
 * \return a uint8_t
 */
uint8_t Button::isPressed() {
    
    uint8_t isPressed;
    switch(xVect_) {
        case 0:
            if(openValue_) {
                if(PIND & 0x04) {
                    isPressed = 0;
                } else {
                    isPressed = 1;
                }
            } else {
                if(PIND & 0x04) {
                    isPressed = 1;
                } else {
                    isPressed = 0;
                }
            }
            break;
        case 1:
            if(openValue_) {
                if(PIND & 0x08) {
                    isPressed = 0;
                } else {
                    isPressed = 1;
                }
            } else {
                if(PIND & 0x04) {
                    isPressed = 1;
                } else {
                    isPressed = 0;
                }
            }
            break;
        case 2:
            if(openValue_) {
                if(PINB & 0x04) {
                    isPressed = 0;
                } else {
                    isPressed = 1;
                }
            } else {
                if(PINB & 0x04) {
                    isPressed = 1;
                } else {
                    isPressed = 0;
                }
            }
            break;
    }
    return isPressed;
}

/**
 * \brief setter for which vector the button will activate
 * \param intxVect the interrupt vector that is to be initialized,
 *                 value between 0-2
 */
void Button::setIntxVect(uint8_t intxVect) {
    
    xVect_ = intxVect;
    
    switch(xVect_) {
        case 0 :                        // corresponds to INT0_VECT
            DDRD  &= ~(1 << DDD2); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC00);
            EICRA &= ~(1 << ISC01);
            
            break;
        case 1 :                        // corresponds to INT1_VECT
            DDRD  &= ~(1 << DDD3); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC10);
            EICRA &= ~(1 << ISC11);
            
            break;
        case 2 :                        // corresponds to INT2_VECT
            DDRB  &= ~(1 << DDB2); 
            EIMSK |= (1 << xVect_);
            EICRA |= (1 << ISC20);
            EICRA &= ~(1 << ISC21); 
            
            break;
    }
}

/**
 * \brief setter for the value that the button has when open
 * \param valueWhenButtonOpen the value of the pin connected to the button
 *                            while button is open (not pressed),
 *                            value between 0-1
 */
void Button::setValueWhenButtonOpen(uint8_t valueWhenButtonOpen) {
    
    openValue_ = valueWhenButtonOpen;
}

/**
 * \brief getter for xVect_
 * \return xVect_
 */
uint8_t Button::getIntxVect() {
    
    return xVect_;
}

/**
 * \brief getter for valueWhenButtonOpen
 * \return valueWhenButtonOpen
 */
uint8_t Button::getValueWhenButtonOpen() {
    
    return openValue_;
}

