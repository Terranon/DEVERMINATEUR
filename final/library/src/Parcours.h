/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        Parcours.h
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

#ifndef PARCOURS_H
#define PARCOURS_H

#include <util/delay.h>

#include "Motor.h"
#include "Sensor.h"
#include "Button.h"
#include "Obstacle.h"
#include "Led.h"
#include "Piezo.h"
#include "Timer.h"

enum State {
	START,
	MUR,
	ROTATION,
	TRANSITION_TOURNE,
	TRANSITION_CORRECT,
	TRANSITION_COLLECT,
	TRANSITION_FONCE,
	TRANSITION_REDRESSE,
};

enum StateBouton {
	PRESSED,
	RELEASED
};

enum StateMusique {
	OFF,
	TONE1,
	PAUSE1,
	TONE2,
	PAUSE2,
	TONE3
};

enum Side {
	G,
	D
};

class Parcours {

public:

	Parcours();

	void start();

private:

	void updateDistance();

	void changeSide();

	void setSpeedCoteMur(uint8_t vitesse);
	void setSpeedCoteOppose(uint8_t vitesse);

	uint8_t getDistMur();
	uint8_t getDistObstacle();

	void runMachine();
	void changeState(State s);
	void setAlarm(uint8_t loops);
	bool getAlarm();

	void runMachineBouton();
	void changeStateBouton(StateBouton s);
	void setAlarmBouton(uint8_t loops);
	bool getAlarmBouton();

	void runMachineMusique();
	void changeStateMusique(StateMusique s);
	void setAlarmMusique(uint8_t loops);
	bool getAlarmMusique();

	const uint8_t DISTANCE_OPTIMALE = 15;
	const uint8_t DISTANCE_FIN_TRANSITION = 20;
	const uint8_t DISTANCE_ARRET_ROTATION = 17;
	const uint8_t DISTANCE_MAXIMALE = 60;

	const uint8_t DELTA_D_OPTIMAL = 1;
	const uint8_t NB_LOOP_COLLECT = 20;

	const uint8_t LO_SPEED = 110;
	const uint8_t HI_SPEED = 150;

	const uint8_t DELTA_T = 50;

	uint8_t detectionObstacle_;

	bool postTransition_;

	uint8_t ancienneDistance_;
	uint8_t deltaD_;
	
	uint8_t distD_;
	uint8_t distG_;

	uint16_t loopCounter_;

	Side side_;

	State etat_;
	bool premiereFois_;
	uint16_t alarm_;

	StateBouton etatBouton_;
	bool premiereFoisBouton_;
	uint16_t alarmBouton_;

	StateMusique etatMusique_;
	bool premiereFoisMusique_;
	uint16_t alarmMusique_;

	Motor bot_;
	Button bouton_;
	Sensor sensor_;
	Led led_;
	Obstacle obstacle_;
	Piezo piezo_;
	Timer timer_;

};

#endif
/*
switch (side_) {
	case D:
		
		break;
	case G:

		break;
}
*/