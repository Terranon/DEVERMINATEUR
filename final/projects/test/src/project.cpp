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
#include "Piezo.h"
#include "Timer.h"
#include <util/delay.h>

const uint8_t DISTANCE_OPTIMALE = 15;
const uint8_t DISTANCE_FIN_TRANSITION = 20;
const uint8_t DISTANCE_ARRET_ROTATION = 17;
const uint8_t DISTANCE_MAXIMALE = 60;

const uint8_t DELTA_D_OPTIMAL = 1;
const uint8_t NB_LOOP_COLLECT = 4;

const uint8_t LO_SPEED = 100;
const uint8_t HI_SPEED = 140;

enum State {
	START,
	MUR_GAUCHE,
	MUR_DROIT,
	ROTATION_GAUCHE,
	ROTATION_DROIT,
	TRANSITION_GAUCHE_TOURNE,
	TRANSITION_GAUCHE_COLLECT,
	TRANSITION_GAUCHE_FONCE,
	TRANSITION_GAUCHE_REDRESSE,
	TRANSITION_DROIT_TOURNE,
	TRANSITION_DROIT_COLLECT,
	TRANSITION_DROIT_FONCE,
	TRANSITION_DROIT_REDRESSE
};

enum SoundState {
	OFF,
	TONE1,
	PAUSE1,
	TONE2,
	PAUSE2,
	TONE3
};

