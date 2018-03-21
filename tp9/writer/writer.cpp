/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        writer.cpp
 * Description:	Program that writes a set of instructions to the EEPROM 
 *             	Receives data through the RS-232 protocol 
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
	
	UCSR0A = 0x00;		//Multi-processor Communication Mode
	UCSR0B = 0x18;		//Receiver Enable, Transmitter Enable
	UCSR0C = 0x06;		//Asynchronous USART, none Parity, stop bit(s) 1-bit
										//character size -- 8 bit 
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

