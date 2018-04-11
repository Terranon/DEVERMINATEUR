/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.cpp
 * Description:
 * Version: 1.0
\******************************************************************************/

#include "Sensor.h"

volatile uint8_t distances[256] = {
61,	61,	61,	61,	61,	61,	61,	61,	
61,	61,	61,	61,	61,	61,	61,	61,	
61,	61,	61,	61,	61,	61,	61,	61,	
61,	61,	61,	61,	61,	61,	61,	60,	
58,	57,	55,	53,	52,	50,	49,	47,	
46,	45,	44,	43,	42,	41,	40,	39,	
38,	37,	36,	36,	35,	34,	33,	33,	
32,	31,	31,	30,	30,	29,	29,	28,	
28,	27,	27,	26,	26,	25,	25,	25,	
24,	24,	24,	23,	23,	23,	22,	22,	
22,	21,	21,	21,	20,	20,	20,	20,	
19,	19,	19,	19,	18,	18,	18,	18,	
17,	17,	17,	17,	17,	16,	16,	16,	
16,	16,	16,	15,	15,	15,	15,	15,	
15,	14,	14,	14,	14,	14,	14,	14,	
13,	13,	13,	13,	13,	13,	13,	12,	
12,	12,	12,	12,	12,	12,	12,	12,	
11,	11,	11,	11,	11,	11,	11,	11,	
11,	11,	10,	10,	10,	10,	10,	10,	
10,	10,	10,	10,	10,	10,	9,	9,	
9,	9,	9,	9,	9,	9,	9,	9,	
9,	9,	9,	8,	8,	8,	8,	8,	
8,	8,	8,	8,	8,	8,	8,	8,	
8,	8,	8,	8,	7,	7,	7,	7,	
7,	7,	7,	7,	7,	7,	7,	7,	
7,	7,	7,	7,	7,	7,	7,	6,	
6,	6,	6,	6,	6,	6,	6,	6,	
6,	6,	6,	6,	6,	6,	6,	6,	
6,	6,	6,	6,	6,	6,	6,	6,	
5,	5,	5,	5,	5,	5,	5,	5,	
5,	5,	5,	5,	5,	5,	5,	5,	
5,	5,	5,	5,	5,	5,	5,	5};

Sensor::Sensor(uint8_t pinG, uint8_t pinD)
	: convertisseur_(),
	  pinG_(pinG),
	  pinD_(pinD)
{
	DDRA = 0x00;
}
 
uint8_t Sensor::getDistanceG()
{
	return getDistance(pinG_);
}

uint8_t Sensor::getDistanceD()
{
	return getDistance(pinD_);
}

uint8_t Sensor::getDistance(uint8_t pin) {
	uint16_t sommeLectures = 0;
	for (uint8_t i = 0; i < 32; i++) {
		 sommeLectures += convertisseur_.read(pin);
	}
	
	// Division par 32 (bitshift de 5) et bitshift de 2
	// pour que ca rentre dans 8bit
	uint8_t moyenne = sommeLectures >> 7;
	
	return distances[moyenne];
}
