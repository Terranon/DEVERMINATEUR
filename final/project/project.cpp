/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Simple test program for the library 'deverminateur'. Robot will
 *              play a note when program first begins then will move forward
 *              when the photocell senses high luminosity and backwards when it
 *              senses low luminosity. The Led will also respond to luminosity.
 * 
 * Pinout :                                      (- +) LED             Jumper  
 *                                                | |                       |
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  0 1 2 3 4 5 6 7    PORTD  1 3 5 7        
 *        0 2 4 6           0 2 4 6                                         |        
 *                                                                      0 2 4 6
 *                                                                              
 * 
 *                                                
 *                
 * 
 * Version: 1.0
\******************************************************************************/
#include "Motor.h"
#include "Sensor.h"
Motor bot;

/******************************************************************************\
 * Init
\******************************************************************************/
void init(){

}

/******************************************************************************\
 * Loop
\******************************************************************************/
void loop(){
	if(distanceDroite = 15){
		bot.setSpeed(200, 200);
	}
	else if(distanceDroite > 15){
		bot.setSpeed(200, 100);
	}
	else if(distanceDroite < 15){
		bot.setSpeed(100, 200);
	}
}

/******************************************************************************\
 * Main
\******************************************************************************/
int main(){
	init();
	while(1){
		loop();
	}
}
