/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Motor.cpp
 * Description: General use of motors 
 * 							Using JM1D : PD4
 * 										JM1E : PD6
 * 										JM2D : PD5
 * 										JM2E : PD7
 * Version: 1.0
\******************************************************************************/
#include "Motor.h"

//Constuctor with parameters
Motor::Motor(uint8_t direction, uint8_t speed)
{
	directionLM_ = direction;
	directionRM_ = direction;
	speedLM_ = speed;
	speedRM_ = speed;
}

//Default Constructor
Motor::Motor()
{
	directionLM_ = FRWD;
	directionRM_ = FRWD;
	speedLM_ = 0x00;
	speedRM_ = 0x00;
}

//Destructor
Motor::~Motor()
{
}

//Modification functions
void Motor::setDirectionLM(uint8_t direction) 
{
	directionLM_ = direction;
}
void Motor::setDirectionRM(uint8_t direction) 
{
	directionRM_ = direction;
}
void Motor::setSpeedLM(uint8_t speed)
{
	speedLM_ = speed;
}
void Motor::setSpeedRM(uint8_t speed){
	speedRM_ = speed;
}

//Get functions
uint8_t Motor::getDirectionLM() 
{
	return directionLM_;
}
uint8_t Motor::getDirectionRM() 
{
	return directionRM_;
}
uint8_t Motor::getSpeedLM()
{
	return speedLM_;
}
uint8_t Motor::getSpeedRM()
{
	return speedRM_;
}



void Motor::turnLeft(){
	stopMotors();
	uint8_t oldSpeedLM = getSpeedLM();
	uint8_t oldSpeedRM = getSpeedRM();
	
	setDirectionRM(FRWD);
	setDirectionLM(BACK);		//LM going backward
	setSpeedLM(255);				//max speed
	setSpeedRM(255);				//max speed
	
	driveMotors();
	_delay_ms(1000);
	stopMotors();
	
	setSpeedLM(oldSpeedLM);
	setSpeedRM(oldSpeedRM);
}

void Motor::turnLeft(){
	stopMotors();
	uint8_t oldSpeedLM = getSpeedLM();
	uint8_t oldSpeedRM = getSpeedRM();
	
	setDirectionRM(BACK);
	setDirectionLM(FRWD);		//LM going backward
	setSpeedLM(255);				//max speed
	setSpeedRM(255);				//max speed
	
	driveMotors();
	_delay_ms(1000);
	stopMotors();
	
	setSpeedLM(oldSpeedLM);
	setSpeedRM(oldSpeedRM);
}


void Motor::stopMotors(){
	setSpeedLM(0);
	setSpeedRM(0);
	driveMotors();
}

void Motor::goFRWD(uint8_t speed){
	setSpeedLM(speed);
	setSpeedRM(speed);
	setDirectionLM(FRWD);
	setDirectionRM(FRWD);
	
	driveMotors();
}

void Motor::goBACK(uint8_t speed){
	setSpeedLM(speed);
	setSpeedRM(speed);
	setDirectionLM(BACK);
	setDirectionRM(BACK);
	
	driveMotors();
}


//Function driveMotors initializing the mechanism of the motors
void Motor::driveMotors() 
{
	// ~~~TCCR0A~~~
	//
	// bit      | 7      6      5      4      3      2      1      0
	// mnemonic |COM0A1 COM0A0 COM0B1 COM0B0  --     --    WGM01  WGM00

	// ~~~TCCR0B~~~
	//
	// bit      | 7      6      5      4      3      2      1      0
	// mnemonic | FOC0A FOC0B   --     --		WGM02  				CS0[2:0]


	//COMPARE OUTPUT (TCCR0A)
	// bits 7:6 COM0A[1:0] Compare Output Mode for Channel A
	// bits 5:4 COM0B[1:0] Compare Output Mode for Channel B
	// 2 | Clear OC0x when up-count match. Set OC0x when downcount match. 
	TCCR0A |= (2 << COM0A0); 
	TCCR0A |= (2 << COM0B0);


	//CLOCK SELECT (TCCR0B)
	// CS0[2:0] Clock Select
	// 2 | clkI/O /8 (From prescaler)
	TCCR2B |= (2 << CS00); 


	//WAVEFORM GENERATOR (TCCR0A & TCCR0B)
	// ~~~WGM0[2:0]~~
	// Mode | Timer/Counter mode           | TOP    | Update of | TOV1 flag  
	// 1    | PWM, Phase Correct				   | 0xFF   | TOP       | BOTTOM
	const uint8_t WGM0_val = 1; 
	TCCR0A |= ((WGM0_val & 0x03) << WGM00);
	TCCR0B |= ((WGM0_val >> 2) << WGM02);
	

	//LW ADJUSTMENT
	DDRB |= speedLM_ << DDB3;			//OC0A
	DDRB |= directionLM_ << DDB5;	
	
	//RW ADJUSTMENT
	DDRB |= speedRM_ << DDB4;			//OC0B
	DDRB |= directionRM_ << DDB6;
}





