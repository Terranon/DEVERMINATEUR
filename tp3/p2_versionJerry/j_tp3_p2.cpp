/*
 * Nom: j_tp3_p2.cpp
 * Description: Make the LED light up in various colors as the button is
 *              pressed and released.
 * 
 *              Pinout :    LED ( + - )
 *                                | |
 *                       PORT C ( 0 1 2 3 4 5 6 7 )
 * 
 * Version: 1.0
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main () {
    
    // C PORT output
    DDRC = 0xff;
    
    // D PORT input
    DDRD = 0x00;
    
    // in ms
    const uint8_t DEBOUNCE_TIME = 40;
    
    // in us
    const uint8_t LOOP_TIME = 100;
    
    // Constants for the LED in port 0..1
    const uint8_t OFF   = 0x00;
    const uint8_t RED   = 0x01;
    const uint8_t GREEN = 0x02;
    
    // List of all possible states fot the state machine
    enum state { INIT, SAMBER, SGREEN1, SRED, SOFF, SGREEN2 };
    
    state machine = INIT;

    // Infinite loop
    while (1){
        switch(machine) {
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case INIT : 
                
                PORTC = RED;
                
                // When the button is pressed
                if (PIND & 0x04) {
                    machine = SAMBER;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SAMBER : 
                
                //Flips the signal sent to the LED
                PORTC ^= 0x03;
                
                // When the button is released
                if (!(PIND & 0x04)) {
                    machine = SGREEN1;
                    
                    // The LED must be changed before the debounce delay,
                    // otherwise it'll flash a random color for DEBOUNCE_TIME ms
                    PORTC = GREEN;
                    
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN1 : 
                
                PORTC = GREEN;
                
                // When the button is pressed
                if (PIND & 0x04) {
                    machine = SRED;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SRED: 
                
                PORTC = RED;
                
                // When the button is released
                if (!(PIND & 0x04)) {
                    machine = SOFF;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SOFF : 
                
                PORTC = OFF;
                
                // When the button is pressed
                if (PIND & 0x04) {
                    machine = SGREEN2;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN2 : 
                
                PORTC = GREEN;
                
                // When the button is released
                if (!(PIND & 0x04)) {
                    machine = INIT;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        }
        
        _delay_us(LOOP_TIME);
    }
  return 0;
}

