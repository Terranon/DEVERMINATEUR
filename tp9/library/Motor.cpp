/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Motor.cpp
 * Description: General use of motors 
 * 						Using 
 * 						JM1D : PORTB5 
 * 						JM1E : PORTB3
 * 						JM2D : PORTB6
 * 						JM2E : PORTB4
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
	speedLM_ = 0;
	speedRM_ = 0;
}

//Destructor
Motor::~Motor()
{
}

//Set functions
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


//Turning functions
void Motor::turnLeft(){
	//remember old speed of both motors then stop them
	uint8_t oldSpeedLM = getSpeedLM();
	uint8_t oldSpeedRM = getSpeedRM();
	stopMotors();
	_delay_ms(500);
		
	//set the speed and the direction of both motors
	setDirectionRM(FRWD);
	setDirectionLM(BACK);		//LM going backward
	setSpeedLM(255);		//max speed
	setSpeedRM(255);		//max speed
	
	//drive both motors to make the turn
	driveMotors();
	_delay_ms(1000);
	stopMotors();
	_delay_ms(500);

	//set their old speed
	setSpeedLM(oldSpeedLM);
	setSpeedRM(oldSpeedRM);
}

void Motor::turnRight(){
	uint8_t oldSpeedLM = getSpeedLM();
	uint8_t oldSpeedRM = getSpeedRM();
	stopMotors();
	_delay_ms(500);
	
	setDirectionRM(BACK);		//RM going backward
	setDirectionLM(FRWD);		
	setSpeedLM(255);		//max speed
	setSpeedRM(255);		//max speed
	
	driveMotors();
	_delay_ms(1000);
	stopMotors();
	_delay_ms(500);
	
	setSpeedLM(oldSpeedLM);
	setSpeedRM(oldSpeedRM);
}

//Stop motor function
void Motor::stopMotors(){
	setSpeedLM(0);
	setSpeedRM(0);
	driveMotors();
}


//Going forward function
void Motor::goFRWD(uint8_t speed){
	setSpeedLM(speed);
	setSpeedRM(speed);
	setDirectionLM(FRWD);
	setDirectionRM(FRWD);
	
	driveMotors();
}

//Going backward function
void Motor::goBACK(uint8_t speed){
	setSpeedLM(speed);
	setSpeedRM(speed);
	setDirectionLM(BACK);
	setDirectionRM(BACK);
	
	driveMotors();
}


//Function driveMotors initializing the mechanism of the motors using Timer 0
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
	TCCR0B |= (2 << CS00); 


	//WAVEFORM GENERATOR (TCCR0A & TCCR0B)
	// ~~~WGM0[2:0]~~
	// Mode | Timer/Counter mode           | TOP    | Update of | TOV1 flag  
	// 1    | PWM, Phase Correct				   | 0xFF   | TOP       | BOTTOM
	const uint8_t WGM0_val = 1; 
	TCCR0A |= ((WGM0_val & 0x03) << WGM00);
	TCCR0B |= ((WGM0_val >> 2) << WGM02);
	
	
	//INITIALIZE PORTB
	DDRB |= 1 << DDB3;			
	DDRB |= 1 << DDB4;	
	DDRB |= 1 << DDB5;			
	DDRB |= 1 << DDB6;
	
	
	//LW ADJUSTMENT
	OCR0A = speedLM_;			
	//LW DIRECTION 
	if (directionLM_ == BACK) {
		PORTB |= (1 << PORTB5 );
	} else {
		PORTB &= ~(1 << PORTB5);
	}
	
	//RW ADJUSTMENT
	OCR0B = speedRM_;
	//RW DIRECTION
	if (directionRM_ == BACK) {
		PORTB |= (1 << PORTB6 );
	} else {
		PORTB &= ~(1 << PORTB6);
	}
		
}





