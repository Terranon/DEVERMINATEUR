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
Button::Button(uint8_t intxVect, uint8_t valueWhenButtonOpen)
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
 * \brief destructor for Button
 */
~Button::Button(){
}

/**
 * \brief setter for which vector the button will activate
 * \param intxVect the interrupt vector that is to be initialized,
 *                 value between 0-2
 */
void Led::setIntxVect(uint8_t intxVect) {
    
    xVect_ = INTx_VECT;
    
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
 * \brief setter for the value that the button has when open
 * \param valueWhenButtonOpen the value of the pin connected to the button
 *                            while button is open (not pressed),
 *                            value between 0-1
 */
void Led::setValueWhenButtonOpen(uint8_t valueWhenButtonOpen) {
    
    openValue_ = valueWhenButtonOpen;
}

/**
 * \brief getter for xVect_
 * \return xVect_
 */
uint8_t Led::getIntxVect() {
    
    return xVect_;
}

/**
 * \brief getter for valueWhenButtonOpen
 * \return valueWhenButtonOpen
 */
uint8_t Led::getValueWhenButtonOpen() {
    
    return openValue_;
}

