﻿/*****************************************************************************\
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

/******************************************************************************\
 * Main
\******************************************************************************/

#include <memoire_24.h>

void init() {

	UCSR0A = 0x02;
	UCSR0B = 0x18;
	UCSR0C = 0x06;

	UBRR0H = 0b1001;
	UBRR0L = 0b01100000;
}

uint8_t readUSB() {

	while (!(UCSR0A & (1 << RXC)));
	return UDR0;
}

/**
 * \brief main function
 * \return exit code
 */
int main () {
	
	Memoire24CXXX mem;

	const uint16_t nbInstructions = 78;
	
	for (uint16_t i = 0; i < nbInstructions; i++) {

		uint8_t data = readUSB();
		mem.ecriture(i,&data,1);
	}
	
    return 0;
}
