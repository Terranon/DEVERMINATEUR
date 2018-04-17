/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        Parcours.cpp
 * Description: Le programme suivant impose au robot de rester a 
				une distance de 15 cm d'un mur a droite. Nous ne prenons pas en 
				consideration les poteaux et les fins de murs. Ce programme  
				utilise donc les classes Sensor et Motor. De plus, ce programme 
				permet au robot de changer de direction de maniere fluide.                                                               
 * Version: 1.0
\******************************************************************************/

#include "Parcours.h"

Parcours::Parcours():
postTransition_(false),
etat_(START),
etatBouton_(RELEASED),
etatMusique_(OFF),
obstacle_(LARGEUR_MIN_MUR) {
}

void Parcours::start() {

	// Boucle principale
	while(1) {

		timer_.schedule(50);

		updateDistance();

		runMachine();

		runMachineMusique();

		runMachineBouton();

		//SCRUTATION

		// DETECTION D'OBSTACLE

		// Si on suit un mur
		if (suitUnMur_) {

			// Si on a fait une transition et qu'il n'y a pas eu 
			// d'interruption dans l'ancien mur, on attends de trouver un 
			// trou
			if (postTransition_) {

				if (getDistObstacle() > DISTANCE_MAXIMALE) {
					postTransition_ = false;
				}

			} else {

				//On push la distance observe par le capteur oppose
				obstacle_.push(getDistObstacle());

			}

			// verifier si on doit agir par rapport aux obstacles de l'autre 
			// cote
			detectionObstacle_ = obstacle_.analyze();

			// il s'agit d'un poteau
			if (detectionObstacle_ == Obstacle::POLE) {
				// faire jouer le piezo
				changeStateMusique(StateMusique::TONE1);
			}

			// il s'agit d'un mur
			if (detectionObstacle_ == Obstacle::WALL) {
				changeSide();
				changeState(State::TRANSITION_INIT);
			}
		}

		// Augmente le compteur de boucle
		loopCounter_++;

		// Delai sur la boucle principale
		while (!timer_.isExpired()) {
		}

	}
	
}

void Parcours::updateDistance() {
	distD_ = sensor_.getDistanceR();
	distG_ = sensor_.getDistanceL();
}

void Parcours::changeSide() {
	switch (side_) {
		case D:
			side_ = G;
			break;
		case G:
			side_ = D;
			break;
	}
}

void Parcours::setSpeedCoteMur(uint8_t vitesse) {
	switch (side_) {
		case D:
			bot_.setSpeedRM(vitesse);
			break;
		case G:
			bot_.setSpeedLM(vitesse);
			break;
	}
}

void Parcours::setSpeedCoteOppose(uint8_t vitesse) {
	switch (side_) {
		case D:
			bot_.setSpeedLM(vitesse);
			break;
		case G:
			bot_.setSpeedRM(vitesse);
			break;
	}
}

uint8_t Parcours::getDistMur() {
	switch (side_) {
		case D:
			return distD_;
			break;
		case G:
			return distG_;
			break;
		default:
			return 0;
	}
}

uint8_t Parcours::getDistObstacle() {
	switch (side_) {
		case D:
			return distG_;
			break;
		case G:
			return distD_;
			break;
		default:
			return 0;	
	}
}

