/*
 * Nom: j_tp3_p2.cpp
 * Description: Make the LED light up in various colors as the button is
 *              pressed and released.
 * 
 *              Pinout :    LED ( - + )
 *                                | |
 *                       PORT C ( 0 1 2 3 4 5 6 7 8 )
 * 
 * Version: 1.0
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define TIMER_SIZE 4U

// Time keeping structure
struct timer {
    uint8_t ms[TIMER_SIZE];
};

void incrementTimer (&timer t) {
    for (int i = 0; i < TIMER_SIZE+1; i++) {
        if (t.ms[TIMER_SIZE-(i+1)] == 0xff) {
            t.ms[TIMER_SIZE-(i)]++;
        }
    }
    t.ms[0]++;
}

uint8_t wait (uint8_t ms, uint8_t multiplier) {
    
}

int main () {
    
    // C PORT output
    DDRC = 0xff;
    
    // D PORT input
    DDRD = 0x00;
    
    // in ms
    const uint8_t DEBOUNCE_TIME = 40;
    
    // in us
    const uint8_t LOOP_TIME = 1000;
    
    // Time keeping variable
    timer time;
    
    // Constants for the LED in port 0..1
    const uint8_t OFF   = 0x00;
    const uint8_t RED   = 0x01;
    const uint8_t GREEN = 0x02;
    
    enum state { INIT, SAMBER, SGREEN1, SRED, SOFF, SGREEN2 };
    
    state machine = INIT;
    
    

    // Infinite loop
    while (1){
        switch(machine) {
            case INIT : 
                
                PORTC = RED;
                
                
                if (PIND & 0x04) {
                    
                }
                if () {
                    machine = SAMBER;
                }
                
            break;
            case SAMBER : 
                
                //Flips the signal sent to the LED
                PORTC ^= 0x03;
                
                if (!(PIND & 0x04)) {
                    machine = SGREEN1;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            case SGREEN1: 
                
                PORTC = GREEN;
                
                if (PIND & 0x04) {
                    machine = SRED;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            case SRED : 
                
                PORTC = RED;
                
                if (!(PIND & 0x04)) {
                    machine = SOFF;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            case SOFF : 
                
                PORTC = OFF;
                
                if (PIND & 0x04) {
                    machine = SGREEN2;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            case SGREEN2 : 
                
                PORTC = GREEN;
                
                if (!(PIND & 0x04)) {
                    machine = INIT;
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
        }
        
        incrementTimer(time);
        
        _delay_us(LOOP_TIME);
    }
  return 0;
}

