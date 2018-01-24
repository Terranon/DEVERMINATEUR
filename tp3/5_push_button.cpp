/****************************************************************************************
 * Nom:         Flashy light program
 * Description: Si le bouton est pousser 5 fois, la DEL libre s'allume en ROUGE pour 1 seconde
 * Utilisation: Brancher fil MAUVE sur PORTC-1 et BLANC sur PORTC-2. Ensuit brancher MAUVE sur borne + et BLANC sur la borne - de DEL libre
 *              Pesez bouton 5 fois pour allumer DEL libre pour 1 seconde.
 * Version:     2.1
 ***************************************************************************************/


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

/*Declaration des constantes*/

DDRC = 0xff;                        // PORT C est en mode sortie
DDRD = 0x00;                        // PORT D est en mode entree
    
const short DEBOUNCETIME = 40;      // 40 ms de antirebond
const int ONTIME = 1000;            // 1000 ms d'attente
const uint8_t red = 0x01;           // DEL couleur rouge
const uint8_t off - 0x00;           // DEL eteinte

/****************************************************************************************
 * Fonction buttonCondition
 ***************************************************************************************/

void buttonCondition(&buttonIsPressed, &buttonWasPressed) {
    
    buttonWasPressed = buttonIsPressed;   // buttonWasPressed prend la valeur de buttonIsPressed 
                                          // pour empecher qu'on continue a augmenter le buttonPushCounter
    
    if (PIND & 0x04) {                    // Si le bouton est pese ...
        buttonIsPressed = true;
        }
    else {                                // Si le bouton n'est pas pese ...
        buttonIsPressed = false;
    }
}

/*****************************************************************************************
 * Fonction main
 ****************************************************************************************/

int main() {
    
    /*Declaration et initialisation des variables*/
    
    enum state {INIT, EA} s = INIT;                           // INIT: Etat Initial, EA: Etat Allumer
    uint8_t buttonPushCounter = 0;
    bool buttonIsPressed = false;
    bool buttonWasPressed = false;
    
    
    while(true) {
        
        _delay_ms(DEBOUNCETIME);                              // antirebond
        
        buttonCondition(buttonIsPressed, buttonWasPressed)    // Modification approprie des variables buttonIsPressed et buttonWasPressed
        
        switch(s){

            case INIT :                                       // INIT: DEL eteinte, augmentation du compteur, et/ou changement a EA
                PORTC = off
                
                if (buttonIsPressed && !buttonWasPressed) {
                    buttonPushCounter++;
                }
                if (buttonPushCounter == 5) {
                    buttonPushCounter = 0;
                    s = EA;
                }
            break;
            
            case EA   :                                        // Maintient DEL a la couleur rouge pour 1000 ms (1 seconde) puit changement a INIT
                PORTC = red;
                _delay_ms(ONTIME);
                s = INIT;
            break;
        }
    }
}
