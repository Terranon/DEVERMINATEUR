﻿/*****************************************************************************\
 * Authors:     Jean-Raphael Matte
 * Name:        Memory.cpp
 * Description: This class can read data from an external EEPROM memory over the
 *              RS232 protocol. Currently, it is only an interface for the
 *              Memoire24CXXX class.
 *                                                                              
 * Version: 1.0
\******************************************************************************/

#include "Memory.h"

Memory::Memory()
	: eeprom_() {
}

Memory::~Memory() {
}

uint8_t Memory::read(uint16_t address) {
	uint8_t byteRead = 0;
	eeprom_.lecture(address, &byteRead);
	return byteRead;
}
