/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        j_tp5_p1.cpp
 * Description: Make the LED light up in various colors as the button is
 *              pressed and released. Uses interruptions
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
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "j_tp5_p1.h"

/******************************************************************************\
 * Constants
\******************************************************************************/



/******************************************************************************\
 * Global variables
\******************************************************************************/

// List of all possible states for the state machine
enum state { INIT, SAMBER, SGREEN1, SRED, SOFF, SGREEN2 };

// Since interruptions will alter the state of the state machine, 
// the state machine must be declared globally
volatile state stateMachine;

/******************************************************************************\
 * Functions
\******************************************************************************/

/**
 * \brief Sets the specified bits of a byte to specific values
 * 
 * This function takes a byte and edits the bits specified in the bitMask byte
 * to the values specified in the values bytes. All bits should be properly
 * aligned. The bits that are set to 0 in the bitMask byte will be left
 * unchanged, and as such, their values in the values byte do not matter.
 * 
 * Usage :
 * 
 * setBits(
 *     reg, 
 *     (v1 << pos1)|(v2 << pos2)|(v3 << pos3),
 *     (1 << pos1)|(1 << pos2)|(1 << pos3)
 * )
 * 
 * "reg" : 
 * This byte will be modified.
 * 
 * "(v1 << pos1)|(v2 << pos2)|(v3 << pos3)" :
 * This statement will build a set of values in the right positions.
 * As an example,
 * (0 << 2)|(1 << 4)|(1 << 1)
 * evaluates to
 * 0b00000000 | 0b00010000 | 0b00000010
 * which evaluates to
 * 0b00010010
 * 
 * "(1 << pos1)|(1 << pos2)|(1 << pos3)" :
 * This will build the bit mask.
 * As an example,
 * (1 << 2)|(1 << 4)|(1 << 1)
 * evaluates to
 * 0b00000100 | 0b00010000 | 0b00000010
 * which evaluates to
 * 0b00010110
 * 
 * Following this example, "reg" will be edited to
 * 0bxxx1x01x
 * where "x" marks an unchanged value.
 * 
 * \param reg target byte
 * \param values values for the specified bits
 * \param bitMask bit mask, where a 1 indicates bits that should be set, and 0
 *                indicates the bits that should be left unchanged
 */
void setBits(uint8_t& reg, const uint8_t& values, const uint8_t& bitMask) {
    reg &= ~bitMask;
    reg |= values;
}

/**
 * \brief initialize the special registers
 * 
 * 
 */
void initialize() {
    
    // disable interruptions
    cli()
    
    // C PORT output
    DDRC = 0xff;
    
    // D PORT input
    DDRD = 0x00;
    
    {
        // EICRA is the External Interrupt Control Register A
        // bit      | 7      6      5      4      3      2      1      0
        // mnemonic | unused unused ISC21  ISC20  ISC11  ISC10  ISC01  ISC00
        // 
        // bits 7:6 are unused
        // bits 5:4 set the behavior of the INT2 interrupt vector
        // bits 3:2 set the behavior of the INT1 interrupt vector
        // bits 1:0 set the behavior of the INT0 interrupt vector
        
        // values    | behavior
        // LOW := 00 | The low level generates an interrupt request.
        // ANY := 01 | Any logical change generates an interrupt request.
        // FAL := 10 | The falling edge generates an interrupt request.
        // RIS := 11 | The rising edge generates an interrupt request.
        const uint8_t LOW = 0b000000'00;
        const uint8_t ANY = 0b000000'01;
        const uint8_t FAL = 0b000000'10;
        const uint8_t RIS = 0b000000'11;
    
        ECRIA = (4 << LOW) // INT2
               |(2 << LOW) // INT1
               |(0 << ANY);// INT0
        
    }
    // enable interruptions
    sei()
}

/**
 * \brief This function is executed whenever PORTD2 is powered
 * 
 * 
 * 
 * \param
 */
ISR (INT0_vect) {

// Wait for the physical switch to stop bouncing
_delay_loop_ms (DEBOUNCE_TIME);

// se souvenir ici si le bouton est pressé ou relâché

'modifier ici'

// changements d'états tels que ceux de la

// semaine précédente

'modifier ici'

// Voir la note plus bas pour comprendre cette instruction et son rôle

EIFR |= (1 << INTF0) ;

}

/******************************************************************************\
 * Main
\******************************************************************************/

/**
 * \brief main function
 * 
 * 
 * 
 * \return exit code
 */
int main () {
    
    // List of all possible states for the state machine
    enum state { INIT, SAMBER, SGREEN1, SRED, SOFF, SGREEN2 };
    
    State machine = INIT;

    // Infinite loop
    while (1){
        
        // Behavior for all states
        switch(machine) {
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case INIT : 
        
                PORTC = RED;
                
                // When the button is pressed
                if (PIND & 0x04) {
                    
                    // Change state
                    machine = SAMBER;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SAMBER : 
                
                //Flips the signal sent to the LED
                PORTC ^= 0x03;
                
                // When the button is released
                if (!(PIND & 0x04)) {
                    
                    // Change state
                    machine = SGREEN1;
                    
                    // The LED must be changed before the debounce delay,
                    // otherwise it'll flash a random color for DEBOUNCE_TIME ms
                    PORTC = GREEN;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN1 : 
            
                PORTC = GREEN;
            
                // When the button is pressed
                if (PIND & 0x04) {
                
                    // Change state
                    machine = SRED;
                
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SRED: 
            
                PORTC = RED;
            
                // When the button is released
                if (!(PIND & 0x04)) {
                
                    // Change state
                    machine = SOFF;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SOFF : 
                
                PORTC = OFF;
                
                // When the button is pressed
                if (PIND & 0x04) {
                  
                    // Change state
                    machine = SGREEN2;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            case SGREEN2 : 
                
                PORTC = GREEN;
        
                // When the button is released
                if (!(PIND & 0x04)) {
                    
                    // Change state
                    machine = INIT;
                    
                    // Wait for debounce
                    _delay_ms(DEBOUNCE_TIME);
                }
                
            break;
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        }
    }
  return EXIT_SUCCESS;
}

