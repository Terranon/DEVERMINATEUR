/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Path.cpp
 * Description: 
 * Version: 1.0
\******************************************************************************/
#include "Path.h"

Path::Path() {
	lastCm_ = 0;
	lastTwoCm_ = 0;
	lastThreeCm_ = 0;
	lastFourCm_ = 0;
	lastFiveCm_ = 0;
}

bool Path::authorizationToContinue() {
	if (lastCm_ > 30 && lastTwoCm_ > 30 && lastThreeCm_ > 0 && lastFourCm_ > 0 && lastFiveCm_ > 0)
		return false;
	else
		return true;
}

void Path::setNewDistance(double newDistance) {
	lastFiveCm_ = lastFourCm_;
	lastFourCm_ = lastThreeCm_;
	lastThreeCm_ = lastTwoCm_;
	lastTwoCm_ = lastCm_;
	lastCm_ = newDistance;
}





