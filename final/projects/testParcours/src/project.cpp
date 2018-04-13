
#include "Motor.h"
#include "Sensor.h"
#include "Button.h"
#include "Obstacle.h"
#include "Led.h"

Motor bot;
Button bouton;
Sensor sensor;						//on initialise le sensor gauche a PA0 et le sensor droit a PA2
Obstacle obstacle;
								
const uint8_t DISTANCE_OPTIMALE = 15;
enum State {START, MUR_GAUCHE, MUR_DROIT, ROTATION_GAUCHE, ROTATION_DROIT, TRANSITION_GAUCHE, TRANSITION_DROIT};
/*
//******************************************************************************
//  Loop
//	Boucle infini imposant au robot de rester a une distance de 15 cm du mur droit
//******************************************************************************
void loop(){			
	State etat = START;				//on initialise etat a INIT
	DDRC = 0xff;							//on initilise le portC en entree pour la del
	bot.setSpeed(0, 255);

	while(1){
		uint8_t distanceDetecteurDroit = sensor.getDistanceD();		//distance detectee a droite
		uint8_t distanceDetecteurGauche = sensor.getDistanceG();	//distance detectee a gauche

//SWITCH CASE

		switch(etat){
			case START:								//detecte le mur le plus pres et va commencer a le suivre
				if(distanceDetecteurDroit < distanceDetecteurGauche)	
					etat = MUR_DROIT;
				else
					etat = MUR_GAUCHE;		
			break;

//DEPLACEMENTS SIMPLES
		
			case MUR_DROIT:						//suit un mur a droite
				PORTC = 0x01; 					//allume rouge si un mur a droite
				bot.setDirection(Motor::FRWD, Motor::FRWD);
				if(distanceDetecteurDroit < DISTANCE_OPTIMALE)
					bot.setSpeed(220, 150);
				else
					bot.setSpeed(150, 220);
					
				obstacle.push(distanceDetecteurGauche);			//On push la distance observe par le capteur oppose
			break;
			
			case MUR_GAUCHE:					//suit un mur a gauche
				PORTC = 0x02; 					//allume vert si un mur a gauche
			  bot.setDirection(Motor::FRWD, Motor::FRWD);
				if (distanceDetecteurGauche < DISTANCE_OPTIMALE)
					bot.setSpeed(150, 220);
				else
					bot.setSpeed(220, 150);
					
				obstacle.push(distanceDetecteurDroit);			//On push la distance observe par le capteur oppose		
			break;

//ROTATION

			case ROTATION_GAUCHE:				//effectue une rotation vers la gauche de 180 degre puis suit un mur a sa gauche
				PORTC = 0x00;
				bot.setDirection(Motor::FRWD, Motor::BACK);
				bot.setSpeed(200, 200);
				if (distanceDetecteurGauche < DISTANCE_OPTIMALE) 
				{
					etat = MUR_GAUCHE;
				}
			break;

			case ROTATION_DROIT:				//effectue une rotation vers la droite de 180 degre puis suit un mur a sa droite
				PORTC = 0x00;
			  bot.setDirection(Motor::BACK, Motor::FRWD);
			  bot.setSpeed(200, 200);
				if (distanceDetecteurDroit < DISTANCE_OPTIMALE) 
				{
					etat = MUR_DROIT;
				}
			break;

//TRANSITION
	
			case TRANSITION_GAUCHE:			//effectue une transition vers la gauche vers un mur
				bot.setSpeed(190, 220);
				if(distanceDetecteurGauche < DISTANCE_OPTIMALE)
					etat = MUR_GAUCHE;
			break;
			
			case TRANSITION_DROIT:			//effectue une transition vers la droite vers un mur
				bot.setSpeed(220, 190);
				if(distanceDetecteurDroit < DISTANCE_OPTIMALE)
					etat = MUR_DROIT;			
			break;
			
		}
		
		
//SCRUTATION	
		
		//s'informe sur ce qu'il se passe avec l'autre sensor
		uint8_t detectionObstacle = obstacle.detectionObstacle();
		if(detectionObstacle == 1)			//il s'agit d'un poteau
			//inserer se que fait le robot lorsquon detecte un poteau
		if(detectionObstacle == 2){
			if (etat == MUR_GAUCHE)
				etat = TRANSITION_DROIT;
			else
				etat = TRANSITION_GAUCHE;
		}
		
		//s'informe si le bouton est appuye
		if (bouton.isPressed()){					//observe si le bouton est appuye
			if (etat == MUR_DROIT)					//si il suivait un mur droit, il va faire une rotation sur sa gauche
				etat = ROTATION_GAUCHE;
			else
				etat = ROTATION_DROIT;
		}
	}
		
}
*/
//******************************************************************************
 // Main
//******************************************************************************
int main(){
	//loop();
}

