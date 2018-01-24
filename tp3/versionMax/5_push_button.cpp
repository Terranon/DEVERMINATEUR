/*
 * Nom: Flashy light program
 * Description: After 5 pushes of a button, LED turns on for 5 seconds then returns to standby state
 * Version: 2.1
 */


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main() {

    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0x00; // PORT D est en mode entree
    
    const short DEBOUNCETIME = 40;
    const int ONTIME = 1000;
    const uint8_t red = 0x01;
    const uint8_t off = 0x00;
    enum state {INIT, EA} s = INIT;             // INIT = Etat initial, EA = Etat allume
    
    
    uint8_t buttonPushCounter = 0;
    bool buttonIsPressed = false;
    bool buttonWasPressed = false;
    
    while(true) {
        
        _delay_ms(DEBOUNCETIME);
        
        buttonWasPressed = buttonIsPressed;
        
        if (PIND & 0x04) {
            buttonIsPressed = true;
        }
        else {
            buttonIsPressed = false;
        }
        
        switch(s){

            case INIT :
                PORTC = off;
                
                if (buttonIsPressed && !buttonWasPressed) {
                    buttonPushCounter++;
                }
                if (buttonPushCounter == 5) {
                    buttonPushCounter = 0;
                    s = EA;
                }
            break;
            
            case EA   :
                PORTC = red;
                _delay_ms(ONTIME);
                s = INIT;
            break;
        }
    }
}
