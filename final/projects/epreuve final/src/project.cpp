/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Ce programme alterne entre les deux modes d'operation 
 *              (Diagnostic ou Path) en utilisant la memoire EEPROM.
 * Pinout :
 * 
 * VCC(PORTB & C)---( power for )
 * GND--------------(  sensors  )
 * 
 *   Sensor inputs ( L R )       RightMotor ( E   D )
 *                   | |                      |   |
 *PORTA  1 2 3 4 5 6 7 8       PORTB  1 2 3 4 5 6 7 8
 *                                          |   |    
 *                              LeftMotor ( E   D )           
 * 
 *      LED ( - + )                     Piezo ( - + )
 *            | |                               | |
 * PORTC  1 2 3 4 5 6 7 8    PORTD  1 2 3 4 5 6 7 8
 *                                          | |
 *                         Jumper for Timer \_/
 * 
 * Version: 1.0
\******************************************************************************/

#include <memoire_24.h>
#include <USBCommunicator.h>
#include <Parcours.h>

/******************************************************************************\
* Constants for loading proper boot states
\******************************************************************************/
const uint16_t EEPROMADDRESS = 0X0000;
const uint8_t DIAGNOSTIC = 1;
const uint8_t PATH = 0;


/**
 * \brief changes the color of the LED
 * \return a uint8_t containing the current Boot State: Diagnostic or Path.
 */
uint8_t loadBootState() {
    
    uint8_t lastState, currentState;
    Memoire24CXXX mem;
    mem.lecture(EEPROMADDRESS, &lastState, 1);
    
    if(lastState == DIAGNOSTIC){
        currentState = PATH;
        mem.ecriture(EEPROMADDRESS, &currentState, 1);
    } else {
        currentState = DIAGNOSTIC;
        mem.ecriture(EEPROMADDRESS, &currentState, 1);
    }
    return currentState;
}


/******************************************************************************\
 * Main
\******************************************************************************/
int main(){
    
    uint8_t bootState = loadBootState();
    
    if(bootState == DIAGNOSTIC){
        USBCommunicator usb;
        usb.communicate();
    } else {
        Parcours parcours;
        parcours.start();
    }
}
