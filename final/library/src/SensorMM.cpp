/******************************************************************************\
 * Authors: Thomas Dufour, Jean-Raphael Matte
 * Name: Sensor.cpp
 * Description: This class reads data from the rangefinders using the ADC and
 *              converts the voltage to a usable distance, in mm.
 * 
 * Version: 1.0
\******************************************************************************/

#include "SensorMM.h"

SensorMM::SensorMM(){
	DDRA = 0x00;
}
 
uint16_t SensorMM::getDistanceL() {
	return getDistance(PIN_L);
}

uint16_t SensorMM::getDistanceR() {
	return getDistance(PIN_R);
}

uint16_t SensorMM::getDistance(uint8_t pin) {
	
	// Find the mean value of 32 readings to cancel out the electrical noise
	uint16_t sumReadings = 0;
	for (uint8_t i = 0; i < 32; i++) {
		 sumReadings += adc_.read(pin);
	}
	
	// Divide by 32 (bitshift right 5)
	uint16_t moyenne = sumReadings >> 5;
	
	return DISTANCES[moyenne];
	
}
