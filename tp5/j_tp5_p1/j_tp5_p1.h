/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

/******************************************************************************\
 * Global variables
\******************************************************************************/

// List of all possible states for the state machine
enum state { INIT, SAMBER, SGREEN1, SRED, SOFF, SGREEN2 };

// Since interruptions will alter the state of the state machine, 
// the state machine must be declared globally
volatile state stateMachine;

/******************************************************************************\
 * Constants
\******************************************************************************/

// in ms
const uint8_t DEBOUNCE_TIME = 30;

// Constants for the LED in port 0..1
const uint8_t OFF   = 0x00;
const uint8_t RED   = 0x01;
const uint8_t GREEN = 0x02;
    
/******************************************************************************\
 * Functions
\******************************************************************************/

void setBits(uint8_t& reg, const uint8_t& values, const uint8_t& bitMask);
void initialize();
int main();
