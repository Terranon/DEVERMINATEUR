/******************************************************************************\
 * Authors: Thomas Dufour, Jean-Raphael Matte
 * Name: Sensor.cpp
 * Description: This class reads data from the rangefinders using the ADC and
 *              converts the voltage to a usable distance, in cm.
 * 
 * Version: 1.2
\******************************************************************************/

#include "Sensor.h"

Sensor::Sensor(){
	DDRA = 0x00;
}
 
uint8_t Sensor::getDistanceL() {
	return getDistance(PIN_L);
}

uint8_t Sensor::getDistanceR() {
	return getDistance(PIN_R);
}

uint8_t Sensor::getDistance(uint8_t pin) {
	
	// Find the mean value of 32 readings to cancel out the electrical noise
	uint16_t sumReadings = 0;
	for (uint8_t i = 0; i < 32; i++) {
		 sumReadings += adc_.read(pin);
	}
	
	// Divide by 32 (bitshift right 5) and bitshift right 2
	// so that the 10 bit value given by Adc::read can fit in a single byte
	uint8_t moyenne = sumReadings >> 7;
	
	return DISTANCES[moyenne];
	
}
