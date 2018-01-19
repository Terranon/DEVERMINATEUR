/*
 * Nom: amber_button.cpp
 * Description: Make the LED amber when button is pressed 
 * Version: 2.0
 */


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main () {
	// PORT A output
    DDRA = 0xff;
    
    // PORT D input
    DDRD = 0x00;
    
    const int TEMPS_ANTIREBOND = 10000;
    const int TEMPS_AMBRE = 100;
    
    const uint8_t GREEN = 0x02;
    const uint8_t RED = 0x01;
	
    // infinite loop
    while (1){
		if (PIND & 0x04) {
			for (int i = 0; i < TEMPS_ANTIREBOND/(2*TEMPS_AMBRE); i++) {
				PORTA = GREEN;
				_delay_us(TEMPS_AMBRE);
				PORTA = RED;
				_delay_us(TEMPS_AMBRE);
			}
		} else {
			PORTA = 0x00;
			_delay_us(TEMPS_ANTIREBOND);
		}
    }
  return 0;
}

