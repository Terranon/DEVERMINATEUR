﻿/*****************************************************************************\
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
	: bytecode() {
	uint8_t sizeH = bytecode.read(0);
	uint8_t sizeL = bytecode.read(1);
	bytecodeSize = (sizeH << 8) | sizeL;
	currentAddress = 2;
}

Interpreter::~Interpreter() {
}

void Interpreter::execute() {
	
	uint8_t instruction = 0;
	uint8_t operand = 0;
	
	while (currentAddress < bytecodeSize) {
		instruction = bytecode.read(currentAddress);
		operand = bytecode.read(currentAddress+1);
		
		executeInstruction(instruction, operand);
		
		currentAddress += 2;
	}
	
}

void Interpreter::executeInstruction(uint8_t instruction, uint8_t operand) {
	
	if (instruction == DBT) {
		begin();
	} else if (beginningFound) {
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
	
}

void Interpreter::wait(uint8_t time) {
	
}

void Interpreter::turnOnLed(uint8_t ledArray) {
	
}

void Interpreter::turnOffLed(uint8_t ledArray) {
	
}

void Interpreter::playSound(uint8_t note) {
	
}

void Interpreter::stopSound() {
	
}

void Interpreter::stopMotors() {
	
}

void Interpreter::moveForward(uint8_t speed) {
	
}

void Interpreter::moveBackward(uint8_t speed) {
	
}

void Interpreter::turnRight() {
	
}

void Interpreter::turnLeft() {
	
}

void Interpreter::beginLoop(uint8_t nIterations) {
	
}

void Interpreter::endLoop() {
	
}

void Interpreter::end() {
	
}