/******************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        USBCommunicator.ch
 * Description:	Class that communicates with computer through USB Cable via UART
 * 
 * Version: 1.0
\******************************************************************************/

#ifndef INTERPRETER_H

#include <memoire_24.h>
#include <util/delay.h>


class USBCommunicator {

public:
    
    /**
    * \brief constructor for the USBCommunicator; the DDRx register will be set to enable
    *        output and input on the appropriate pins
    * \return a USBCommunicator
    */
    USBCommunicator();
    
    /**
    * \brief destructor for the USBCommunicator
    */
    ~USBCommunicator();
    
    /**
    * \brief receives the byte coming from the USB cable and stores it in the UDR0 register
    * \return a uint8_t
    */
    uint8_t USBCommunicator::receiveUSB();
    
    /**
    * \brief writes appropriate bytes to the UDR0 register and transmits it
    * \param valueTransmitted is the data value that the robot must send to the 
    *        computer
    */
    void USBCommunicator::transmitUSB(uint8_t valueTransmitted);
    
    /**
    * \brief communicates with PC via USB
    */
    void USBCommunicator::communicate();
    
private:
    
    static const uint8_t NAMESIZE = 8;     // # of characters in the robot's name
    static const uint8_t NUMBERSIZE = 4;   // # of characters in the team's number
    static const uint8_t SEMESTERSIZE = 4; // # of characters in the semester code
    
    static const char[NAMESIZE] ROBOTNAME = {71,117,99,99,105,66,111,116}; // GucciBot
    static const char[NUMBERSIZE] TEAMNUMBER = {57,51,57,55}; // 9397
    static const uint8_t SECTIONNUMBER = 5; // section 5
    static const char[SEMESTERSIZE] SEMESTER = {49,56,45,49}; // 18-1
    static const uint8_t ROBOTCOLOUR = 1; // black
    
    
    uint8_t instructionReceived_;
    char[NAMESIZE] robotName_;
    char[NUMBERSIZE] teamNumber_;
    uint8_t sectionNumber_;
    char[SEMESTERSIZE] semester_;
    uint8_t robotcolor_;
    
    Button button_;
    Sensor sensor_;
    Motor motors_;
    Led led_;
    
};
#endif

