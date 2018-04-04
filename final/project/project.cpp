/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Le programme suivant impose au robot de rester a 
				une distance de 15 cm d'un mur a droite. Nous ne prenons pas en 
				consideration les poteaux et les fins de murs. Ce programme  
				utilise donc les classes Sensor et Motor.

				De plus, ce programme permet au robot de changer de direction de maniere
				fluide.
 * 
 * Pinout :                                                     
 *                                                                     
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  0 1 2 3 4 5 6 7    PORTD  1 3 5 7        
 *        0 2 4 6           0 2 4 6                                     0 2 4 6       
 *                                                                      

 * Version: 1.0
\******************************************************************************/
#include "Motor.h"
#include "Sensor.h"
#include "Path.h"
Motor bot;
Path path;

/******************************************************************************\
 * Init
	Initialisation 
\******************************************************************************/
void init(){

}

/******************************************************************************\
* TestLeCapteur
	Fonction permettant de verifier le bon fonctionnement du capteur
\******************************************************************************/
void testLeCapteur() {

}

/******************************************************************************\
 * Loop
	Boucle infini imposant au robot de rester a une distance de 15 cm du mur
\******************************************************************************/
void loop(){
	if(distanceDroite = 15){
		bot.setSpeed(200, 200);
	}
	else if(distanceDroite > 15){
		bot.setSpeed(200, 100);
	}
	else if(distanceDroite < 15){
		bot.setSpeed(100, 200);
	}
	path.setNewDistance();
	bool verification = path.authorizationToContinue();
	if (!verification)
		//si il detecte une fin de mur, il est pret a agir en consequence

}

/******************************************************************************\
 * Main
\******************************************************************************/
int main(){
	init();
	testeLeCapteur();
	while(1){
		loop();
	}
}
