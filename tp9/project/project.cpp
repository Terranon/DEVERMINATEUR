/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Simple test program for the library 'deverminateur'. Robot will
 *              play a note when program first begins then will move forward
 *              when the photocell senses high luminosity and backwards when it
 *              senses low luminosity. The Led will also respond to luminosity.
 * 
 * Pinout :                                      (- +) LED             Jumper  
 *                                                | |                       |
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  0 1 2 3 4 5 6 7    PORTD  1 3 5 7        
 *        0 2 4 6           0 2 4 6                                         |        
 *                                                                      0 2 4 6
 *                                                                              
 * 
 *                                                
 *                
 * 
 * Version: 1.0
\******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <Timer.h>
#include <Led.h>

/******************************************************************************\
 * Main
\******************************************************************************/

/**
 * \brief main function
 * \return exit code
 */
int main () {
    
    /*
    DDRA |= (1 << DDA0);
    DDRA |= (1 << DDA1);
    
    PORTA &= ~(1 << 0);
    
    Led led;
    Timer t;
    
    led.setColor(Led::GREEN); // initial color of the Led is green
    
    t.schedule(500);
    for (uint8_t i = 0; i < 20; i++) {
        
        while ( !t.isExpired() ) {
        }
        t.resetExpiration();
        
        led.toggleColor();
        
    }
    */
    
    
    
    
    
    
        
    return 0;
}

