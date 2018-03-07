/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.cpp
 * Description:
 * Version: 1.0
\******************************************************************************/

#include "PhotoCell.h"
#include "can.h"

/**
 * \brief default constructor for the intensity of the Led
 * \param valeurIntensite_ sets the Led's color
 * \return none
 */
 
PhotoCell::PhotoCell(uint8_t valeurIntensite_ = 0){
}

/**
 * \brief allumerDelAmbree turns the Led to ambree
 * \param none
 * \return none
 */
 
void PhotoCell::allumerDelAmbree(){
	PORTC = DEL_ROUGE;
	_delay_ms(5);
	PORTC = DEL_VERT;
	_delay_ms(10);
}

/**
 * \brief sets Led's color based on valeurIntensite_'s value. the Led's
 * 		will keep his color as long as the intensity stays in the range
 * \param valeurIntensite_ determines color of Led
 * \return none
 */
 
void PhotoCell::SetCouleurLed(valeurIntensite_){
	
	while(1){
		
	valeurIntensite_ = convertisseur.lecture(position) >> 2;
	
	if (valeurIntensite_ < intensiteFaible)
		PORTC = DEL_VERT;

    else if (valeurIntensite_ < intensiteMoyenne)  
		allumerDelAmbree();

	else 
		PORTC = DEL_ROUGE;
	}
}

/**
 * \brief destructor for the Led
 * \param pwmFreq sets begining frequency of the pwm in Hz
 * \return an Led
 */
 
PhotoCell::~PhotoCell{
}
