/*****************************************************************************\
 * Authors: Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour, William Chartrand
 * Name: sPhotoCell.h
 * Description:
 * Version: 1.0
\******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

class PhotoCell {
public:
    
PhotoCell(uint8_t valeurIntensite);
void AllumeDelAmbre;
void SetCouleurLed(valeurIntensite);
can convertisseur;
PhotoCell~;
    
private:

uint8_t valeurIntensite_;
const uint8_t ENTREE = 0x00;      
const uint8_t SORTIE = 0xff;
const uint8_t DEL_ROUGE = (1<<1);
const uint8_t DEL_VERT = (1<<0);
const uint8_t intensiteFaible = 140; 
const uint8_t intensiteMoyenne = 230;
DDRA = ENTREE;
DDRC = SORTIE;

};
