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
 * \brief constructor for the USBCommunicator; the DDRx register will be set to enable
 *        output and input on the appropriate pins
 * \return a USBCommunicator
 */
USBCommunicator::USBCommunicator()
    : instructionReceived_(),
      robotName_(ROBOTNAME),
      teamNumber_(TEAMNUMBER),
      sectionNumber_(SECTIONNUMBER),
      semester_(SEMESTER),
      robotColor_(ROBOTCOLOUR),
      buttonState_(0),
      leftSensorDistance_(),
      rightSensorDistance_(),
      leftMotorSpeed_(0),
      rightMotorSpeed_(0),
      ledColor_(0),
      infoRequestSent_() {
          
    DDRD &= ~(1 << DDD0);
    DDRD |= (1 << DDD1);
        
    UCSR0A = 0x00;		//Multi-processor Communication Mode
    UCSR0B = 0x18;		//Receiver Enable (bit4), Transmitter Enable(bit3)
    UCSR0C = 0x06;		//Asynchronous USART, none Parity, stop bit(s) 1-bit
                                            //character size -- 8 bit 

    UBRR0H = 0;
    UBRR0L = 0xCF;
    
    Sensor sensor();
    Led led();
    Button button();
    }

/**
 * \brief destructor for the USBCommunicator
 */
USBCommunicator::~USBCommunicator() {
}

/**
 * \brief receives the byte coming from the USB cable and stores it in the UDR0 register
 * \return a uint8_t
 */
uint8_t USBCommunicator::receiveUSB() {
    
    if(UCSR0A & (1 << RXC0) {
        
        instructionReceived_ = 1;
        return UDR0;
        
	} else {
        
        instructionReceived_ = 0;
        return 0;
}

/**
 * \brief writes appropriate bytes to the UDR0 register and transmits it
 * \param valueTransmitted is the data value that the robot must send to the 
 *        computer
 */
void USBCommunicator::transmitUSB(uint8_t valueTransmitted) {
    
    if(UCSR0A & (1 << TXC0)) {
        
        UDR0 = valueToBeSent;
    }
}

/**
 * \brief communicates with PC via USB
 */
void USBCommunicator::communicate() {
    
    uint8_t instruction;
    
    while(1) {
        
        instruction = receiveUSB();
        _delay_ms(5);
        
        if(instructionReceived_ == 1) {
        
            switch (instruction) {
                case 0xFB:         // info request
                    infoRequestSent_ = 1;
                    
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
                    
                    transmitUSB(0xF4); // robot colour send instruction
                    transmitUSB(robotColor_);
                    
                    setButtonState();
                    transmitUSB(0xF5); // button state send instruction
                    transmitUSB(buttonState_);
                    
                    setLeftSensorDistance();
                    transmitUSB(0xF6); // left sensor distance send instruction
                    transmitUSB(leftSensorDistance_);
                    
                    setRightSensorDistance();
                    transmitUSB(0xF7); // right sensor distance send instruction
                    transmitUSB(rightSensorDistance_);
                    break;
                case 0xF8:           // change speed of left motor
                    leftMotorSpeed_ = receiveUSB();
                    break;
                case 0xF9:
                    rightMotorSpeed_ = receiveUSB();
                    break;
                case 0xF9:
                    ledColor_ = receiveUSB();
                    break;
            }
}

/**
 * \brief sets button's state from Button Class
 */
void USBCommunicator::setButtonState() {
    
    buttonState_ = button.getButtonState();
}

/**
 * \brief sets left sensor's distance from Sensor Class
 */
void USBCommunicator::setLeftSensorDistance() {
    
    leftSensorDistance_ = sensor.getDistanceG();
}

/**
 * \brief sets right sensor's distance from Sensor Class
 */
void USBCommunicator::setRightSensorDistance() {
    
    rightSensorDistance_ = sensor.getDistanceD();
}


/**
 * \brief changes the colour of the led using Led Class
 */
void USBCommunicator::changeLedColor(uint8_t ledColor_) {
    
    led.setColor(ledColor_);
}

/******************************************************************************\
 * Main
\******************************************************************************/
