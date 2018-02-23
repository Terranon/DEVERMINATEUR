/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 1.0
\******************************************************************************/

#include "Led.h"

/**
 * \breif constructor for the Led
 * \param posLead the pin on which the positive lead of the LED is connected,
 *                value between 0-7
 * \param negLead the pin on which the negative lead of the LED is connected,
 *                value between 0-7
 * \param port the port on which the LED is connected, can be Led::A, Led::B,
 *             Led::C or Led::D
 * \return an Led
 */
Led::Led(uint8_t posLead, uint8_t negLead, uint8_t port):
    positiveLead(posLead),
    negativeLead(negLead),
    port(port)
{}

/**
 * \brief changes the color of the LED
 * \param color color of the LED, can be Led::OFF, Led::GREEN or Led::RED
 */
void Led::setColor(uint8_t color) {
    
    switch(this->port) {
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
 * \brief changes the color of an LED in PORTA
 * \param color color of the LED, can be OFF, GREEN or RED
 */
void Led::setPORTA(uint8_t color) {
    switch(color) {
        case OFF :
            PORTA &= ~(1 << positiveLead);
            PORTA &= ~(1 << negativeLead);
            break;
        case GREEN :
            PORTA &= ~(1 << positiveLead);
            PORTA |= (1 << negativeLead);
            break;
        case RED :
            PORTA |= (1 << positiveLead);
            PORTA &= ~(1 << negativeLead);
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
            PORTB &= ~(1 << positiveLead);
            PORTB &= ~(1 << negativeLead);
            break;
        case GREEN :
            PORTB &= ~(1 << positiveLead);
            PORTB |= (1 << negativeLead);
            break;
        case RED :
            PORTB |= (1 << positiveLead);
            PORTB &= ~(1 << negativeLead);
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
            PORTC &= ~(1 << positiveLead);
            PORTC &= ~(1 << negativeLead);
            break;
        case GREEN :
            PORTC &= ~(1 << positiveLead);
            PORTC |= (1 << negativeLead);
            break;
        case RED :
            PORTC |= (1 << positiveLead);
            PORTC &= ~(1 << negativeLead);
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
            PORTD &= ~(1 << positiveLead);
            PORTD &= ~(1 << negativeLead);
            break;
        case GREEN :
            PORTD &= ~(1 << positiveLead);
            PORTD |= (1 << negativeLead);
            break;
        case RED :
            PORTD |= (1 << positiveLead);
            PORTD &= ~(1 << negativeLead);
            break;
    }
}
