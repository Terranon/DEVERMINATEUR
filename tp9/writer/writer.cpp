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

/******************************************************************************\
 * Main
\******************************************************************************/

#include <avr/io.h>
#include <memoire_24.h>

void init() {
	
	DDRD &= ~(1 << DDD0);
	DDRD |= (1 << DDD1);
	
	UCSR0A = 0x00;	
	UCSR0B = 0x18;
	UCSR0C = 0x06;

	UBRR0H = 0;
	UBRR0L = 0xCF;
}

uint8_t readUSB() {

	while (!(UCSR0A & (1 << RXC0))) {
	}
	return UDR0;
}

/**
 * \brief main function
 * \return exit code
 */
int main () {
	
	DDRA = 0xFF;
	init();
	
	Memoire24CXXX mem;

	const uint16_t nbInstructions = 78;
	
	for (uint16_t i = 0; i < nbInstructions; i++) {

		uint8_t data = readUSB();
		PORTA = i;
		mem.ecriture(i, &data, 1);
		
	}
	PORTA = 0b01010101;
	
    return 0;
}

