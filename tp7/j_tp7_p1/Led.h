/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * Version: 1.0
\******************************************************************************/

#include <avr/io.h>

#ifndef LED_H
#define LED_H

class Led {
public:
    
    Led(uint8_t posLead, uint8_t negLead, uint8_t port);
    void setColor(uint8_t color);
    
    static const uint8_t OFF = 0;
    static const uint8_t GREEN = 1;
    static const uint8_t RED = 2;
    static const uint8_t A = 0;
    static const uint8_t B = 1;
    static const uint8_t C = 2;
    static const uint8_t D = 3;
    
private:
    
    void setPORTA(uint8_t color);
    void setPORTB(uint8_t color);
    void setPORTC(uint8_t color);
    void setPORTD(uint8_t color);
    
    uint8_t color;
    uint8_t positiveLead;
    uint8_t negativeLead;
    uint8_t port;
};

#endif // LED_H
