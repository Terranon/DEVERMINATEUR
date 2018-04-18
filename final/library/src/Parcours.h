/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        Parcours.h
 * Description: Le programme suivant impose au robot de rester a 
				une distance de 15 cm d'un mur a droite. Nous ne prenons pas en 
				consideration les poteaux et les fins de murs. Ce programme  
				utilise donc les classes Sensor et Motor. De plus, ce programme 
				permet au robot de changer de direction de maniere fluide.
 * Version: 1.3
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

// machine a etat pour le deplacement du robot
enum State {
	START,
	MUR_INIT,
	MUR_IDEAL,
	MUR_AJUSTE,
	MUR_FINDHOME,
	MUR_REAJUSTE,
	MUR_PERDU,
	MUR_VIRAGESERRE,
	MUR_VIRAGEREDRESSE,
	ROTATION,
	TRANSITION_INIT,
	TRANSITION_TOURNE,
	TRANSITION_CORRECT,
	TRANSITION_VERIFY,
	TRANSITION_FONCE,
	TRANSITION_REDRESSE
};

// machine a etat pour le bouton
enum StateBouton {
	PRESSED,
	RELEASED
};

// machine a etat pour la sequence de son
enum StateMusique {
	OFF,
	TONE1,
	PAUSE1,
	TONE2,
	PAUSE2,
	TONE3
};

// cote gauche / droit
enum Side {
	G,
	D
};

class Parcours {

public:

	// constructeur
	Parcours();

	// demarrage de la boucle principale
	void start();

private:

	// mise a jour des distances des deux cote
	void updateDistance();

	// change de cote
	void changeSide();

	// modifie la vitesse de la roue du cote du mur
	void setSpeedCoteMur(uint8_t vitesse);

	// modifie la vitesse de la roue du cote oppose au mur
	void setSpeedCoteOppose(uint8_t vitesse);
	
	// donne la distance du mur
	uint8_t getDistMur();

	// donne la distance des obstacles
	uint8_t getDistObstacle();

	// execute le switch de la machine a etat du parcours
	void runMachine();
	// change d'etat et met premiereFois_ a false
	void changeState(State s);
	// fixe dans combien d'iterations de la boucle getAlarm sera vrai
	// fixe alarm_ a (loopCounter_+loops)
	void setAlarm(uint8_t loops);
	// indique si loopCounter_ est plus grand que alarm_
	bool getAlarm();

	// execute le switch de la machine a etat du bouton
	void runMachineBouton();
	// change d'etat et met premiereFoisBouton_ a false
	void changeStateBouton(StateBouton s);
	// fixe dans combien d'iterations de la boucle getAlarmBouton sera vrai
	// fixe alarmBouton_ a (loopCounter_+loops)
	void setAlarmBouton(uint8_t loops);
	// indique si loopCounter_ est plus grand que alarmBouton_
	bool getAlarmBouton();

	// execute le switch de la machine a etat de la musique
	void runMachineMusique();
	// change d'etat et met premiereFoisMusique_ a false
	void changeStateMusique(StateMusique s);
	// fixe dans combien d'iterations de la boucle getAlarmMusique sera vrai
	// fixe alarmMusique_ a (loopCounter_+loops)
	void setAlarmMusique(uint8_t loops);
	// indique si loopCounter_ est plus grand que alarmMusique_
	bool getAlarmMusique();

	// Distance cible
	const uint8_t DISTANCE_OPTIMALE = 15;
	// Distance a laquelle il faut faire un virage serre
	const uint8_t DISTANCE_VIRAGE_SERRE = 11;
	// Distance a laquelle on peut commencer a suivre le mur
	const uint8_t DISTANCE_FIN_TRANSITION = 20;
	// Distance a laquelle on a termine de tourner 180 degrees
	const uint8_t DISTANCE_ARRET_ROTATION = 18;
	// Distance maximale que l'on doit detecter
	const uint8_t DISTANCE_MAXIMALE = 60;

	// Nombre de cycles minimal lorsque le robot est en mode MUR_FINDHOME
	const uint8_t LONGUEUR_FINDHOME = 2;
	
	// Ajustement lors de TRANSITION_CORRECT
	const uint8_t DIFF_CORRECT = 3;
	// Ajustement lors de TRANSITION_REDRESSE
	const uint8_t DIFF_REDRESSE = 3;

	// Nombre de cycles avant de confirmer la detection d'un mur
	const uint8_t LARGEUR_MIN_MUR = 20;

	// Distance que le robot doit se rapprocher lors de TRANSITION_VERIFY
	const uint8_t DELTA_D_OPTIMAL = 1;

	// Nombre de cycles pour TRANSITION_VERIFY
	const uint8_t NB_LOOP_VERIFY = 20;

	// Vitesse des moteurs pour le fonctionnement general du robot
	const uint8_t HI_SPEED = 150;

	// Vitesse des moteurs lors de ROTATION
	const uint8_t ROTATION_SPEED = 130;

	// Duree d'un cycle, en ms
	const uint8_t DELTA_T = 50;

	// Nombre de cycles lors de MUR_AJUSTE
	uint8_t longeurAjustement_;

	// Indique si on est apres une transition
	bool postTransition_;

	// Compteur pour le nombre de cycles que l'on doit faire MUR_VIRAGEREDRESSE
	uint8_t compteurVirageSerre_;

	// Compteur pour le nombre de cycles que l'on doit faire TRANSITION_REDRESSE
	uint8_t compteurRotationTransition_;

	// Distance precedente, pour le calcul de deltaD_ lors de TRANSITION_VERIFY
	uint8_t ancienneDistance_;

	// Variation de distance, lors de TRANSITION_VERIFY
	uint8_t deltaD_;
	
	// Distance du capteur droit
	uint8_t distD_;

	// Distance du capteur gauche
	uint8_t distG_;

	// Compteur de cycles
	uint16_t loopCounter_;

	// Indique si le robot suit un mur
	bool suitUnMur_;

	// Cote que le robot utilise pour se diriger
	Side side_;

	// Indique si le robot est trop loin du mur lorsqu'il le suit
	bool tropLoin_;

	// Etat pour le parcours
	State etat_;
	// Indique si c'est la premiere fois qu'on execute un etat
	bool premiereFois_;
	// Garde en memoire un nombre de cycles futur
	uint16_t alarm_;

	// Etat pour le bouton
	StateBouton etatBouton_;
	// Indique si c'est la premiere fois qu'on execute un etat
	bool premiereFoisBouton_;
	// Garde en memoire un nombre de cycles futur
	uint16_t alarmBouton_;

	// Etat pour la musique
	StateMusique etatMusique_;
	// Indique si c'est la premiere fois qu'on execute un etat
	bool premiereFoisMusique_;
	// Garde en memoire un nombre de cycles futur
	uint16_t alarmMusique_;
	
	// Instances de classes utilitaires
	Motor bot_;
	Button bouton_;
	Sensor sensor_;
	Led led_;
	Obstacle obstacle_;
	Piezo piezo_;
	Timer timer_;

};

#endif