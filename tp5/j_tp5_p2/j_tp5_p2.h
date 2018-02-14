/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

/******************************************************************************\
 * Type Definitions
\******************************************************************************/


/******************************************************************************\
 * Global variables
\******************************************************************************/

// Global variables to catch interruptions
volatile uint8_t timerExpired;
volatile uint8_t buttonPressed;

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
void initIO();
void initEInt();
void initTimer(uint16_t duration);
void initialize();
int main();
