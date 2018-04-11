#ifndef QUEUE_H
#define QUEUE_H
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h> 
#define CAPACITY 9

class Queue {
public:
	Queue();
	void push(uint8_t distance);
	uint8_t get(uint8_t i) const; //envoie un index entre 0 et 8, 0 etant la plus ancienne

private:
	uint8_t data_[CAPACITY];
	uint8_t head_;				//pointe vers la prochaine case ou inserer la distance

};


#endif 
