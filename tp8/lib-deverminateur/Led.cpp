/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 2.0
\******************************************************************************/

#include "Led.h"

/**
 * \brief constructor for the Led; the DDRx register will be set to enable
 *        output on the appropriate pins
 * \param pwmFreq sets begining frequency of the pwm in Hz
 * \return an Led
 */
Led::Led(uint16_t pwmFreq)
    : color_(OFF),
      pwmFrequency_(pwmFreq) {
          
          DDRC = 0x03;              // sets PINC0 and PINC1 to output
}

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
        
        PORTC ^= color_;
        _delay_ms(10);
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
    
    color_(color);
    pwmFrequency_(pwmFreq);
    
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
