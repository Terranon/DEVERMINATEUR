/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.h
 * Description:
 * Version: 1.0
\******************************************************************************/

#ifndef PHOTOCELL_H
#define PHOTOCELL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
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
 * \brief allumerDelAmbree turns the Led to ambree
 * \param none
 * \return none
 */
	void allumeDelAmbree() const;
	
	/**
 * \brief sets Led's color based on valeurIntensite_'s value. the Led's
 * 		will keep his color as long as the intensity stays in the range
 * \param valeurIntensite_ determines color of Led
 * \return none
 */
	void setCouleurLed();
	
	static const uint8_t position = 0;
	static const uint8_t ENTREE = 0x00;
	static const uint8_t SORTIE = 0xff;
	static const uint8_t DEL_ROUGE = (1<<1);
	static const uint8_t DEL_VERT = (1<<0);
	static const uint8_t intensiteFaible = 140;
	static const uint8_t intensiteMoyenne = 230;
    
private:
	uint8_t valeurIntensite_ = 0;

};
#endif
