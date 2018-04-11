/******************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        USBCommunicator.h
 * Description:	Class that communicates with computer through USB Cable via UART
 * 
 * Version: 1.0
\******************************************************************************/

#ifndef USBCommunicator_H
#define USBCommunicator_H

#include <util/delay.h>
#include "Button.h"
#include "Sensor.h"
#include "Motor.h"
#include "Led.h"


class USBCommunicator {

public:
    
    /**
    * \brief constructor for the USBCommunicator; the DDRx register will be set
    *        to enable output and input on the appropriate pins
    * \return a USBCommunicator
    */
    USBCommunicator();
    
    /**
    * \brief destructor for the USBCommunicator
    */
    ~USBCommunicator();
    
    /**
    * \brief receives the byte coming from the USB cable and stores it in the
    *        UDR0 register
    * \return a uint8_t
    */
    uint8_t receiveUSB();
    
    /**
    * \brief waits for the Transmit Complete flag to be true then writes 
    *        appropriate bytes to the UDR0 register and transmits it
    * \param valueTransmitted is the data value that the robot must send to the 
    *        computer
    */
    void transmitUSB(uint8_t valueTransmitted);
    
    /**
    * \brief communicates with PC via USB
    */
    void communicate();
    
private:
    
    // # of characters in the robot's name
    static const uint8_t NAMESIZE = 13;
    // # of characters in the team's number
    static const uint8_t NUMBERSIZE = 9;
    // # of characters in the semester code
    static const uint8_t SEMESTERSIZE = 4;
    
    char robotName_[NAMESIZE+1];
    char teamNumber_[NUMBERSIZE+1];
    char sectionNumber_;
    char semester_[SEMESTERSIZE+1];
    uint8_t robotColor_;
    
    Button button_;
    Sensor sensor_;
    Motor motors_;
    Led led_;
    
};
#endif

