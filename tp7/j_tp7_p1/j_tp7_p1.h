/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "Led.h"

/******************************************************************************\
 * Type Definitions
\******************************************************************************/



/******************************************************************************\
 * Global variables
\******************************************************************************/

// Global variables to catch interruptions
volatile uint8_t buttonPressed;
volatile uint8_t timerExpired;

/******************************************************************************\
 * Constants
\******************************************************************************/


    
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

void startTimer(uint32_t duration);

/******************************************************************************\
 * Main
\******************************************************************************/

int main();
