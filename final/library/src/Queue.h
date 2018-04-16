/******************************************************************************\
 * Authors: William Chartrand, Jean-Raphael Matte
 * Name: Queue.h
 * Description: Random access circular buffer data structure
 * 
 * Version: 1.0
\******************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <avr/io.h>

#define QUEUE_CAPACITY 128

class Queue {
public:
	
	/**
	 * \brief constructor
	 * \return a Queue filled with 0s
	 */
	Queue();
	
	/**
	 * \brief add an element to the queue, overwriting the oldest element
	 * \param data the data to add
	 */
	void push(uint8_t data);
	
	/**
	 * \brief gives the element at index i, where 0 is the most recent element
	 * \param i index
	 * \return the element at index i
	 */
	uint8_t get(uint8_t i) const;

private:
	
	// Array to contain the data
	uint8_t data_[QUEUE_CAPACITY];
	
	// Index where the next value will be written
	uint8_t head_;

};


#endif 
