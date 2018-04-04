/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.cpp
 * Description:
 * Version: 1.0
\******************************************************************************/

#include "Sensor.h"

volatile int distance[256] = {
	255,255,255,255,255,255,255,255,	
	255,255,255,255,255,255,255,255,	
	255,255,255,255,255,255,255,255,	
	255,255,255,255,255,255,255,255,	
	255,255,255,255,255,255,255,255,	
	255,255,255,255,255,253,245,239,	
	232,226,220,214,208,203,198,193,	
	188,183,179,175,170,166,162,159,	
	155,151,148,145,141,138,135,132,	
	129,126,124,121,118,116,113,111,	
	109,106,104,102,100,98,	96,	94,	
	92,	90,	88,	86,	85,	83,	81,	80,	
	78,	76,	75,	73,	72,	70,	69,	67,	
	66,	65,	63,	62,	61,	60,	58,	57,	
	56,	55,	54,	52,	51,	50,	49,	48,	
	47,	46,	45,	44,	43,	42,	41,	40,	
	39,	39,	38,	37,	36,	35,	34,	33,	
	33,	32,	31,	30,	30,	29,	28,	27,	
	27,	26,	25,	25,	24,	23,	22,	22,	
	21,	21,	20,	19,	19,	18,	17,	17,	
	16,	16,	15,	15,	14,	14,	13,	12,	
	12,	11,	11,	10,	10,	9,	9,	8,	
	8,	7,	7,	7,	6,	6,	5,	5,	
	4,	4,	3,	3,	3,	2,	2,	1,	
	1,	1,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0
	};
/**
 * \brief default constructor for the intensity of the Led
 * \param none
 * \return none
 */

Sensor::Sensor() : convertisseur_()
{
	DDRA = 0x00;
	positionG_ = 0;
	positionD_ = 2;
	valeurVoltageG_ = 0;
	valeurVoltageD_ = 0;
}

/**
 * \brief return distance between bot and wall
 * \param valeurIntensite_ determines color of Led
 * \return none
 */
 
uint8_t Sensor::getDistanceG()
{
	valeurVoltageG_ = convertisseur_.read(positionG_) >> 2;
	
	uint16_t rv = (distance[valeurVoltageG_]+10)/5;
	return rv;
	
}

/**
 * \brief return distance between bot and wall
 * \param valeurIntensite_ determines color of Led
 * \return none
 */
 
uint8_t Sensor::getDistanceD()
{
	valeurVoltageD_ = convertisseur_.read(positionD_) >> 2;
	
	uint16_t rv = (distance[valeurVoltageD_]+10)/5;
	return rv;
	
}

/**
 * \brief sets pin's position on A port
 * \param position of pin on A port
 * \return none
 */
 
void Sensor::setPositionGauche(uint8_t positionG)
{
	positionG_ = positionG;
	
}
void Sensor::setPositionDroite(uint8_t positionD)
{
	positionD_ = positionD;
}

