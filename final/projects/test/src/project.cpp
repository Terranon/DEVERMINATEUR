/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Le programme suivant impose au robot de rester a 
				une distance de 15 cm d'un mur a droite. Nous ne prenons pas en 
				consideration les poteaux et les fins de murs. Ce programme  
				utilise donc les classes Sensor et Motor. De plus, ce programme 
				permet au robot de changer de direction de maniere fluide.
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

Motor bot;
Sensor sensor;
Button bouton;
enum State {INIT, MUR_GAUCHE, MUR_DROIT,BOUTON};




/******************************************************************************\
 * Init
	Initialisation 
\******************************************************************************/
void init(){
	DDRA = 0x00; //port entree

}

/******************************************************************************\
 * Loop
	Boucle infini imposant au robot de rester a une distance de 15 cm du mur droit
\******************************************************************************/
void loop(){
	uint8_t distanceDetecteurDroit = sensor.getDistanceG();
	uint8_t distanceDetecteurGauche = sensor.getDistanceD();
	
	State etat = INIT;
	
	switch(etat){
		
		case INIT:							//detecte le mur le plus pres et va commencer a
			if (bouton.isPressed())
				etat = BOUTON;
			else if(distanceDetecteurDroit < distanceDetecteurGauche)	//le suivre
				etat = MUR_DROIT;
			else
				etat = MUR_GAUCHE;
		break;
		
		case MUR_DROIT:
			if(distanceDetecteurDroit < 15 )
				bot.setSpeed(220, 130);
			else
				bot.setSpeed(130, 220);
		break;
		
		case MUR_GAUCHE:
		 if (distanceDetecteurGauche < 15)
				bot.setSpeed(130, 220);
			else
				bot.setSpeed(220, 130);					
		break;

		case BOUTON:
			
	
	}
}
/******************************************************************************\
 * Main
\******************************************************************************/
int main(){
	init();
	while(1){
		loop();
	}
}
