/*
 * Nom: Flashy light program
 * Description: Makes light flash in an alternating pattern; Green, Red, Amber 
 * Version: 2.1
 */


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main()
{
    DDRA = 0xff; // PORT A est en mode sortie
    
    
    static const int TEMPSDEDUREE = 2000;
    static const int TEMPS_AMBRE = 100;
    
    uint8_t green = 0x02, red = 0x01;

    
	while (true) {                                       // boucle sans fin
        
        PORTA = green;                              // DEL en VERT
        
        _delay_ms (TEMPSDEDUREE);            		// Attendre TEMPSDEDUREE ms
        
        PORTA = red;                                // DEL en ROUGE
        
        _delay_ms (TEMPSDEDUREE);                   // Attendre TEMPSDEDUREE ms
        
        for (int i = 0; i < TEMPSDEDUREE*(1000/TEMPS_AMBRE); i++) { // Duree de temps pour la couleur ambre
			PORTA = i >> 4;
			_delay_us (TEMPS_AMBRE);
        }
        
    }    
  return 0; 
}