void Parcours::runMachine() {

	switch (etat_) {

		// detecte le mur le plus pres et va commencer a le suivre
		case START:

			if (distD_ < distG_) {
				side_ = D;
			} else {
				side_ = G;
			}

			changeState(State::MUR_INIT);

			break;

		case MUR_INIT:
			if (premiereFois_) {

				obstacle_.clear();

				suitUnMur_ = true;

				switch (side_) {
					case D:
						// allume rouge si un mur a droite
						led_.setColor(Led::RED);
						break;
					case G:
						// allume vert si un mur a gauche
						led_.setColor(Led::GREEN);
						break;
				}

				// on avance
				bot_.setDirection(Motor::FRWD, Motor::FRWD);

				premiereFois_ = false;
			}

			changeState(State::MUR_IDEAL);

			break;

		case MUR_IDEAL:
			if (premiereFois_) {

				// tout droit
				setSpeedCoteMur(HI_SPEED);
				setSpeedCoteOppose(HI_SPEED);

				premiereFois_ = false;
			}
			
			// si on sort de la distance optimale
			if (getDistMur() != DISTANCE_OPTIMALE) {

				// si on est trop proche
				if (getDistMur() < DISTANCE_OPTIMALE) {
					tropLoin_ = false;
				} else {
					tropLoin_ = true;
				}

				longeurAjustement_ = 0;
				changeState(State::MUR_AJUSTE);

			}

			break;

		case MUR_AJUSTE:
			if (premiereFois_) {
				if (tropLoin_) {
					setSpeedCoteMur(0);
					setSpeedCoteOppose(HI_SPEED);
				} else {
					setSpeedCoteMur(HI_SPEED);
					setSpeedCoteOppose(0);
				}

				setAlarm(longeurAjustement_);

				premiereFois_ = false;
			}

			// Si on trouve la distance optimale, on se replace droit
			if (getDistMur() == DISTANCE_OPTIMALE) {
				changeState(State::MUR_REAJUSTE);
			}

			// Essaie de retrouver la distance optimale apres l'ajustement
			if (getAlarm()) {
				changeState(State::MUR_FINDHOME);
			}

			break;

		// avance tout droit en esperant rencontrer la distance ideale
		case MUR_FINDHOME:
			if (premiereFois_) {

				// tout droit
				setSpeedCoteMur(HI_SPEED);
				setSpeedCoteOppose(HI_SPEED);

				setAlarm(longeurAjustement_*4+LONGUEUR_FINDHOME);

				premiereFois_ = false;
			}

			// Si on ne voit plus le mur, il faut le retrouver
			if (getDistMur() > DISTANCE_MAXIMALE) {
				changeState(State::MUR_PERDU);
			}

			// Si on est vraiment trop pres du mur, on fait un virage serre
			if (getDistMur() < DISTANCE_OPTIMALE-3) {
				changeState(State::MUR_VIRAGESERRE);
			}

			// Si on trouve la disance optimale, on se replace droit
			if (getDistMur() == DISTANCE_OPTIMALE) {
				changeState(State::MUR_REAJUSTE);
			}

			// si on ne la retrouve pas, on refait un plus gros ajusement
			if (getAlarm()) {
				longeurAjustement_++;
				changeState(State::MUR_AJUSTE);
			}

			break;

		// se replace droit apres l'ajustement
		case MUR_REAJUSTE:
			if (premiereFois_) {

				if (tropLoin_) {
					setSpeedCoteMur(HI_SPEED);
					setSpeedCoteOppose(0);
				} else {
					setSpeedCoteMur(0);
					setSpeedCoteOppose(HI_SPEED);
				}

				setAlarm( (longeurAjustement_ * (longeurAjustement_+1))/4 );

				premiereFois_ = false;
			}

			if (getAlarm()) {
				changeState(State::MUR_IDEAL);
			}

			break;

		// On retrouve un mur perdu
		case MUR_PERDU:
			if (premiereFois_) {

				// on cherche le mur
				setSpeedCoteOppose(HI_SPEED);

				premiereFois_ = false;
			}

			// Vitesse 1/3 de HI_SPEED
			if (loopCounter_ % 3 == 0) {
				setSpeedCoteMur(HI_SPEED);
			} else {
				setSpeedCoteMur(0);
			}

			// si on a retrouve le mur
			if (getDistMur() <= DISTANCE_MAXIMALE) {
				changeState(State::MUR_IDEAL);
			}

			break;

		case MUR_VIRAGESERRE:
			if (premiereFois_) {

				// on vire
				setSpeedCoteMur(HI_SPEED);
				setSpeedCoteOppose(0);

				premiereFois_ = false;
			}

			if (getDistMur() >= DISTANCE_OPTIMALE) {
				changeState(State::MUR_IDEAL);
			}

			break;

		// effectue une rotation de 180 degres puis suit le mur
		case ROTATION:

			if (premiereFois_) {

				suitUnMur_ = false;

				// on eteint la led
				led_.setColor(Led::OFF);

				// on change de cote
				changeSide();

				// on tourne sur nous meme du cote oppose
				switch (side_) {
					case D:
						bot_.setDirection(Motor::FRWD, Motor::BACK);
						break;
					case G:
						bot_.setDirection(Motor::BACK, Motor::FRWD);
						break;
				}

				// on tourne
				bot_.setSpeed(ROTATION_SPEED, ROTATION_SPEED);

				premiereFois_ = false;
				
			}

			// on arrete de tourner lorsque la distance est bonne
			if (getDistMur() < DISTANCE_ARRET_ROTATION) {
				changeState(State::MUR_INIT);
			}

			break;

		// TRANSITION

		// effectue une transition vers un mur
		case TRANSITION_INIT:
			if (premiereFois_) {

				suitUnMur_ = false;
				postTransition_ = true;

				compteurRotationTransition_ = 0;

				// on eteint la led
				led_.setColor(Led::OFF);

				// on avance
				bot_.setDirection(Motor::FRWD, Motor::FRWD);
				
				premiereFois_ = false;
			}

			changeState(State::TRANSITION_TOURNE);

			break;

		// tourne jusqu'a ce que le mur ne soit plus en vue
		case TRANSITION_TOURNE:
		
			if (premiereFois_) {

				// on tourne
				setSpeedCoteOppose(HI_SPEED);

				premiereFois_ = false;
			}

			// on compte pour le redressement
			compteurRotationTransition_++;

			// Vitesse 1/4 de HI_SPEED
			if (loopCounter_ % 4 == 0) {
				setSpeedCoteMur(HI_SPEED);
			} else {
				setSpeedCoteMur(0);
			}

			// Si on trouve le debut du mur (en tournant)
			if (getDistMur() > DISTANCE_MAXIMALE + 5) {
				// on corrige l'erreur d'inertie
				changeState(State::TRANSITION_CORRECT);
			}
			
			// Si le mur est deja proche, on le suit
			if (getDistMur() < DISTANCE_OPTIMALE + 2) {
				changeState(State::MUR_INIT);
			}

			break;

		// retrouve le debut du mur
		case TRANSITION_CORRECT:
			if (premiereFois_) {

				// on tourne
				setSpeedCoteMur(HI_SPEED);

				setAlarm(compteurRotationTransition_/4);

				premiereFois_ = false;
			}

			// Vitesse 1/4 de HI_SPEED
			if (loopCounter_ % 4 == 0) {
				setSpeedCoteOppose(HI_SPEED);
			} else {
				setSpeedCoteOppose(0);
			}

			// on compte pour le redressement
			compteurRotationTransition_--;

			if (getAlarm()) {
				changeState(State::TRANSITION_COLLECT);
			}

			break;

		// calcule
		case TRANSITION_COLLECT:

			if (premiereFois_) {

				// on avance droit
				bot_.setSpeed(HI_SPEED, HI_SPEED);

				// on enregistre la distance
				ancienneDistance_ = getDistMur();

				setAlarm(NB_LOOP_COLLECT);

				premiereFois_ = false;
			}

			// Si le mur est deja proche, on le suit
			if (getDistMur() < DISTANCE_FIN_TRANSITION) {
				changeState(State::TRANSITION_REDRESSE);
			}

			// on attend un certain nombre d'execution de la boucle
			if (getAlarm()) {

				// on calcule deltaD
				deltaD_ = ancienneDistance_ - getDistMur();

				// si deltaD n'est pas assez grand
				if (deltaD_ < DELTA_D_OPTIMAL) {

					// on tourne
					changeState(State::TRANSITION_TOURNE);

				} else {

					// on fonce
					changeState(State::TRANSITION_FONCE);

				}

			}

			break;

		case TRANSITION_FONCE:

			if (premiereFois_) {

				// on avance droit
				setSpeedCoteMur(HI_SPEED);
				setSpeedCoteOppose(HI_SPEED);

				premiereFois_ = false;
			}
			
			// Si le mur est assez proche, on le suit
			if (getDistMur() < DISTANCE_FIN_TRANSITION) {
				changeState(State::TRANSITION_REDRESSE);
			}

			break;

		case TRANSITION_REDRESSE:

			if (premiereFois_) {

				// on tourne
				setSpeedCoteMur(HI_SPEED);

				setAlarm(compteurRotationTransition_-3);

				premiereFois_ = false;
			}

			// Vitesse 1/4 de HI_SPEED
			if (loopCounter_ % 4 == 0) {
				setSpeedCoteOppose(HI_SPEED);
			} else {
				setSpeedCoteOppose(0);
			}

			if (getAlarm()) {
				changeState(State::MUR_INIT);
			}

			break;

	}

}

