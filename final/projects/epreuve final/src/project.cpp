/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: 
 * 
 * Pinout :                                                     
 *                                                                     
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  0 1 2 3 4 5 6 7    PORTD  1 3 5 7        
 *        0 2 4 6           0 2 4 6                                     0 2 4 6       
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
const uint8_t DISTANCE_OPTIMALE = 15;
const uint8_t DISTANCE_ARRET_ROTATION = 17;
const uint8_t DISTANCE_MAXIMALE = 60;
const uint8_t NB_BOUCLE_DECREMENTION = 30;

/******************************************************************************\
* Constants for speed regulation
\******************************************************************************/
const uint8_t LO_SPEED = 90;
const uint8_t HI_SPEED = 150;

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
