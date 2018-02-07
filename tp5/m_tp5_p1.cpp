/*****************************************************************************\
 * Authors:     Maximilien Bianchi, Jean-Raphael Matte
 * Name:        m_tp5_p1.cpp
 * Description: Make the LED light up in various colors as the button is
 *              pressed and released, using interrupts.
 * 
 *              Pinout :    LED ( + - )
 *                                | |
 *                       PORT C ( 0 1 2 3 4 5 6 7 )
 * 
 * Version: 1.0
\******************************************************************************/

/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/
#include <m_tp5_p1.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

/******************************************************************************\
 * Main
\******************************************************************************/
int main () {
    
    
    
    // List of all possible states for the state machine
    enum state { INIT, SAMBER, SGREEN1, SRED, SOFF, SGREEN2 };
    
    state machine = INIT;

    // Infinite loop
    while (1){
        
        // Behavior for all states
        switch(machine) {
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case INIT : 
                
                PORTC = RED;
                
                // When the button is pressed
                if (PIND & 0x04) {
                    
                    // Change state
                    machine = SAMBER;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SAMBER : 
                
                //Flips the signal sent to the LED
                PORTC ^= 0x03;
                
                // When the button is released
                if (!(PIND & 0x04)) {
                    
                    // Change state
                    machine = SGREEN1;
                    
                    // The LED must be changed before the debounce delay,
                    // otherwise it'll flash a random color for DEBOUNCE_TIME ms
                    PORTC = GREEN;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN1 : 
                
                PORTC = GREEN;
                
                // When the button is pressed
                if (PIND & 0x04) {
                    
                    // Change state
                    machine = SRED;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SRED: 
                
                PORTC = RED;
                
                // When the button is released
                if (!(PIND & 0x04)) {
                    
                    // Change state
                    machine = SOFF;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SOFF : 
                
                PORTC = OFF;
                
                // When the button is pressed
                if (PIND & 0x04) {
                    
                    // Change state
                    machine = SGREEN2;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN2 : 
                
                PORTC = GREEN;
                
                // When the button is released
                if (!(PIND & 0x04)) {
                    
                    // Change state
                    machine = INIT;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        }
        
        _delay_us(LOOP_TIME);
    }
  return 0;
}

