/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.cpp
 * Description:
 * Version: 1.0
\******************************************************************************/

#include "Sensor.h"

int distances = {};

/**
 * \brief default constructor for the intensity of the Led
 * \param none
 * \return none
 */

Sensor::Sensor() : convertisseur_()
{
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
 
uint8_t Sensor::getDistance()
{
	valeurVoltageG_ = convertisseur_.read(position_) >> 2;
	
	valeurVoltageD_ = convertisseur_.read(position_) >> 2;
	
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

