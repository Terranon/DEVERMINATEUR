// List of all possible states for the state machine
enum etat { INIT, SAMBER, SGREEN1, SRED, SOFF, SGREEN2 };
    
volatile etat machine;

// in ms
const uint8_t DEBOUNCE_TIME = 40;
    
// in us
const uint8_t LOOP_TIME = 100;
    
// Constants for the LED in port 0..1
const uint8_t OFF   = 0x00;
const uint8_t RED   = 0x01;
const uint8_t GREEN = 0x02;

void initialisation()


/*****************************************************************************\
 * Authors:     Maximilien Bianchi, Jean-Raphael Matte
 * Name:        m_tp5_p1.cpp
 * Description: Make the LED light up in various colors as the button is
 *              pressed and released, using interrupts.
 * 
 *              Pinout :    LED ( + - )
 *                                | |
 *                       PORT C ( 0 1 2 3 4 5 6 7 )
 * 
 * Version: 1.0
\******************************************************************************/

/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_VECT) {

    _delay_loop_ms (30);

    // se souvenir ici si le bouton est pressé ou relâché

    machine++

    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0);
}

void initialisation() {

// cli bloque toutes les interruptions.

cli ();

// C PORT output
DDRC = 0xff;
    
// D PORT input
DDRD = 0x00;


// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0) ;


// N'importe quel changement logique sur INT0 genere une requete d'interruption

EICRA |= (0 << ISC01) | (1 << ISC00);


// sei permet de recevoir à nouveau des interruptions.

sei ();

}

/******************************************************************************\
 * Main
\******************************************************************************/

int main() {
    
    initialisation();
    
    machine = INIT;

    // Infinite loop
    while (1){
        
        // Behavior for all states
        switch(machine) {
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case INIT : 
                
                PORTC = RED;
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SAMBER : 
                
                //Flips the signal sent to the LED
                PORTC ^= 0x03;
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN1 : 
                
                PORTC = GREEN;
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SRED: 
                
                PORTC = RED;
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SOFF : 
                
                PORTC = OFF;
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN2 : 
                
                PORTC = GREEN;
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        }
    }
  return 0;
}

