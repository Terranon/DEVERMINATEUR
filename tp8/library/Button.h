/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Button.h
 * Description: Simplify the use of a button
 * Version: 1.1
\******************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

class Button {
public:
    
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
    Button(uint8_t intxVect, uint8_t valueWhenButtonOpen);
    
    /**
    * \brief destructor for Button
    */
    ~Button();
    
    /**
    * \brief checks if Button is pressed
    * \return a uint8_t
    */
    uint8_t isPressed();
    
    /**
    * \brief setter for which vector the button will activate
    * \param intxVect the interrupt vector that is to be initialized,
    *                 value between 0-2
    */
    void setIntxVect(uint8_t intxVect);
    
    /**
    * \brief setter for the value that the button has when open
    * \param valueWhenButtonOpen the value of the pin connected to the button
    *                            while button is open (not pressed),
    *                            value between 0-1
    */
    void setValueWhenButtonOpen(uint8_t valueWhenButtonOpen);
    
    /**
    * \brief getter for xVect_
    * \return xVect_
    */
    uint8_t getIntxVect();

    /**
    * \brief getter for valueWhenButtonOpen
    * \return valueWhenButtonOpen
    */
    uint8_t getValueWhenButtonOpen();
    
private:

    uint8_t xVect_;
    uint8_t openValue_;
};

#endif // BUTTON_H
