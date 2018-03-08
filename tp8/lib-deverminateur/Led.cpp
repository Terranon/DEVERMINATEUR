/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 1.1
\******************************************************************************/

#include "Led.h"

/**
 * \brief constructor for the Led; the DDRx register will be set to enable
 *        output on the appropriate pins
 * \param posLead the pin on which the positive lead of the LED is connected,
 *                value between 0-7
 * \param negLead the pin on which the negative lead of the LED is connected,
 *                value between 0-7
 * \param port the port on which the LED is connected, can be Led::A, Led::B,
 *             Led::C or Led::D
 * \return an Led
 */
Led::Led(uint8_t posLead, uint8_t negLead, uint8_t port)
    : positiveLead_(posLead),
      negativeLead_(negLead),
      port_(port),
      color_(OFF) {
          
    switch(port_) {
        case A :
            DDRA |= (1 << positiveLead_); 
            DDRA |= (1 << negativeLead_);
            break;
        case B :
            DDRB |= (1 << positiveLead_); 
            DDRB |= (1 << negativeLead_);
            break;
        case C :
            DDRC |= (1 << positiveLead_); 
            DDRC |= (1 << negativeLead_);
            break;
        case D :
            DDRD |= (1 << positiveLead_); 
            DDRD |= (1 << negativeLead_);
            break;
    }
    
}

/**
 * \brief destructor for the Led
 */
~Led::Led() {
}

/**
 * \brief changes the color of the LED
 * \param color color of the LED, can be Led::OFF, Led::GREEN or Led::RED
 */
void Led::setColor(uint8_t color) {
    
    color_ = color;
    
    switch(port_) {
        case A :
            this->setPORTA(color);
            break;
        case B :
            this->setPORTB(color);
            break;
        case C :
            this->setPORTC(color);
            break;
        case D :
            this->setPORTD(color);
            break;
    }
        
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

/**
 * \brief changes the color of an LED in PORTA
 * \param color color of the LED, can be OFF, GREEN or RED
 */
void Led::setPORTA(uint8_t color) {
    switch(color) {
        case OFF :
            PORTA &= ~(1 << positiveLead_);
            PORTA &= ~(1 << negativeLead_);
            break;
        case GREEN :
            PORTA &= ~(1 << positiveLead_);
            PORTA |= (1 << negativeLead_);
            break;
        case RED :
            PORTA |= (1 << positiveLead_);
            PORTA &= ~(1 << negativeLead_);
            break;
    }
}

/**
 * \brief changes the color of an LED in PORTB
 * \param color color of the LED, can be OFF, GREEN or RED
 */
void Led::setPORTB(uint8_t color) {
    switch(color) {
        case OFF :
            PORTB &= ~(1 << positiveLead_);
            PORTB &= ~(1 << negativeLead_);
            break;
        case GREEN :
            PORTB &= ~(1 << positiveLead_);
            PORTB |= (1 << negativeLead_);
            break;
        case RED :
            PORTB |= (1 << positiveLead_);
            PORTB &= ~(1 << negativeLead_);
            break;
    }
}

/**
 * \brief changes the color of an LED in PORTC
 * \param color color of the LED, can be OFF, GREEN or RED
 */
void Led::setPORTC(uint8_t color) {
    switch(color) {
        case OFF :
            PORTC &= ~(1 << positiveLead_);
            PORTC &= ~(1 << negativeLead_);
            break;
        case GREEN :
            PORTC &= ~(1 << positiveLead_);
            PORTC |= (1 << negativeLead_);
            break;
        case RED :
            PORTC |= (1 << positiveLead_);
            PORTC &= ~(1 << negativeLead_);
            break;
    }
}

/**
 * \brief changes the color of an LED in PORTD
 * \param color color of the LED, can be OFF, GREEN or RED
 */
void Led::setPORTD(uint8_t color) {
    switch(color) {
        case OFF :
            PORTD &= ~(1 << positiveLead_);
            PORTD &= ~(1 << negativeLead_);
            break;
        case GREEN :
            PORTD &= ~(1 << positiveLead_);
            PORTD |= (1 << negativeLead_);
            break;
        case RED :
            PORTD |= (1 << positiveLead_);
            PORTD &= ~(1 << negativeLead_);
            break;
    }
}
