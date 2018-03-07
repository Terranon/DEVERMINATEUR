#include "Motor.h"

const uint8_t FRWD = 0x00; //lorsque direction = 0 lumiere verte
const uint8_t BACK = 0xC0; //lorsque direction = 1 lumiere rouge
const uint8_t PORT_SORTIE = 0xff;

//constructeur
motor::motor(uint8_t direction = FRWD , uint8_t speed = 0) : 
	direction_(direction),
	speed_(speed),
{
	DDRD = PORT_SORTIE;
}


//destructeur
motor::~motor()
{
}


//methodes de modifications
void motor::setDirection(uint8_t direction) 
{
	direction_ = direction;
}

void motor::setSpeed(uint8_t speed)
{
	speed_ = speed;
}


//methode driveMotors
// ~~~TCCR1A~~~
//
// bit      | 7      6      5      4      3      2      1      0
// mnemonic | COM1A1 COM1A0 COM1B1 COM1B0 --     --     WGM11  WGM10
// 
// bits 7:6 COM1A[1:0] Compare Output Mode for Channel A
// bits 5:4 COM1B[1:0] Compare Output Mode for Channel B
// 2 | Clear OC1x when up-count match. Set OC1x when downcount match.


// ~~~TCCR1B~~~
//
// bit      | 7      6      5      4      3      2      1      0
// mnemonic | ICNC1  ICES1  --     WGM13  WGM12  CS12   CS11   CS10

// CS1[2:0] Clock Select
// 2 | clkI/O /8 (From prescaler)

void motor::driveMotors() const
{
	//compare output 
	TCCR2A |= (2 << COM2A0); 
	TCCR2A |= (2 << COM2B0);

	//clock select
	TCCR2B |= (2 << CS20); 


	//waveform generation

	// ~~~WGM1[3:0]~~
	//
	// Mode | Timer/Counter mode           | TOP    | Update of | TOV1 flag  
	// 1    | PWM, Phase Correct, 8-bit    | 0x00FF | TOP       | BOTTOM

	const uint8_t WGM2_val = 1; 

	TCCR2A |= ((WGM2_val & 0x03) << WGM20);
	TCCR2B |= ((WGM2_val >> 2) << WGM22);
	

	PORTD = direction_;
	OCR2A = speed_;	//OC2A PD7
	OCR2B = speed_; //OC2B PD6

}