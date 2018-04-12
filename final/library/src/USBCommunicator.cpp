/******************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        USBCommunicator.cpp
 * Description:	Class that communicates with computer through USB Cable via UART
 * 
 * Version: 1.0
\******************************************************************************/

#include "USBCommunicator.h"

/**
 * \brief constructor for the USBCommunicator; the DDRx register will be set to
 *        enable output and input on the appropriate pins.
 * \return a USBCommunicator
 */
USBCommunicator::USBCommunicator():
robotName_("GucciBot     "),
teamNumber_("93-97    "),
sectionNumber_('5'),
semester_("18-1"),
robotColor_(1),
button_(),
sensor_(),
motors_(),
led_() {
          
    DDRD &= ~(1 << DDD0);
    DDRD |= (1 << DDD1);

    UBRR0H = 0;
    UBRR0L = 0xCF;
        
    UCSR0A = 0x00;		// Multi-processor Communication Mode
    UCSR0B = 0x18;		//Receiver Enable (bit4), Transmitter Enable(bit3)
    UCSR0C = 0x06;		//Asynchronous USART, non Parity, stop bit(s) 1-bit
                        //character size -- 8 bit 
    
}

/**
 * \brief destructor for the USBCommunicator
 */
USBCommunicator::~USBCommunicator() {
}

/**
 * \brief receives the byte coming from the USB cable and stores it in the UDR0
 *        register
 * \return a uint8_t
 */
uint8_t USBCommunicator::receiveUSB() {
    
	// Only return the data in the buffer if it it full
    if (UCSR0A & (1 << RXC0)) {
        return UDR0;
	} else {
        return 0;
    }
}

/**
 * \brief waits for the Transmit Complete flag to be true then writes 
 *        appropriate bytes to the UDR0 register and transmits it
 * \param valueTransmitted is the data value that the robot must send to the 
 *        computer
 */
void USBCommunicator::transmitUSB(uint8_t valueTransmitted) {
    
	// Clear the TXC0 flag (by writing 1 to its bit location)
	UCSR0A |= (1 << TXC0);
	
	// Add the data to the data buffer register
    UDR0 = valueTransmitted;
	
	// Wait for the data to be sent
    while(!(UCSR0A & (1 << TXC0))) {
    }
    
}

/**
 * \brief communicates with PC via USB
 */
void USBCommunicator::communicate() {
    
    uint8_t instruction;
	uint8_t unsignedValue;
    int8_t signedValue;
    
    while(1) {
        
        instruction = receiveUSB();
        
        if (instruction != 0) {
        
            switch (instruction) {
                case 0xFB:          // info request
                    
                    transmitUSB(0xF0); // robot name send instruction
                    for(uint8_t i = 0; i < NAMESIZE; i++) {
                        transmitUSB(robotName_[i]);
                    }
                    
                    transmitUSB(0xF1); // team number send instruction
                    for(uint8_t i = 0; i < NUMBERSIZE; i++) {
                        transmitUSB(teamNumber_[i]);
                    }
                    
                    transmitUSB(0xF2); // section number send instruction
                    transmitUSB(sectionNumber_);
                    
                    transmitUSB(0xF3); // current semester
                    for(uint8_t i = 0; i < SEMESTERSIZE; i++) {
                        
                        transmitUSB(semester_[i]);
                    }
                    
                    transmitUSB(0xF4); // robot color send instruction
                    transmitUSB(robotColor_);
                    
                    unsignedValue = button_.sendState();
                    transmitUSB(0xF5); // button state send instruction
                    transmitUSB(unsignedValue);
                    
                    unsignedValue = sensor_.getDistanceL();
                    transmitUSB(0xF6); // left sensor distance send instruction
                    transmitUSB(unsignedValue);
                    
                    unsignedValue = sensor_.getDistanceR();
                    transmitUSB(0xF7); // right sensor distance send instruction
                    transmitUSB(unsignedValue);
                    break;
                case 0xF8:          // change speed of left motor
                    
                    signedValue = receiveUSB();
                    
                    switch (signedValue) {
                        case 0:
                            motors_.setSpeedLM(0);
                            break;
                        case -100:
                            motors_.setDirectionLM(1);
                            motors_.setSpeedLM(255);
                            break;
                        case -75:
                            motors_.setDirectionLM(1);
                            motors_.setSpeedLM(191);
                            break;
                        case -50:
                            motors_.setDirectionLM(1);
                            motors_.setSpeedLM(127);
                            break;
                        case -25:
                            motors_.setDirectionLM(1);
                            motors_.setSpeedLM(80);
                            break;
                        case 25:
                            motors_.setDirectionLM(0);
                            motors_.setSpeedLM(80);
                            break;
                        case 50:
                            motors_.setDirectionLM(0);
                            motors_.setSpeedLM(127);
                            break;
                        case 75:
                            motors_.setDirectionLM(0);
                            motors_.setSpeedLM(191);
                            break;
                        case 100:
                            motors_.setDirectionLM(0);
                            motors_.setSpeedLM(255);
                            break;
                    }
                    break;
                case 0xF9:          // change speed of right motor
                    
                    signedValue = receiveUSB();
                    
                    switch (signedValue) {
                        case 0:
                            motors_.setSpeedRM(0);
                            break;
                        case -100:
                            motors_.setDirectionRM(1);
                            motors_.setSpeedRM(255);
                            break;
                        case -75:
                            motors_.setDirectionRM(1);
                            motors_.setSpeedRM(191);
                            break;
                        case -50:
                            motors_.setDirectionRM(1);
                            motors_.setSpeedRM(127);
                            break;
                        case -25:
                            motors_.setDirectionRM(1);
                            motors_.setSpeedRM(80);
                            break;
                        case 25:
                            motors_.setDirectionRM(0);
                            motors_.setSpeedRM(80);
                            break;
                        case 50:
                            motors_.setDirectionRM(0);
                            motors_.setSpeedRM(127);
                            break;
                        case 75:
                            motors_.setDirectionRM(0);
                            motors_.setSpeedRM(191);
                            break;
                        case 100:
                            motors_.setDirectionRM(0);
                            motors_.setSpeedRM(255);
                            break;
                    }
                    break;
                case 0xFA:          // change color of led
                    
                    unsignedValue = receiveUSB();
                    
                    led_.setColor(unsignedValue);
                    break;
            }
        }
    }
}
