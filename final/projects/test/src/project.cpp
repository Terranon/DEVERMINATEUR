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

enum State {INIT, MUR_GAUCHE, MUR_DROITE};

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
	uint8_t distanceDetecteurDroit = sensor.getValeurVoltage();
	uint8_t distanceDetecteurGauche = sensor.getValeurVoltage();
	
	State etat = INIT;
	
	switch(etat){
		
		case INIT:
			if(distanceDetecteurDroit < 25)
				etat = MUR_DROITE;
			else
				etat = MUR_GAUCHE;
		break;
		
		case MUR_GAUCHE:
			if(distanceDetecteurDroit < 15 )
				bot.setSpeed(220, 150);
			else
				bot.setSpeed(150, 220);
			
			//VERIFICATION D'UN POTEAU DE L'AUTRE COTE	
			
		break;
		
		case MUR_DROITE:
		 if (distanceDetecteurGauche < 15)
				bot.setSpeed(150, 220);
			else
				bot.setSpeed(220, 150);			
			//VERIFICATION D'UN POTEAU DE L'AUTRE COTE
		
		break;
	
		
		
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
