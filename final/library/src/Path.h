/*****************************************************************************\
 * Author:      William Chartrand
 * Name:        Path.h
 * Description: 
 * Version: 1.0
\******************************************************************************/

#ifndef PATH_H
#define PATH_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h> 

class Path {
public:
	//constructeur par defaut qui initialise les 5 derniers cm parcourus a 0
	Path();
	bool authorizationToContinue();
	void setNewDistance(double newDistance);

private:
	//pourrait aussi etre un vecteur
	double lastCm_;
	double lastTwoCm_;
	double lastThreeCm_;
	double lastFourCm_;
	double lastFiveCm_;
};
#endif 
