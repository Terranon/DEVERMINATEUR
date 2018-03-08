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
    
	PhotoCell();
	void allumeDelAmbree() const;
	void SetCouleurLed();
	
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
