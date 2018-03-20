/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        Interpreter.cpp
 * Description: This class is an interpreter for bytecode stored in EEPROM
 *              external memory.
 * 
 * Pinout :                                                              
 *                                                                              
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  1 3 5 7    PORTD  1 3 5 7         
 *        0 2 4 6           0 2 4 6           0 2 4 6           0 2 4 6         
 *                                                                              
 *                                                                              
 *                                                                              
 *                                                                              
 *                                                                              
 * Version: 1.0
\******************************************************************************/

#include "Interpreter.h"

Interpreter::Interpreter() 
	: bytecode_(),
	  beginningFound_(0),
	  currentAddress_(2),
	  loopBeginningAddress_(2),
	  loopCounter_(0),
	  timer_(),
	  led_(),
	  piezo_(),
	  motor_(),
	  memory_() {
	
	uint8_t sizeH = bytecode_.read(0);
	uint8_t sizeL = bytecode_.read(1);
	bytecodeSize_ = (sizeH << 8) | sizeL;

}

Interpreter::~Interpreter() {
}

void Interpreter::execute() {
	
	uint8_t instruction = 0;
	uint8_t operand = 0;
	
	while (currentAddress_ < bytecodeSize_) {
		
		instruction = bytecode_.read(currentAddress_);
		operand = bytecode_.read(currentAddress_+1);
		
		executeInstruction(instruction, operand);
		
		currentAddress_ += 2;
		
	}
	
}

void Interpreter::executeInstruction(uint8_t instruction, uint8_t operand) {
	
	if (instruction == DBT) {
		begin();
	} else if (beginningFound_ == 1) {
		switch (instruction) {
			case DBT:
				begin();
				break;
			case ATT:
				wait(operand);
				break;
			case DAL:
				turnOnLed(operand);
				break;
			case DET:
				turnOffLed(operand);
				break;
			case SGO:
				playSound(operand);
				break;
			case SAR:
				stopSound();
				break;
			case MAR: // fallthrough
			case MAR2:
				stopMotors();
				break;
			case MAV:
				moveForward(operand);
				break;
			case MRE:
				moveBackward(operand);
				break;
			case TRD:
				turnRight();
				break;
			case TRG:
				turnLeft();
				break;
			case DBC:
				beginLoop(operand);
				break;
			case FBC:
				endLoop();
				break;
			case FIN:
				end();
				break;
		}
	}
	
}

void Interpreter::begin() {
	beginningFound_ = 1;
}

void Interpreter::wait(uint8_t time) {
	timer_.schedule(((uint16_t)time)*25);
	while (!t.isExpired()) {
	}
}

void Interpreter::turnOnLed(uint8_t ledArray) {
	led_.setColor(Led::GREEN);
}

void Interpreter::turnOffLed(uint8_t ledArray) {
	led_.setColor(Led::OFF);
}

void Interpreter::playSound(uint8_t note) {
	piezo_.playNote(note);
}

void Interpreter::stopSound() {
	piezo_.stopPlayingNote();
}

void Interpreter::stopMotors() {
	motor_.stopMotors();
}

void Interpreter::moveForward(uint8_t speed) {
	motor_.goFRWD(speed);
}

void Interpreter::moveBackward(uint8_t speed) {
	motor_.goBACK(speed);
}

void Interpreter::turnRight() {
	motor_.turnRight();
}

void Interpreter::turnLeft() {
	motor_.turnLeft();
}

void Interpreter::beginLoop(uint8_t nIterations) {
	loopBeginningAddress_ = currentAddress_;
	loopCounter_ = nIterations;
}

void Interpreter::endLoop() {
	if (loopCounter_ > 0) {
		currentAddress_ = loopBeginningAddress_;
		loopCounter_--;
	}
}

void Interpreter::end() {
	currentAddress_ = bytecodeSize_;
}
