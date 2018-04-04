/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
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
	DDRC = 0xff;
}


/******************************************************************************\
 * Loop
	Boucle infini imposant au robot de rester a une distance de 15 cm du mur droit
\******************************************************************************/
void loop(){
	uint8_t valeur = sensor.getValeurVoltage();
	if(valeur > 169){
		bot.setSpeed(220, 150);
		PORTC = 0x01;
	}
	else { 
		bot.setSpeed(150, 220);
		PORTC = 0x02;
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
