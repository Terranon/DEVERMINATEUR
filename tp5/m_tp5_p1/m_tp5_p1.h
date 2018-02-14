#include <stdint.h>

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