void Parcours::changeState(State s) {
	premiereFois_ = true;
	etat_ = s;
}

void Parcours::setAlarm(uint8_t loops) {
	alarm_ = loopCounter_ + loops;
}

bool Parcours::getAlarm() {
	return loopCounter_ >= alarm_;
}

void Parcours::runMachineBouton() {
	switch (etatBouton_) {
		case PRESSED:
			if (premiereFoisBouton_) {
				changeState(State::ROTATION);
				premiereFoisBouton_ = false;
			}
			if ( !bouton_.isPressed() ) {
				changeStateBouton(StateBouton::RELEASED);
			}
			break;
		case RELEASED:
			if (premiereFoisBouton_) {
				
				premiereFoisBouton_ = false;
			}
			if ( bouton_.isPressed() ) {
				changeStateBouton(StateBouton::PRESSED);
			}
			break;
	}
}

void Parcours::changeStateBouton(StateBouton s) {
	premiereFoisBouton_ = true;
	etatBouton_ = s;
}

void Parcours::setAlarmBouton(uint8_t loops) {
	alarmBouton_ = loopCounter_ + loops;
}

bool Parcours::getAlarmBouton() {
	return loopCounter_ >= alarmBouton_;
}

void Parcours::runMachineMusique() {

	switch (etatMusique_) {

		case OFF:

			if (premiereFoisMusique_) {
				piezo_.stopPlayingNote();
				premiereFoisMusique_ = false;
			}

			break;

		case TONE1:

			if (premiereFoisMusique_) {
				piezo_.playNote(Piezo::LA_FOUR);
				setAlarmMusique(4);
				premiereFoisMusique_ = false;
			}

			if (getAlarmMusique()) {
				changeStateMusique(StateMusique::PAUSE1);
			}
			break;

		case PAUSE1:

			if (premiereFoisMusique_) {
				piezo_.stopPlayingNote();
				setAlarmMusique(2);
				premiereFoisMusique_ = false;
			}

			if (getAlarmMusique()) {
				changeStateMusique(StateMusique::TONE2);
			}

			break;

		case TONE2:

			if (premiereFoisMusique_) {
				piezo_.playNote(Piezo::LA_FOUR);
				setAlarmMusique(4);
				premiereFoisMusique_ = false;
			}

			if (getAlarmMusique()) {
				changeStateMusique(StateMusique::PAUSE2);
			}

			break;

		case PAUSE2:

			if (premiereFoisMusique_) {
				piezo_.stopPlayingNote();
				setAlarmMusique(2);
				premiereFoisMusique_ = false;
			}

			if (getAlarmMusique()) {
				changeStateMusique(StateMusique::TONE3);
			}

			break;

		case TONE3:

			if (premiereFoisMusique_) {
				piezo_.playNote(Piezo::LA_FOUR);
				setAlarmMusique(4);
				premiereFoisMusique_ = false;
			}

			if (getAlarmMusique()) {
				changeStateMusique(StateMusique::OFF);
			}

			break;

	}

}

void Parcours::changeStateMusique(StateMusique s) {
	premiereFoisMusique_ = true;
	etatMusique_ = s;
}

void Parcours::setAlarmMusique(uint8_t loops) {
	alarmMusique_ = loopCounter_ + loops;
}

bool Parcours::getAlarmMusique() {
	return loopCounter_ >= alarmMusique_;
}
