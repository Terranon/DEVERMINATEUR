/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.cpp
 * Description:
 * Version: 1.0
\******************************************************************************/

#include "Sensor.h"

//Distances{10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};

/**
 * \brief default constructor for the intensity of the Led
 * \param none
 * \return none
 */

Sensor::Sensor() : convertisseur_()
{

	position_ = 0;
	valeurVoltage_ = 0;
}

/**
 * \brief return distance between bot and wall
 * \param valeurIntensite_ determines color of Led
 * \return none
 */
 
uint8_t Sensor::getValeurVoltage()
{
	valeurVoltage_ = convertisseur_.read(position_) >> 2;
	
	return valeurVoltage_;
}


/**
 * \brief sets pin's position on A port
 * \param position of pin on A port
 * \return none
 */
 /*
void Sensor::setPosition(uint8_t position)
{
	position_ = position;
}
*/
