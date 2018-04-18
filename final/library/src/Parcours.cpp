/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        Parcours.cpp
 * Description: Le programme suivant impose au robot de rester a 
				une distance de 15 cm d'un mur a droite. Nous ne prenons pas en 
				consideration les poteaux et les fins de murs. Ce programme  
				utilise donc les classes Sensor et Motor. De plus, ce programme 
				permet au robot de changer de direction de maniere fluide.                                                               
 * Version: 1.3
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

		// Fixe la duree du cycle
		timer_.schedule(DELTA_T);

		updateDistance();

		runMachine();

		runMachineMusique();

		runMachineBouton();

		//SCRUTATION

		// DETECTION D'OBSTACLE

		// Si on suit un mur
		if (suitUnMur_) {

			// Si on a fait une transition et qu'il n'y a pas eu 
			// d'interruption dans l'ancien mur, on attends d'en trouver une
			if (postTransition_) {

				// Si on a trouve un trou
				if (getDistObstacle() > DISTANCE_MAXIMALE) {
					postTransition_ = false;
				}

			} else {
				// On indique au gestionnaire d'obstacle la distance observe 
				// par le capteur
				obstacle_.push(getDistObstacle());
			}

			// verifier si on doit agir par rapport aux obstacles
			uint8_t detectionObstacle = obstacle_.analyze();

			// il s'agit d'un poteau
			if (detectionObstacle == Obstacle::POLE) {
				// faire jouer le piezo
				changeStateMusique(StateMusique::TONE1);
			}

			// il s'agit d'un mur
			if (detectionObstacle == Obstacle::WALL) {
				// Fait une transition
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

		// Commence a suivre un mur
		case MUR_INIT:
			if (premiereFois_) {

				// Redemarre le gestionnaire d'obstacles
				obstacle_.clear();

				// On suit un mur
				suitUnMur_ = true;

				// Allume la DEL en vert
				led_.setColor(Led::GREEN);

				// On avance
				bot_.setDirection(Motor::FRWD, Motor::FRWD);

				premiereFois_ = false;
			}

			changeState(State::MUR_IDEAL);

			break;

		// On est precisement a la distance optimale
		case MUR_IDEAL:
			if (premiereFois_) {

				// Tout droit
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

				// On initialise la longeurAjustement_
				longeurAjustement_ = 0;
				changeState(State::MUR_AJUSTE);

			}

			break;

		case MUR_AJUSTE:
			if (premiereFois_) {

				// Si on es trop loin
				if (tropLoin_) {
					// On tourne vers le mur
					setSpeedCoteMur(0);
					setSpeedCoteOppose(HI_SPEED);
				} else {
					// On tourne pour s'eloigner du mur
					setSpeedCoteMur(HI_SPEED);
					setSpeedCoteOppose(0);
				}

				// Fixe une alarme
				setAlarm(longeurAjustement_);

				premiereFois_ = false;
			}

			// Si on trouve la distance optimale, on se replace droit
			if (getDistMur() == DISTANCE_OPTIMALE) {
				changeState(State::MUR_REAJUSTE);
			}

			// L'ajustement est fini
			if (getAlarm()) {
				changeState(State::MUR_FINDHOME);
			}

			break;

		// Essaie de retrouver la distance optimale en allant droit
		case MUR_FINDHOME:
			if (premiereFois_) {

				// tout droit
				setSpeedCoteMur(HI_SPEED);
				setSpeedCoteOppose(HI_SPEED);

				// Formule pour le nombre de cycles
				setAlarm(longeurAjustement_*4+LONGUEUR_FINDHOME);

				premiereFois_ = false;
			}

			// Si on ne voit plus le mur, il faut le retrouver
			if (getDistMur() > DISTANCE_MAXIMALE) {
				changeState(State::MUR_PERDU);
			}

			// Si on est vraiment trop pres du mur, on fait un virage serre
			if (getDistMur() <= DISTANCE_VIRAGE_SERRE) {
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

		// Se replace droit apres l'ajustement
		case MUR_REAJUSTE:
			if (premiereFois_) {

				if (tropLoin_) {
					setSpeedCoteMur(HI_SPEED);
					setSpeedCoteOppose(0);
				} else {
					setSpeedCoteMur(0);
					setSpeedCoteOppose(HI_SPEED);
				}

				// Formule pour le nombre de cycles
				setAlarm( (longeurAjustement_ * (longeurAjustement_+1))/4 );

				premiereFois_ = false;
			}

			// Le reajustement est fini
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

			// Vitesse 1/2 de HI_SPEED
			if (loopCounter_ % 2 == 0) {
				setSpeedCoteMur(HI_SPEED);
			} else {
				setSpeedCoteMur(0);
			}

			// Si on a retrouve le mur
			if (getDistMur() <= DISTANCE_MAXIMALE) {
				changeState(State::MUR_IDEAL);
			}

			break;

		// Fais un virage serre
		case MUR_VIRAGESERRE:
			if (premiereFois_) {

				compteurVirageSerre_ = 0;

				// On vire
				setSpeedCoteMur(HI_SPEED);
				setSpeedCoteOppose(0);

				premiereFois_ = false;
			}

			// Incremente le compteur
			compteurVirageSerre_++;

			// Arrete le virage lorsqu'on est a une distance raisonable
			if (getDistMur() > DISTANCE_VIRAGE_SERRE) {
				changeState(State::MUR_VIRAGEREDRESSE);
			}

			break;

		// Redresse apres un virage serre
		case MUR_VIRAGEREDRESSE:
			if (premiereFois_) {

				setSpeedCoteMur(0);
				setSpeedCoteOppose(HI_SPEED);

				setAlarm(compteurVirageSerre_/2);

				premiereFois_ = false;
			}
			if (getAlarm()) {
				changeState(State::MUR_IDEAL);
			}

			break;

		// Effectue une rotation de 180 degres puis suit le mur
		case ROTATION:

			if (premiereFois_) {

				// On ne suit pas un mur
				suitUnMur_ = false;

				// Allume la DEL en rouge
				led_.setColor(Led::RED);

				// On va suivre l'autre cote
				changeSide();

				// On tourne sur nous meme du cote de obstacles
				switch (side_) {
					case D:
						bot_.setDirection(Motor::FRWD, Motor::BACK);
						break;
					case G:
						bot_.setDirection(Motor::BACK, Motor::FRWD);
						break;
				}

				// On tourne
				bot_.setSpeed(ROTATION_SPEED, ROTATION_SPEED);

				premiereFois_ = false;
				
			}

			// On arrete de tourner lorsque la distance est bonne
			if (getDistMur() < DISTANCE_ARRET_ROTATION) {
				changeState(State::MUR_INIT);
			}

			break;

		// TRANSITION

		// Effectue une transition vers un mur
		case TRANSITION_INIT:
			if (premiereFois_) {
				
				// On ne suit pas un mur
				suitUnMur_ = false;

				// On a fait un transition
				postTransition_ = true;

				// Le compteur de rotation doit etre reinitialise
				compteurRotationTransition_ = 0;


				// On va suivre l'autre cote
				changeSide();

				// Allume la DEL en rouge
				led_.setColor(Led::RED);

				// On avance
				bot_.setDirection(Motor::FRWD, Motor::FRWD);
				
				premiereFois_ = false;
			}

			changeState(State::TRANSITION_TOURNE);

			break;

		// Tourne jusqu'a ce que le mur ne soit plus en vue
		case TRANSITION_TOURNE:
		
			if (premiereFois_) {

				// On tourne
				setSpeedCoteOppose(HI_SPEED);

				premiereFois_ = false;
			}

			// On compte pour le redressement
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
			if (getDistMur() < DISTANCE_FIN_TRANSITION) {
				changeState(State::TRANSITION_REDRESSE);
			}

			break;

		// Retrouve le debut du mur
		case TRANSITION_CORRECT:
			if (premiereFois_) {

				// On tourne
				setSpeedCoteMur(HI_SPEED);

				if (compteurRotationTransition_/4 >= DIFF_CORRECT) {
					setAlarm(compteurRotationTransition_/4 - DIFF_CORRECT);
				} else {
					setAlarm(compteurRotationTransition_/4);
				}

				premiereFois_ = false;
			}

			// Vitesse 1/4 de HI_SPEED
			if (loopCounter_ % 4 == 0) {
				setSpeedCoteOppose(HI_SPEED);
			} else {
				setSpeedCoteOppose(0);
			}

			// On compte pour le redressement
			if (compteurRotationTransition_ != 0) {
				compteurRotationTransition_--;
			}

			if (getAlarm()) {
				changeState(State::TRANSITION_VERIFY);
			}

			break;

		// Calcule la vitesse de rapprochement du mur
		case TRANSITION_VERIFY:

			if (premiereFois_) {

				// On avance droit
				bot_.setSpeed(HI_SPEED, HI_SPEED);

				// On enregistre la distance
				ancienneDistance_ = getDistMur();

				setAlarm(NB_LOOP_VERIFY);

				premiereFois_ = false;
			}

			// Si le mur est deja proche, on le suit
			if (getDistMur() < DISTANCE_FIN_TRANSITION) {
				changeState(State::TRANSITION_REDRESSE);
			}

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

		// Avance en ligne droite jusqu'a ce que le mur soit assez proche
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

		// Essaie de replacer le robot droit avec le mur
		case TRANSITION_REDRESSE:

			if (premiereFois_) {

				// on tourne
				setSpeedCoteMur(HI_SPEED);

				if (compteurRotationTransition_ >= DIFF_REDRESSE) {
					setAlarm(compteurRotationTransition_ - DIFF_REDRESSE);
				}

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

				if (suitUnMur_) {
					changeState(State::ROTATION);
				}

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
