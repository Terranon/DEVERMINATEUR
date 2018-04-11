#include "Obstacle.h"
#define NOMBRE_DIST_MAX 9


Obstacle::Obstacle() {
	Queue distances_;
	uint8_t numberOfDistances_ = 0;
}

void Obstacle::push(uint8_t distance) {
	distances_.push(distance);
	if (numberOfDistances_ < NOMBRE_DIST_MAX)
		numberOfDistances_++;
}

uint8_t Obstacle::detectionObstacle() {
	if (numberOfDistances_ < NOMBRE_DIST_MAX)
		return 0; // pas assez de donnees
	else if (distances_.get(NOMBRE_DIST_MAX - 1) == 61) {
			if (distances_.get(NOMBRE_DIST_MAX - 2) == 61) 
				return 0; // dans le vide
			else 
				return 1; // fin de poteau
	}
	else {
		uint8_t largeurPoteau = 5;
		for (uint8_t i = 0; i < largeurPoteau; i++) {
			if (distances_.get(NOMBRE_DIST_MAX - (1 + i) == 61)) {
				return 0; // a trouve le debut du poteau
			}
		}
		return 2; // trouve pas le debut du poteau
	}
}
