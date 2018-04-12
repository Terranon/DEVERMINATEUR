/******************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Led.h
 * Description: Simplify the use of an LED
 * 
 *  2  4  6  8
 *   1 |3  5  7
 *     ||   PORTC
 *     ||
 *     ||
 * LED +- 
 *
 * Version: 1.3
\******************************************************************************/

#include "Led.h"

Led::Led():
color_(OFF) {
	
	// sets PORTC2 to output
	DDRC |= (1 << DDC2);
	
	// sets PORTC3 to output
	DDRC |= (1 << DDC3);
	
}

Led::~Led() {
}

void Led::setColor(uint8_t color) {
	
	color_ = color;
	switch (color_) {
		case OFF:
			PORTC &= ~(1 << DDC2);
			PORTC &= ~(1 << DDC3);
			break;
		case GREEN:
			PORTC |= (1 << DDC2);
			PORTC &= ~(1 << DDC3);
			break;
		case RED:
			PORTC &= ~(1 << DDC2);
			PORTC |= (1 << DDC3);
			break;
	}
	
}

void Led::toggleColor() {
	
	if (color_ == RED) {
		setColor(GREEN);
	} else if (color_ == GREEN) {
		setColor(RED);
	}
	    
}
