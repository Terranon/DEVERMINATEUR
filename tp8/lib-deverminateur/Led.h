/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 1.1
\******************************************************************************/

#include <avr/io.h>

#ifndef LED_H
#define LED_H

class Led {
public:
    
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
    Led(uint8_t posLead, uint8_t negLead, uint8_t port);
    
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
    
    /**
     * \brief these constants set the value of the possible ports; either A, B, C or D
     */
    static const uint8_t A = 0;
    static const uint8_t B = 1;
    static const uint8_t C = 2;
    static const uint8_t D = 3;
    
private:
    
    /**
    * \brief changes the color of an LED in PORTA
    * \param color color of the LED, can be OFF, GREEN or RED
    */
    void setPORTA(uint8_t color);
    
    /**
    * \brief changes the color of an LED in PORTB
    * \param color color of the LED, can be OFF, GREEN or RED
    */
    void setPORTB(uint8_t color);
    
    /**
    * \brief changes the color of an LED in PORTC
    * \param color color of the LED, can be OFF, GREEN or RED
    */
    void setPORTC(uint8_t color);
    
    /**
    * \brief changes the color of an LED in PORTD
    * \param color color of the LED, can be OFF, GREEN or RED
    */
    void setPORTD(uint8_t color);
    
    uint8_t color_;
    uint8_t positiveLead_;
    uint8_t negativeLead_;
    uint8_t port_;
};

#endif // LED_H
