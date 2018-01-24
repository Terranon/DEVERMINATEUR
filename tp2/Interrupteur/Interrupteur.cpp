/*
 * Nom: Interrupteur
 * Description: activates LED when button is pushed
 * Version: 1.0
 */


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main()
{
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0x00; // PORT D est en mode entree
    
    static const short DEBOUNCETIME = 10;
    static const int TEMPSDEDUREE = 2000;
    static const int TEMPS_AMBRE = 100;
    static const short OFF = 0x00;
    
    while(1) {
        
        _delay_ms (DEBOUNCETIME);
        
        unsigned oscillator = 0;
        
        while (PIND & 0x04) {
             
            oscillator++;
            
            PORTC = oscillator >> 4;
            }
        if (!(PIND & 0x04)) {
            PORTC = OFF;
        }
    }   
  return 0; 
}

