/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: 
 * 
 * Pinout :
 *   Sensor inputs ( L R )       RightMotor ( E   D )
 *                   | |                      |   |
 *PORTA  1 2 3 4 5 6 7 8       PORTB  1 2 3 4 5 6 7 8         VCC---( power )
 *                                          |   |                   (  for  )
 *                              LeftMotor ( E   D )           GND---(Sensors)
 * 
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
#include <Motor.h>
#include <Sensor.h>
#include <Button.h>
#include <Obstacle.h>
#include <Led.h>
#include <Piezo.h>
#include <Timer.h>
#include <util/delay.h>

/******************************************************************************\
* Constants for loading proper boot states
\******************************************************************************/
const uint16_t EEPROMADDRESS = 0X0000;
const uint8_t DIAGNOSTIC = 1;
const uint8_t PATH = 0;

/******************************************************************************\
* Constants for sensors
\******************************************************************************/


/******************************************************************************\
* Constants for speed regulation
\******************************************************************************/


/******************************************************************************\
* supporting functions
\******************************************************************************/
uint8_t loadBootState() {
    
    uint8_t lastState, currentState;
    mem.lecture(EEPROMADDRESS, &lastState, 1);
    
    if(lastState == DIAGNOSTIC){
        currentState = PARCOURS;
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
    
    USBCommunicator usb;
    Memoire24CXXX mem;
    uint8_t bootState = loadBootState();
    
    if(bootState == 1){
        USBCommunicator usb;
        usb.communicate;
    } else {
        
        //code pour parcours
        
    }
}
