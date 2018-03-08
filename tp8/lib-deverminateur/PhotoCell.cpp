/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: PhotoCell.cpp
 * Description:
 * Version: 1.0
\******************************************************************************/

#include "PhotoCell.h"

/**
 * \brief default constructor for the intensity of the Led
 * \param none
 * \return none
 */
PhotoCell::PhotoCell() : convertisseur_()
{
	valeurIntensite_ = 0;
	position_ = 0;
}

/**
 * \brief sets Led's color based on valeurIntensite_'s value. Led's
 * color will stay the same as long as the intensity stays in the range
 * \param valeurIntensite_ determines color of Led
 * \return none
 */
uint8_t PhotoCell::getValeurIntensite(){
	

	valeurIntensite_ = convertisseur_.read(position_) >> 2;
	return valeurIntensite_;
}


void PhotoCell::setPosition(uint8_t position){
	position_ = position;
}
