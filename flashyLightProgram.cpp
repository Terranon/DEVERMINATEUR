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
    
    static const int TEMPSDEDUREE = 2;
    
    uint8_t green = 0x02, red = 0x01;
    
    typedef enum { false, true } bool;
    
    while(true){                                        // boucle sans fin
        
        PORTA = green;                              // DEL en VERT
        
        for (int i = 0; i < TEMPSDEDUREE; i++) {    // Attendre TEMPSDEDUREEx1000ms
            _delay_ms (1000);
        }
        
        PORTA = red;                                // DEL en ROUGE
        
        for (int i = 0; i < TEMPSDEDUREE; i++) {    // Attendre TEMPSDEDUREEx1000ms
            _delay_ms (1000);
        }
        
        unsigned compteur = 1;
        PORTA = compteur >> 4;                      // DEL en AMBRE commence une fois que le compteur change de valeur
        
        do {                                        // Loop commence a 1 alors la condition de sortie est seulement vrais quand compteur retourne a 0
        compteur++
        } while (compteur != 0)
        
  return 0; 
}

