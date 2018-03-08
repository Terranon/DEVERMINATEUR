/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.cpp
 * Description: Simplify the use of an LED
 * Version: 2.0
\******************************************************************************/

#include "Led.h"

/**
 * \brief constructor for the Led; the DDRC register will be set to enable
 *        output on the appropriate pins
 * \param pwmFreq sets begining frequency of the pwm in Hz
 * \return an Led
 */
Led::Led(uint16_t pwmFreq)
    : color_(OFF),
      pwmFrequency_(pwmFreq) {

        DDRB = 0x06;              // sets PINB3 and PINB4 to output
        
        // TCCR0A/TCCR0B are the Timer/Counter Control Registers 0 A/B]
    
        // ~~~TCCR0A~~~
        
        TCCR0A |= (3 << COM0A0);
        TCCR0A |= (2 << COM0B0);
        TCCR0A |= (1 << WGM00);
        TCCR0A &= ~(1 << WGM01);
    
        // ~~~TCCR0B~~~
        TCCR0B |= (0 << FOC0A);
        TCCR0B |= (0 << FOC0B);
        TCCR0B &= ~(1 << WGM02);
        TCCR0B |= (5 << CS00);
    
        // TIMSK0 is the Timer Interrupt Mask Register 0
        TIMSK0 &= ~(0 << ICIEA);
        TIMSK0 &= ~(0 << ICIEB);
        TIMSK0 &= ~(0 << TOIE);
        
        TCNT0 = 0;
*/
}

/**
 * \brief destructor for the Led
 */
Led::~Led() {
}

/**
 * \brief makes Led flash in an amberColor for a specified amout of time then turns LED off
 * \param time length of time that the led will flash with an amber color in miliseconds
 */
void Led::amberColor(float time) {
    
    color_ = AMBER;
    
    float nLoopIterations = time / 10;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
<<<<<<< HEAD
        PORTC ^= color_;            // toggles the pins of PORTC to produce an amber color
        delay_ms(10);
=======
        PORTC ^= color_;
        _delay_ms(10);
>>>>>>> c1d4d7ace8317714917fdbbbb4216676e6dd4f41
    }
    
    color_ = OFF;
    PORTC = OFF;
}

/**
 * \brief changes the color of the LED (time must be specified if chosen color is amber
 * \param color color of the LED, can be Led::OFF, Led::GREEN, Led::RED OR Led::AMBER
 * \param time length of time for LED to stay on in amber, in miliseconds
 */
void Led::setColor(uint8_t color, float time) {
    
    color_ = color;
    
    if (color_ == AMBER) {
        
        amberColor(time);
    }
    else {
    
        PORTC = color_;
    }
}

/**
 * \brief changes LED to specified color with PWM
 * \param color color of the LED, can be Led::GREEN, Led::RED OR Led::AMBER
 * \param onTime period of time for LED to stay on in miliseconds
 * \param offTime period of time for LED to stay off in miliseconds
 */
void Led::setPwmColor(uint8_t color, float onTime, float offTime) {
    
    color_ = color;
    
    if(color == AMBER) {
        amberColor(onTime);
        PORTC = OFF;
        delay_ms(offTime);
    }
    else {
        PORTC = color;
        delay_ms(onTime);
        PORTC = OFF;
        delay_ms(offTime);
    }
}

/**
 * \brief changes behavior of pwm for led; for practicality
 * \param percentOn sets the percentage of time where waveform is ON
 * \param pwmFreq sets the frequency of the waveform of the pwm
 * \param time length of time that the led is on in miliseconds
 */
void Led::setPwm(uint8_t color, uint16_t pwmFreq, uint32_t time, float percentOn) {
    
    color_ = color;
    pwmFrequency_ = pwmFreq;
    
    uint32_t nLoopIterations = time / pwmFreq;
    float onTime = pwmFreq * (percentOn / 100);
    float offTime = pwmFreq - onTime;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
        switch(color){
            case GREEN
                setPwmColor(GREEN, onTime, offTime);
                break;
            case RED
                setPwmColor(RED, onTime, offTime);
                break;
            case AMBER
                setPwmColor(AMBER, onTime, offTime);
                break;
        }
    }
}

/**
 * \brief toggles the color of the LED (green becomes red and vice versa).
 *        Has no effect if the LED is off.
 */
void Led::toggleColor() {
    
    if (color_ == RED) {
        PORTC = GREEN;
    } else if (color_ == GREEN) {
        PORTC = RED;
    }
}

/**
 * \brief gets value of color_
 * \return a color_
 */
uint8_t Led::getColor() {
    return color_;
}

/**
 * \brief gets value of pwmFrequency_
 * \return a pwmFrequency_
 */
uint16_t Led::getPwmFrequency() {
    return pwmFrequency_;
}
