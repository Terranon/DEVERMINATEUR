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
	valeurDistance = 0;
	position_ = 0;
}
/*
void Sensor::setDistance(uint8_t dist){

		case 10:
			//OUTPUT 2.6V
		case 15:
			//OUTPUT 1.75V
		case 20:
			//OUTPUT 1.4V
		case 25:
			//OUTPUT 1.13V
		case 30:
			//OUTPUT 0.96V
		case 35:
			//OUTPUT 0.85V
		case 40:
			//OUTPUT 0.75V
		case 45:
			//OUTPUT 0.67V
		case 50:
			//OUTPUT 0.62V
		case 55:
			//OUTPUT 0.58V
		case 60:
			//OUTPUT 0.53V
		case 65:
			//OUTPUT 0.5V
		case 70:
			//OUTPUT 0.47V
		case 75:
			//OUTPUT 0.43V
		case 80:
			//OUTPUT 0.41V
}
*/
/**
 * \brief return distance between bot and wall
 * \param valeurIntensite_ determines color of Led
 * \return none
 */

uint8_t Sensor::getDistance()
{
	valeurVoltage_ = convertisseur_.read(position_) >> 2;
	uint8_t distance = (6787/(valeurVoltage_-3))-4;
	if (distance < 10)
		return 0;
	if (distance > 60)
		return 255
	else
		return distance;
}


/**
 * \brief sets pin's position on A port
 * \param position of pin on A port
 * \return none
 */
void Sensor::setPosition(uint8_t position)
{
	position_ = position;
}
