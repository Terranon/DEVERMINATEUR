/*
 * Nom: versionJerry.cpp
 * Description: Make the LED light up for a second after the button is pressed
 *              5 times.
 * 
 *              Pinout :    LED ( - + )
 *                                | |
 *                       PORT A ( 0 1 2 3 4 5 6 7 8 )
 * 
 * Version: 1.0
 */


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main () {
    // A PORT output
    DDRA = 0xff;
    
    // D PORT input
    DDRD = 0x00;
    
    // in ms
    const int DEBOUNCE_TIME = 40;
    const int ON_TIME = 1000;
    const int LOOP_TIME = 1;
    
    // Constants for the LED in port 0..1
    const uint8_t RED   = 0x01;
    const uint8_t OFF   = 0x00;
    
    enum state { INIT, EA };
    
    state machine = INIT;
    
    uint8_t counter = 0;
    
    uint8_t btnWasPressed = 0;
    uint8_t btnIsPressed = 0;

    // infinite loop
    while (1){
        switch(machine) {
            case INIT : 
                
                // Turn off the LED
                PORTA = OFF;
                
                // Save previous button state
                btnWasPressed = btnIsPressed;
                
                // Debouncer
                if (PIND & 0x04) {
                    btnIsPressed = 1;
                    _delay_ms(DEBOUNCE_TIME);
                } else {
                    btnIsPressed = 0;
                }
                
                // On the rising edge, increase the counter
                if (!btnWasPressed && btnIsPressed) {
                    counter++;
                }
                
                // Change state when counter is >= 5
                if (counter >= 5) {
                    machine = EA;
                }
                
            break;
            case EA : 
                
                // Turn on the LED
                PORTA = RED;
                
                // Reset the counter
                counter = 0;
                
                // Wait for the specified time
                _delay_ms(ON_TIME);
                
                // Return to default state
                machine = INIT;
                
            break;
        }
        _delay_ms(LOOP_TIME);
    }
  return 0;
}

