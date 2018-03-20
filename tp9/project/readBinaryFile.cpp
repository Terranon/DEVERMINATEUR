/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Simple test program for the library 'deverminateur'. Robot will
 *              play a note when program first begins then will move forward
 *              when the photocell senses high luminosity and backwards when it
 *              senses low luminosity. The Led will also respond to luminosity.
 * 
 * Pinout :                                      (- +) LED             Jumper  
 *                                                | |                       |
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  0 1 2 3 4 5 6 7    PORTD  1 3 5 7        
 *        0 2 4 6           0 2 4 6                                         |        
 *                                                                      0 2 4 6
 *                                                                              
 * 
 *                                                
 *                
 * 
 * Version: 1.0
\******************************************************************************/

#include <fstream>
using namespace std;

/******************************************************************************\
 * Main
\******************************************************************************/

/**
 * \brief main function
 * \return exit code
 */
 /*
int main () {
    uint16_t tailleTableau = 78;
    uint8_t tab[tailleTableau] = {};
    ifstream fichierEntree;
    fichierEntree.open("fichierDeSortie", ios::binary);
		fichierEntree.seekg(0, ios::beg);
		
    while(fichier.peek != eof){
			for(uint16_t i = 0; i < tailleTableau; i++){
					uint8_t octet;
					fichierEntree.read((char *) &octet, sizeof(uint8_t));
					tab[i] = octet;			 
			}
		}
		
		Memoire24CXXX mem;
		for(uint16_t i = 0; i < tailleTableau; i++){
			mem.ecriture(i, tab[i]);
		}
    return 0;
}
*/
