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
#include "Button.h"
#include "Obstacle.h"
#include "Led.h"
#include <util/delay.h>

Motor bot;								//utilisation des deux moteurs
Button bouton;						//utilisation d'un bouton
Sensor sensor;						//on initialise le sensor gauche a PA0 et le sensor droit a PA2
Led led;									//on ititialise la led au portC
Obstacle obstacle;				//utilisation de la classe obstacle pour detecter les murs et les poteaux
								
const uint8_t DISTANCE_OPTIMALE = 15;
const uint8_t DISTANCE_ARRET_ROTATION = 17;
enum State {START, MUR_GAUCHE, MUR_DROIT, ROTATION_GAUCHE, ROTATION_DROIT, TRANSITION_GAUCHE, TRANSITION_DROIT};

//******************************************************************************
//  Loop
//	Boucle infini imposant au robot de rester a une distance de 15 cm du mur droit
//******************************************************************************
void loop(){	
	State etat = START;				//on initialise etat a START
	bool detecterMur = false;
	
	
	while(1){
		uint8_t distanceDetecteurDroit = sensor.getDistanceR();		//distance detectee a droite
		uint8_t distanceDetecteurGauche = sensor.getDistanceL();	//distance detectee a gauche
			
//SWITCH CASE

		switch(etat){
			case START:								//detecte le mur le plus pres et va commencer a le suivre
				if(distanceDetecteurDroit < distanceDetecteurGauche)	
					etat = MUR_DROIT;
				else
					etat = MUR_GAUCHE;		
			break;

//DEPLACEMENTS SIMPLES
		
			case MUR_DROIT:											//suit un mur a droite
				led.setColor(Led::RED); 					//allume rouge si un mur a droite
				bot.setDirection(Motor::FRWD, Motor::FRWD);
				if(distanceDetecteurDroit < DISTANCE_OPTIMALE)
					bot.setSpeed(100, 160);
				else
					bot.setSpeed(160, 100);
				if(!detecterMur)
					obstacle.push(distanceDetecteurGauche);			//On push la distance observe par le capteur oppose
			break;
			
			
			case MUR_GAUCHE:					//suit un mur a gauche
				led.setColor(Led::GREEN);  					//allume vert si un mur a gauche
				bot.setDirection(Motor::FRWD, Motor::FRWD);
				if (distanceDetecteurGauche < DISTANCE_OPTIMALE)
					bot.setSpeed(160, 100);
				else
					bot.setSpeed(100, 160);
				if(!detecterMur)
					obstacle.push(distanceDetecteurDroit);			//On push la distance observe par le capteur oppose		
			break;

//ROTATION

			case ROTATION_GAUCHE:				//effectue une rotation vers la gauche de 180 degre puis suit un mur a sa gauche
				led.setColor(Led::OFF); 
				bot.setDirection(Motor::BACK, Motor::FRWD);
				bot.setSpeed(120, 120);
				if (distanceDetecteurGauche < DISTANCE_ARRET_ROTATION) 
				{
					etat = MUR_GAUCHE;
				}
			break;

			case ROTATION_DROIT:				//effectue une rotation vers la droite de 180 degre puis suit un mur a sa droite
				led.setColor(Led::OFF); 
				bot.setDirection(Motor::FRWD, Motor::BACK);
				bot.setSpeed(120, 120);
				if (distanceDetecteurDroit < DISTANCE_ARRET_ROTATION) 
				{
					etat = MUR_DROIT;
				}
			break;

//TRANSITION
	
			case TRANSITION_GAUCHE:			//effectue une transition vers la gauche vers un mur
				led.setColor(Led::OFF);
				bot.setSpeed(110, 160);
				if(distanceDetecteurGauche < DISTANCE_OPTIMALE)
				{
					etat = MUR_GAUCHE;
					detecterMur = true;
				}
			break;
			
			case TRANSITION_DROIT:			//effectue une transition vers la droite vers un mur
				led.setColor(Led::OFF); 
				bot.setSpeed(160, 110);
				if(distanceDetecteurDroit < DISTANCE_OPTIMALE)
				{
					etat = MUR_DROIT;
					detecterMur = true;
				}			
			break;			
	
		}

//SCRUTATION


//SECTION DETECTION MUR ET POTEAU

		//s'informe sur ce qui se passe avec l'autre sensor
		if (etat != TRANSITION_DROIT && etat != TRANSITION_GAUCHE && !detecterMur){
			uint8_t detectionObstacle = obstacle.analyze();
			//if(detectionObstacle == Obstacle::POLE)			//il s'agit d'un poteau
				//inserer se que fait le robot lorsquon detecte un poteau
			if(detectionObstacle == Obstacle::WALL){			//2 == Obstacle::WALL
				if (etat == MUR_GAUCHE)
					etat = TRANSITION_DROIT;
				else if (etat == MUR_DROIT)
					etat = TRANSITION_GAUCHE;
			}
		}
//SECTION DETECTION BOUTON
		//observe si le bouton est appuye
		if (bouton.isPressed()){					//observe si le bouton est appuye
			if (etat == MUR_DROIT)					//si il suivait un mur droit, il va faire une rotation sur sa gauche
				etat = ROTATION_GAUCHE;
			else if (etat == MUR_GAUCHE)
				etat = ROTATION_DROIT;		
		}
		_delay_ms(50);
	}
}

//******************************************************************************
 // Main
//******************************************************************************
int main(){
	loop();
}

