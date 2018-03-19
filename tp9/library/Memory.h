/*****************************************************************************\
 * Authors:     Jean-Raphael Matte
 * Name:        Memory.h
 * Description: This class can read data from an external EEPROM memory over the
 *              RS232 protocol. Currently, it is only an interface for the
 *              Memoire24CXXX class.
 *                                                                              
 * Version: 1.0
\******************************************************************************/

#ifndef MEMORY_H

#include "memoire_24.h"

class Memory {
public:
	
	/**
	 * \brief constructor
	 * \return a Memory object
	 */
	Memory();
	
	/**
	 * \brief destructor
	 */
	~Memory();
	
	/**
	 * \brief reads a byte of the memory
	 * \param address the address of the selected byte
	 * \return the byte at the given address
	 */
	uint8_t read(uint16_t address);
	
private:
	
	Memoire24CXXX eeprom;
	
};
