/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.cpp
 * Description:
 * Version: 1.0
\******************************************************************************/

#include "PhotoCell.h"

/**
 * \brief default constructor for the intensity of the Led
 * \param valeurIntensite_ sets the Led's color
 * \return none
 */
 
PhotoCell::PhotoCell():
	valeurIntensite_(0){
}

/**
 * \brief allumerDelAmbree turns the Led to ambree
 * \param none
 * \return none
 */
 
void PhotoCell::allumeDelAmbree() const{
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
 
void PhotoCell::SetCouleurLed(){
	
	can convertisseur;
	while(1){
		
	valeurIntensite_ = convertisseur.lecture(position) >> 2;
	
	if (valeurIntensite_ < intensiteFaible)
		PORTC = DEL_VERT;

    else if (valeurIntensite_ < intensiteMoyenne)  
		allumeDelAmbree();

	else 
		PORTC = DEL_ROUGE;
	}
}
