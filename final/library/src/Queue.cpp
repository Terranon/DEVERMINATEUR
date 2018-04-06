#include "Queue.h"

Queue::Queue() {
	uint8_t data_[CAPACITY] = 0;
	uint8_t head_ = 0;
}

void Queue::push(uint8_t distance) {
	data_[head_] = distance;
	head_++;
	if (head_ = CAPACITY)
		head_ = 0;

}

uint8_t Queue::get(uint8_t i) const {
	return data_[(i+head_) % CAPACITY];
}