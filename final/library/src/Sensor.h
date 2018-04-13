/******************************************************************************\
 * Authors: Thomas Dufour, Jean-Raphael Matte
 * Name: Sensor.h
 * Description: This class reads data from the rangefinders using the ADC and
 *              converts the voltage to a usable distance, in cm.
 * 
 * Version: 1.2
\******************************************************************************/

#ifndef SENSOR_H
#define SENSOR_H

#include <avr/io.h>
#include "Adc.h"

volatile const uint8_t DISTANCES[256] = {
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
	5,	5,	5,	5,	5,	5,	5,	5
};

class Sensor {
public:
	
	/**
	 * \brief constructor
	 * \return a Sensor
	 */
	Sensor();
	
	/**
	 * \brief give the reading of the left sensor
	 * \return the reading of the left sensor, in cm
	 */
	uint8_t getDistanceL();
	
	/**
	 * \brief give the reading of the right sensor
	 * \return the reading of the right sensor, in cm
	 */
	uint8_t getDistanceR();

private:
	
	/**
	 * \brief gives the distance reading of a sensor connected to the selected
	 *        pin
	 * \param pin the pin on which the sensor is connected
	 */
	uint8_t getDistance(uint8_t pin);

	Adc adc_;
	
	//static const uint8_t PIN_L = 0;
	//static const uint8_t PIN_R = 2;
	uint8_t PIN_R;
	uint8_t PIN_L;

};

#endif
