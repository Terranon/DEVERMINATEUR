/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.h
 * Description: PINA0
 * Version: 1.0
\******************************************************************************/

#ifndef SENSOR_H
#define SENSOR_H

#include <avr/io.h>
#include "Adc.h"

class Sensor {
public:

	/**
	 * \brief default constructor for the intensity of the Led
	 * \param pinG position of left sensor data pin
	 * \param pinD position of right sensor data pin
   * \return a Sensor
   */
	Sensor(uint8_t pinG, uint8_t pinD);
 
	uint8_t getDistanceG();
	uint8_t getDistanceD();

private:
	
	uint8_t getDistance(uint8_t pin);

	Adc convertisseur_;
	uint8_t pinG_;
	uint8_t pinD_;

};
#endif
