/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 2.0
\******************************************************************************/

#include <avr/io.h>
#include <avr/delay.h>

#ifndef LED_H
#define LED_H

class Led {
public:
    
    /**
    * \brief constructor for the Led; the DDRC register will 
    *        be set to enable output on the appropriate pins
    * \param pwmFreq sets begining frequency of the pwm in Hz
    * \return an Led
    */
    Led(uint16_t pwmFreq);
    
    /**
    * \brief destructor for the Led
    */
    ~Led();
    
    /**
    * \brief makes Led flash in an amberColor for a specified amout of time
    * \param time length of time that the led will flash with an amber color in miliseconds
    */
    void amberColor(float time);
    
    /**
     * \brief changes the color of the LED
     * \param color color of the LED, can be Led::OFF, Led::GREEN or Led::RED
     */
    void setColor(uint8_t color);
    
    /**
    * \brief changes behavior of pwm for led
    * \param percentOn sets the percentage of time where waveform is ON
    * \param pwmFreq sets the frequency of the waveform of the pwm
    * \param time length of time that the led is on in miliseconds
    */
    void setPwm(float percentOn, uint16_t pwmFreq, uint32_t time);
    
    /**
     * \brief toggles the color of the LED (green becomes red and vice versa).
     *        Has no effect if the LED is off.
     */
    void toggleColor();
    
    /**
    * \brief gets value of color_
    * \return a color_
    */
    uint8_t getColor();
    
    /**
    * \brief gets value of pwmFrequency_
    * \return a pwmFrequency_
    */
    uint16_t getPwmFrequency()
    
    /** 
     * \brief These constants define the value of color_
     */
    static const uint8_t OFF = 0;
    static const uint8_t GREEN = 1;
    static const uint8_t RED = 2;
    static const uint8_t AMBER = 3;

private:
    
    /**
    * \brief changes LED to specified color with PWM
    * \param color color of the LED, can be Led::GREEN, Led::RED OR Led::AMBER
    * \param onTime period of time for LED to stay on in miliseconds
    * \param offTime period of time for LED to stay off in miliseconds
    */
    void Led::setPwmColor(uint8_t color, float onTime, float offTime);
    
    /**
     * \brief The color of the LED; can be OFF, RED, GREEN or AMBER
     */ 
    uint8_t color_;
    
    /**
     * \brief The frequency that the pwm
     */
    uint16_t pwmFrequency_;
    
};

#endif // LED_H
