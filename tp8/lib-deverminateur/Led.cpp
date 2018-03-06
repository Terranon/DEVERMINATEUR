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
 * \param posLead the pin on which the positive lead of the LED is connected,
 *                value between 0-7
 * \param negLead the pin on which the negative lead of the LED is connected,
 *                value between 0-7
 * \param port the port on which the LED is connected, can be Led::A, Led::B,
 *             Led::C or Led::D
 * \return an Led
 */
Led::Led()
    : color_(OFF),
      pwmFrequency_(LA) {
    
}
/**
 * \brief makes Led flash in an amberColor
 */
void Led::amberColorInfinite() {
    
    while(1) {
        PORTC ^= 0x03;
    }
}

/**
 * \brief makes Led flash in an amberColor for a specified amout of time
 * \param time length of time that the led will flash with an amber color
 */

void Led::amberColor(uint8_t time) {
    
    uint8_t nLoopIterations = time / 10;
    
    for(uint8_t i = 0; i < nLoopIterations; i++) {
        
        PORTC ^= 0x03;
        delay_ms(10);
    }
}

/**
 * \brief changes behavior of pwm for led
 * \param percentOn sets the percentage of time where waveform is ON
 * \param pwmFreq sets the frequency of the waveform of the pwm
 * \param time length of time that the led is on
 */
void Led::setPwm(float percentOn, uint8_t pwmFreq, uint32_t time) {
    
    uint32_t nLoopIterations = time / pwmFreq;
    uint8_t onTime = pwmFreq * (percentOn / 100);
    uint8_t offTime = pwmFreq - onTime;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
        Led::amberColor(onTime);
        PORTC = OFF;
        delay_us(offTime);
    }
}

/**
 * \brief changes the color of the LED
 * \param color color of the LED, can be Led::OFF, Led::GREEN, Led::RED OR Led::AMBER
 */
void Led::setColor(uint8_t color) {
    
    color_ = color;
    
    if (color == AMBER) {
        
        Led::amberColorInfinite();
    }
    else {
    
        setPORTC(color);
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
