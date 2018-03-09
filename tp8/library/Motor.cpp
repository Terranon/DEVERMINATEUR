/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Motor.cpp
 * Description: General use of motors
 * Version: 1.0
\******************************************************************************/
#include "Motor.h"

//Constuctor with parameters
Motor::Motor(uint8_t direction, uint8_t speed)
{
	direction_ = direction;
	speed_ = speed;
}

//Default Constructor
Motor::Motor()
{
	direction_ = FRWD;
	speed_ = 0x00;
}

//Destructor
Motor::~Motor()
{
}

//Modification functions
void Motor::setDirection(uint8_t direction) 
{
	direction_ = direction;
}

void Motor::setSpeed(uint8_t speed)
{
	speed_ = speed;
}

//Function driveMotors initializing the mechanism of the motors
void Motor::driveMotors() 
{
	// ~~~TCCR2A~~~
	//
	// bit      | 7      6      5      4      3      2      1      0
	// mnemonic |COM2A1 COM2A0 COM2B1 COM2B0  --     --    WGM21  WGM20

	// ~~~TCCR2B~~~
	//
	// bit      | 7      6      5      4      3      2      1      0
	// mnemonic | FOC2A FOC2B   --     --		WGM22  				CS2[2:0]


	//COMPARE OUTPUT (TCCR2A)
	// bits 7:6 COM2A[1:0] Compare Output Mode for Channel A
	// bits 5:4 COM2B[1:0] Compare Output Mode for Channel B
	// 2 | Clear OC2x when up-count match. Set OC1x when downcount match. 
	TCCR2A |= (2 << COM2A0); 
	TCCR2A |= (2 << COM2B0);


	//CLOCK SELECT (TCCR2B)
	// CS2[2:0] Clock Select
	// 2 | clkI/O /8 (From prescaler)
	TCCR2B |= (2 << CS20); 


	//WAVEFORM GENERATOR (TCCR2A & TCCR2B)
	// ~~~WGM2[2:0]~~
	// Mode | Timer/Counter mode           | TOP    | Update of | TOV1 flag  
	// 1    | PWM, Phase Correct				   | 0xFF   | TOP       | BOTTOM
	const uint8_t WGM2_val = 1; 
	TCCR2A |= ((WGM2_val & 0x03) << WGM20);
	TCCR2B |= ((WGM2_val >> 2) << WGM22);
	

	DDRD |= PORT_SORTIE_MOTEURS;

	//DIRECTION OF MOTORS 
	PORTD = direction_;

	//SPEED OF MOTORS
	OCR2A = speed_;	//OC2A 
	OCR2B = speed_; //OC2B 
}



