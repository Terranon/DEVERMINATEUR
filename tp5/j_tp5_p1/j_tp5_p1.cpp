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

#include "j_tp5_p1.h"

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
 * \param bitMask bit mask, where a 1 indicates a bit that should be set, and 0
 *                indicates a bit that should be left unchanged
 */
void setBits(uint8_t& reg, const uint8_t& values, const uint8_t& bitMask) {
    reg &= ~bitMask;
    reg |= values;
}

/**
 * \brief This function is executed whenever PORTD2 is powered
 * 
 * 
 * 
 * \param INT0_vect the function will run when the INT0 interrupt vector is
 *                  called
 */
ISR (INT0_vect) {

    // Wait for the physical switch to stop bouncing
    _delay_loop_ms(DEBOUNCE_TIME);

    // Change to thr next state
    stateMachine++;

    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
    
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

    {// EIMSK is the External Interrupt Mask Register
        
        // bit      | 7      6      5      4      3      2      1      0
        // mnemonic | unused unused unused unused unused INT2   INT1   INT0
        // 
        // bits 7:3 are unused
        // bit 2 sets the behavior of the INT2 interrupt vector
        // bit 1 sets the behavior of the INT1 interrupt vector
        // bit 0 sets the behavior of the INT0 interrupt vector
        
        // values | behavior
        // 0      | the corresponding bit will not be set
        // 1      | the corresponding bit will be set to 1
        
        EIMSK |= (0 << INT2);
        EIMSK |= (0 << INT1);
        EIMSK |= (1 << INT0);
    }
    
    {// EICRA is the External Interrupt Control Register A
        
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
    
        EICRA |= (LOW << ISC20);// INT2
        EICRA |= (LOW << ISC10);// INT1
        EICRA |= (ANY << ISC00);// INT0
    }
    
    // enable interruptions
    sei()
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
    
    initialize();
    stateMachine = INIT;

    // Infinite loop
    while (1){
        
        // Behavior for all states
        switch(stateMachine) {
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
    return EXIT_SUCCESS;
}

