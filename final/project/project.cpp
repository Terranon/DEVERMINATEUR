/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Le programme suivant impose au robot de rester a 
				une distance de 15 cm d'un mur a droite. Nous ne prenons pas en 
				consideration les poteaux et les fins de murs. Ce programme  
				utilise donc les classes Sensor et Motor.

				De plus, ce programme permet au robot de changer de direction de maniere
				fluide.
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

Motor bot;
Sensor sensor;

/******************************************************************************\
 * Init
	Initialisation 
\******************************************************************************/
void init(){
	DDRA = 0x00; //port entree
}


/******************************************************************************\
 * Loop
	Boucle infini imposant au robot de rester a une distance de 15 cm du mur
\******************************************************************************/
void loop(){
	uint8_t valeur = sensor.getValeurVoltage();
	if(distanceDroite < 169)
		bot.setSpeed(200, 100);
	else 
		bot.setSpeed(100, 200);
}

/******************************************************************************\
 * Main
\******************************************************************************/
int main(){
	init();
	testeLeCapteur();
	while(1){
		loop();
	}
}
