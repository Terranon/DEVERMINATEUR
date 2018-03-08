/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 1.2s
\******************************************************************************/

#include <avr/io.h>

#ifndef LED_H
#define LED_H



class Led {
public:
    
    /**
    * \brief constructor for the Led; the DDRx register will be set to enable
    *        output on the appropriate pins
    * \return an Led
    */
    Led();
    
    /**
    * \brief destructor for the Led
    */
    ~Led();
    
    /**
    * \brief changes the color of the LED
    * \param color color of the LED, can be Led::OFF, Led::GREEN or Led::RED
    */
    void setColor(uint8_t color);
    
    /**
    * \brief toggles the color of the LED (green becomes red and vice versa).
    *        Has no effect if the LED is off.
    */
    void toggleColor();
    
    /**
    * \brief these constants represent the value of the LED; either OFF, GREEN or RED
    */
    static const uint8_t OFF = 0;
    static const uint8_t GREEN = 1;
    static const uint8_t RED = 2;
    
private:
        
    uint8_t color_;
};

#endif // LED_H
