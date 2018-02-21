/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "memoire_24.h"

/******************************************************************************\
 * Type Definitions
\******************************************************************************/


/******************************************************************************\
 * Global variables
\******************************************************************************/

// Global variables to catch interruptions
enum state { INIT, FLGREEN, FLRED, ONGREEN };
    
volatile state machine;
volatile uint8_t buttonPressed;
volatile uint8_t timerNotComplete;
volatile uint8_t counter;


/******************************************************************************\
 * Constants
\******************************************************************************/

// in ms
const uint8_t DEBOUNCE_TIME = 30;
const uint8_t FLICKER_TIME = 10;
const uint8_t HALF_SECOND = 500;
const uint8_t READ_DELAY_AFTER_WRITE = 5;

// Constants for the LED in port 0..1
const uint8_t OFF   = 0x00;
const uint8_t RED   = 0x01;
const uint8_t GREEN = 0x02;
    
/******************************************************************************\
 * Initialization functions
\******************************************************************************/

void initIO();
void initEInt();
void initTimer();
void initialize();

/******************************************************************************\
 * Functions
\******************************************************************************/

void enableEInt0();
void disableEInt0();
void startCounter(uint32_t duration);

/******************************************************************************\
 * Main
\******************************************************************************/

int main();
