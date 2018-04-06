#include "Obstacle.h"

Obstacle::Obstacle() {
	Queue distances_();
}

void Queue::push(uint8_t distance) {
	distances_.push(distance);
	if (numberOfDistances_ < 9)
		numberOfDistances_++;
}

uint8_t Queue::detectionObstacle() {
	if (numberOfDistances_ < 9) {
		return 0; // pas assez de donnees
	} else if (distances_.get(9 - 1) == 61) {
		if (distances_.get(9 - 2) == 61) {
			return 0; // dans le vide
		} else {
			return 1; // fin de poteau
		}
	} else {
		uint8_t largeurPoeau = 5;
		for (uint8_t i = 0; i < largeurPoteau; i++) {
			if (distances_.get(9 - (1 + i) == 61) {
				return 0; // a trouve le debut du poteau
			}
		}
		return 2; // trouve pas le debut du poteau
	}
			
}