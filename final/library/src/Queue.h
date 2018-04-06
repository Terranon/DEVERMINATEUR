#ifndef QUEUE_H
#define QUEUE_H

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