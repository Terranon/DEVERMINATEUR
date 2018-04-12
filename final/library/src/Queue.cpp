/******************************************************************************\
 * Authors: William Chartrand, Jean-Raphael Matte
 * Name: Queue.cpp
 * Description: Random access circular buffer data structure
 * 
 * Version: 1.0
\******************************************************************************/

#include "Queue.h"

Queue::Queue()
: head_(0) {}

void Queue::push(uint8_t data) {
	
	// Overwrite the oldest data
	data_[head_] = data;
	
	// Increment the head (to the next oldest data)
	head_++;
	
	// Loop the head to the first value if it reached the end
	if (head_ == QUEUE_CAPACITY) {
		head_ = 0;
	}

}

uint8_t Queue::get(uint8_t i) const {
	// Access the data n+1 positions behind head
	// Ensures the index is within bounds
	return data_[(head_-(i+1)+QUEUE_CAPACITY) % QUEUE_CAPACITY];
}
