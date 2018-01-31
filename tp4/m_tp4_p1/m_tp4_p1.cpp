/*************************************************************************************************
 * Auteurs:     Maximilien Bianchi, Jean-Raphael Matte
 * Nom:         probleme_1.cpp
 * Description: Allume la Del libre en rouge et l'eteint progressivement, et repete en vert.
 * Utilisation: Pinout:      Del libre ( + - )
 *                                       | |
 *                              PORT D ( 0 1 2 3 4 5 6 7 )
 ************************************************************************************************/
 
 
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

/*************************************************************************************************
 * Declaration des modes des PORTS et constantes.
 ************************************************************************************************/

const uint16_t FREQUENCY = 1000;  // 1000 us (1 ms) correspond a une frequence de 1 kHz.
const uint16_t ONTIME    = 3000;  // Correspond au nombre de cycle dans la fonction pwm. 
                                  // 3000 us x 1000 us donne 3 secondes pour chaque execution de la fonction pwm.
const uint8_t  RED       = 0x01;  // Del libre couleur rouge
const uint8_t  GREEN     = 0x02;  // Del libre couleur verte
const uint8_t  OFF       = 0x0;   // Del libre eteinte

/*************************************************************************************************
 * Fonction wait: prend la variable delay comme operateur pour attendre 10 x delay us.
 ************************************************************************************************/

void wait(uint16_t delay) {
    
    for (uint16_t i = 0; i < delay; i++){
        _delay_us (10);
    }
}

/*************************************************************************************************
 * Fonction pwm: prend la couleur, le nombre de cycle et la frequence comme parametre.
 * Dans ce cas on execute 3000 boucle (ONTIME) de 1000 us (FREQUENCY).
 ************************************************************************************************/

void pwm(uint8_t color, uint16_t ONTIME, uint16_t FREQUENCY) {
    
    for (uint16_t i = 0; i < ONTIME; i++) {
        
        uint16_t delayRed = (FREQUENCY - (i/(ONTIME/FREQUENCY)) );
        uint16_t delayOff = (i/(ONTIME/FREQUENCY));
        
        PORTD = color;      // delayRed + delayOff devrait toujours s'additionner a 1000
        wait(delayRed/10);   // on divise toujours par 10 pour compenser le multiple de 10
                            // existant dans la fonction wait.
        PORTD = OFF;
        wait(delayOff/10);
    }
}

/*************************************************************************************************
 * Fonction main: Contient les deux etats possible de Del libre, soit allume en rouge ou en vert.
 ************************************************************************************************/

int main() {
    
    DDRD = 0xff; // PORT D est en mode sortie
    
    enum state { red, green } s = red;   
    
    while(true) {             // boucle sans fin
                 
        switch(s) {
        
            case red :
                pwm(RED, ONTIME, FREQUENCY);
                s = green;
            break;
        
            case green :
                pwm(GREEN, ONTIME, FREQUENCY);
                s = red;
            break;
            
    }
  }
  return 0; 
}
