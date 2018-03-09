/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.h
 * Description: PINA0
 * Version: 1.0
\******************************************************************************/

#ifndef PHOTOCELL_H
#define PHOTOCELL_H

#include <avr/io.h>
#include "Adc.h"

class PhotoCell {
public:
/**
 * \brief default constructor for the intensity of the Led
 * \param none
 * \return none
 */
	PhotoCell();

/**
 * \brief sets Led's color based on valeurIntensite_'s value. the Led's
 * 		will keep his color as long as the intensity stays in the range
 * \param valeurIntensite_ determines color of Led
 * \return value of intensity
 */
	uint8_t getValeurIntensite();
	
/**
 * \brief sets pin's position on A port
 * \param position of pin on A port
 * \return none
 */
	void setPosition(uint8_t position);
	
	
private:
	uint8_t valeurIntensite_;
	Adc convertisseur_;
	uint8_t position_;

};
#endif