//******************************************************************************
// Loop
// Boucle infini imposant au robot de rester a 15 cm du mur droit
//******************************************************************************
void loop() {

	// utilisation des deux moteurs
	Motor bot;

	// utilisation d'un bouton
	Button bouton;

	// on initialise le sensor gauche a PA0 et le sensor droit a PA2
	Sensor sensor;

	// on initialise la led au portC
	Led led;

	// utilisation de la classe obstacle pour detecter les murs et les poteaux
	Obstacle obstacle;

	// On utilise le piezo pour faire des sons
	Piezo piezo;

	// On utilise le timer pour gerer le timing de la musique
	Timer timer;

	// On initialise etat a START
	State etat = START;

	// n initialise musique a OFF
	SoundState musique = OFF;

	// vrai si on vient juste de faire une transition
	bool postTransition = false;

	// ancienne distance
	uint8_t ancienneDistance;

	// variation de la distance
	uint8_t deltaD = 0;

	// distance detectee a droite
	uint8_t distanceDetecteurDroit = 0;

	// distance detectee a gauche
	uint8_t distanceDetecteurGauche = 0;

	// compteur de boucle
	uint8_t compteur = 0;

	// Boucle principale
	while(1){

		distanceDetecteurDroit = sensor.getDistanceR();
		distanceDetecteurGauche = sensor.getDistanceL();

		// SWITCH CASE

		switch (etat) {

			// detecte le mur le plus pres et va commencer a le suivre
			case START:
				if (distanceDetecteurDroit < distanceDetecteurGauche) {
					etat = MUR_DROIT;
				} else {
					etat = MUR_GAUCHE;
				}
				break;

			// DEPLACEMENTS SIMPLES
		
			// Suit un mur a droite
			case MUR_DROIT:

				// allume rouge si un mur a droite
				led.setColor(Led::RED);

				// on avance
				bot.setDirection(Motor::FRWD, Motor::FRWD);

				// si on est trop proche
				if (distanceDetecteurDroit < DISTANCE_OPTIMALE) {
					// on s'eloigne
					bot.setSpeed(LO_SPEED, HI_SPEED);
				} else {
					// on se rapproche
					bot.setSpeed(HI_SPEED, LO_SPEED);
				}

				// Si on a fait une transition et qu'il n'y a pas eu 
				// d'interruption dans l'ancien mur, on attends de trouver un 
				// trou
				if (postTransition) {
					if (distanceDetecteurGauche > DISTANCE_MAXIMALE) {
						postTransition = false;
					}
				} else {
					//On push la distance observe par le capteur oppose
					obstacle.push(distanceDetecteurGauche);
				}

				break;
			
			// suit un mur a gauche
			case MUR_GAUCHE:

				// allume vert si un mur a gauche
				led.setColor(Led::GREEN);

				// on avance
				bot.setDirection(Motor::FRWD, Motor::FRWD);

				// si on est trop proche
				if (distanceDetecteurGauche < DISTANCE_OPTIMALE) {
					// on s'eloigne
					bot.setSpeed(HI_SPEED, LO_SPEED);
				} else {
					// on se rapproche
					bot.setSpeed(LO_SPEED, HI_SPEED);
				}

				// Si on a fait une transition et qu'il n'y a pas eu 
				// d'interruption dans l'ancien mur, on attends de trouver un 
				// trou
				if (postTransition) {
					if (distanceDetecteurDroit > DISTANCE_MAXIMALE) {
						postTransition = false;
					}
				} else {
					//On push la distance observe par le capteur oppose
					obstacle.push(distanceDetecteurDroit);
				}

				break;

			//ROTATION

			// effectue une rotation vers la gauche de 180 degres puis suit un 
			// mur a sa gauche
			case ROTATION_GAUCHE:

				// on eteint la led
				led.setColor(Led::OFF);

				// on tourne sur nous meme a gauche
				bot.setDirection(Motor::BACK, Motor::FRWD);
				bot.setSpeed(LO_SPEED, LO_SPEED);

				// on arrete de tourner lorsque la distance est bonne
				if (distanceDetecteurGauche < DISTANCE_ARRET_ROTATION) {
					etat = MUR_GAUCHE;
				}

				break;

			// effectue une rotation vers la droite de 180 degres puis suit un 
			// mur a sa droite
			case ROTATION_DROIT:

				// on eteint la led
				led.setColor(Led::OFF);

				// on tourne sur nous meme a droite
				bot.setDirection(Motor::FRWD, Motor::BACK);
				bot.setSpeed(LO_SPEED, LO_SPEED);

				// on arrete de tourner lorsque la distance est bonne
				if (distanceDetecteurDroit < DISTANCE_ARRET_ROTATION) {
					etat = MUR_DROIT;
				}

				break;

			// TRANSITION

			// effectue une transition vers la gauche vers un mur
			case TRANSITION_GAUCHE_TOURNE:

				// on eteint la led
				led.setColor(Led::OFF);

				// on avance
				bot.setDirection(Motor::FRWD, Motor::FRWD);

				// Si on voit encore le mur
				if (distanceDetecteurGauche < DISTANCE_MAXIMALE + 10) {
					// on tourne
					bot.setSpeed(LO_SPEED, HI_SPEED);
				} else {
					// on avance droit
					bot.setSpeed(HI_SPEED, HI_SPEED);

					// on enregistre la distance
					ancienneDistance = distanceDetecteurGauche;

					// on redemarre le compteur
					compteur = 0;

					// on calcule la vitesse
					etat = TRANSITION_GAUCHE_COLLECT;
				}
				
				// Fin de la transition
				if (distanceDetecteurGauche < DISTANCE_OPTIMALE + 2) {
					postTransition = true;
					obstacle.clear();
					etat = MUR_GAUCHE;
				}

				break;

			case TRANSITION_GAUCHE_COLLECT:

				// on attend un certain nombre d'execution de la boucle
				if (compteur > NB_LOOP_COLLECT) {

					// on calcule deltaD
					deltaD = ancienneDistance - distanceDetecteurGauche;

					// si deltaD n'est pas assez grand
					if (deltaD < DELTA_D_OPTIMAL) {

						// on tourne
						etat = TRANSITION_GAUCHE_TOURNE;

					} else {

						// on fonce
						etat = TRANSITION_GAUCHE_FONCE;

					}
				}

				break;

			case TRANSITION_GAUCHE_FONCE:

				// on avance droit
				bot.setSpeed(HI_SPEED, HI_SPEED);
				
				// Fin de la transition
				if (distanceDetecteurGauche < DISTANCE_FIN_TRANSITION) {
					etat = TRANSITION_GAUCHE_REDRESSE;
				}

				break;

			case TRANSITION_GAUCHE_REDRESSE:

				// on tourne a droite
				bot.setSpeed(HI_SPEED, LO_SPEED);

				if (distanceDetecteurGauche < DISTANCE_OPTIMALE) {
					obstacle.clear();
					postTransition = true;
					etat = MUR_GAUCHE;
				}

				break;
			
			// effectue une transition vers la droite vers un mur
			case TRANSITION_DROIT_TOURNE:

				// on eteint la led
				led.setColor(Led::OFF);

				// on avance
				bot.setDirection(Motor::FRWD, Motor::FRWD);

				// Si on voit encore le mur
				if (distanceDetecteurDroit < DISTANCE_MAXIMALE + 10) {
					// on tourne
					bot.setSpeed(HI_SPEED, LO_SPEED);
				} else {
					// on avance droit
					bot.setSpeed(LO_SPEED, LO_SPEED);

					// on enregistre la distance
					ancienneDistance = distanceDetecteurDroit;

					// on redemarre le compteur
					compteur = 0;

					// on calcule la vitesse
					etat = TRANSITION_DROIT_COLLECT;
				}
				
				// Fin de la transition
				if (distanceDetecteurDroit < DISTANCE_OPTIMALE + 4) {
					postTransition = true;
					obstacle.clear();
					etat = MUR_DROIT;
				}

				break;

			case TRANSITION_DROIT_COLLECT:

				// on attend un certain nombre d'execution de la boucle
				if (compteur > NB_LOOP_COLLECT) {

					// on calcule deltaD
					deltaD = ancienneDistance - distanceDetecteurDroit;

					// si deltaD n'est pas assez grand
					if (deltaD < DELTA_D_OPTIMAL) {

						// on tourne
						etat = TRANSITION_DROIT_TOURNE;

					} else {

						// on fonce
						etat = TRANSITION_DROIT_FONCE;

					}
				}

				break;

			case TRANSITION_DROIT_FONCE:

				// on avance droit
				bot.setSpeed(HI_SPEED, HI_SPEED);
				
				// Fin de la transition
				if (distanceDetecteurDroit < DISTANCE_FIN_TRANSITION) {
					etat = TRANSITION_DROIT_REDRESSE;
				}

				break;

			case TRANSITION_DROIT_REDRESSE:

				// on tourne a gauche
				bot.setSpeed(LO_SPEED, HI_SPEED);

				if (distanceDetecteurDroit < DISTANCE_OPTIMALE) {
					obstacle.clear();
					postTransition = true;
					etat = MUR_DROIT;
				}

				break;
	
		}

		//SCRUTATION

		//SECTION DETECTION MUR ET POTEAU

		// si on est en train de suivre un mur
		if (etat == MUR_GAUCHE || etat == MUR_DROIT) {

			// verifier si on doit agir par rapport au obstacles de l'autre cote
			uint8_t detectionObstacle = obstacle.analyze();

			// il s'agit d'un poteau
			if (detectionObstacle == Obstacle::POLE) {
				// faire jouer le piezo
				timer.schedule(200);
				musique = TONE1;
			}

			// il s'agit d'un mur
			if (detectionObstacle == Obstacle::WALL) {
				if (etat == MUR_GAUCHE) {
					etat = TRANSITION_DROIT_TOURNE;
				} else if (etat == MUR_DROIT) {
					etat = TRANSITION_GAUCHE_TOURNE;
				}
			}
		}

		// SECTION DETECTION BOUTON

		// si le bouton est appuye
		if ( bouton.isPressed() ) {
			if (etat == MUR_DROIT) {
				etat = ROTATION_GAUCHE;
			} else if (etat == MUR_GAUCHE) {
				etat = ROTATION_DROIT;
			}
		}

		switch (musique) {
			case OFF:
				piezo.stopPlayingNote();
				break;
			case TONE1:
				piezo.playNote(Piezo::LA_FOUR);
				if (timer.isExpired()) {
					timer.schedule(100);
					musique = PAUSE1;
				}
				break;
			case PAUSE1:
				piezo.stopPlayingNote();
				if (timer.isExpired()) {
					timer.schedule(200);
					musique = TONE2;
				}
				break;
			case TONE2:
				piezo.playNote(Piezo::LA_FOUR);
				if (timer.isExpired()) {
					timer.schedule(100);
					musique = PAUSE2;
				}
				break;
			case PAUSE2:
				piezo.stopPlayingNote();
				if (timer.isExpired()) {
					timer.schedule(200);
					musique = TONE3;
				}
				break;
			case TONE3:
				piezo.playNote(Piezo::LA_FOUR);
				if (timer.isExpired()) {
					musique = OFF;
				}
				break;

		}

		// Augmente le compteur de boucle
		compteur++;

		// Delai sur la boucle principale
		_delay_ms(40);

	}

}

//******************************************************************************
// Main
//******************************************************************************
int main(){
	loop();
}

