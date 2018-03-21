/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        Interpreter.h
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

#ifndef INTERPRETER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Led.h"
#include "Piezo.h"
#include "Timer.h"
#include "Motor.h"
#include "Memory.h"

class Interpreter {
public:
	
	/**
	 * \brief constructor
	 * \return an Interpreter object
	 */
	Interpreter();
	
	/**
	 * \brief destructor
	 */
	~Interpreter();
	
	/**
	 * \brief execute the program in memory
	 */
	void execute();
	
private:
	
	/**
	 * \brief executes a single instruction
	 * \param instruction the instruction to be executed
	 * \param operand the operand to the instruction. Will be ignored if the 
	 *                instruction takes no operand.
	 */
	void executeInstruction(uint8_t instruction, uint8_t operand);
	
	/**
	 * \instruction Debut
	 * \mnemonic dbt
	 * \bytecode 0x01
	 * \brief start executing the bytecode
	 */
	void begin();
	
	/**
	 * \instruction Attendre
	 * \mnemonic att
	 * \bytecode 0x02
	 * \brief Wait for a specified amount of time
	 * \param time amount of time, given in multiples of 25ms (1/40 second)
	 */
	void wait(uint8_t time);
	
	/**
	 * \instruction Allumer la DEL
	 * \mnemonic dal
	 * \bytecode 0x44
	 * \brief Light up the specified LEDs
	 * \param ledArray an array of bits, where a bit set to 1 lights up the
	 *        corresponding LED
	 */
	void turnOnLed(uint8_t ledArray);
	
	/**
	 * \instruction Eteindre les DEL
	 * \mnemonic det
	 * \bytecode 0x45
	 * \brief Turns off the specified LEDs
	 * \param ledArray an array of bits, where a bit set to 1 lights up the
	 *        corresponding LED 
	 */
	void turnOffLed(uint8_t ledArray);
	
	/**
	 * \instruction Jouer une sonorite
	 * \mnemonic sgo
	 * \bytecode 0x48
	 * \brief start playing a note
	 * \param note MIDI note number, where 69 is A4 (440hz).
	 *        Must be between 45-81, inclusively. Notes outside of these bounds
	 *        will not be played.
	 */
	void playSound(uint8_t note);
	
	/**
	 * \instruction Arreter de jouer la sonorite
	 * \mnemonic sar
	 * \bytecode 0x09
	 * \brief stop playing a note
	 */
	void stopSound();
	
	/**
	 * \instruction Arreter les moteurs
	 * \mnemonic mar
	 * \bytecode 0x60 or 0x61
	 * \brief stop moving
	 */
	void stopMotors();
	
	/**
	 * \instruction Avancer
	 * \mnemonic mav
	 * \bytecode 0x62
	 * \brief move forward at a specified speed
	 * \param speed value where 0 is the slowest speed (stopped) and 255 is the
	 * 				fastest speed
	 */
	void moveForward(uint8_t speed);
	
	/**
	 * \instruction Reculer
	 * \mnemonic mre
	 * \bytecode 0x63
	 * \brief move backward at a specified speed
	 * \param speed value where 0 is the slowest speed (stopped) and 255 is the
	 * 				fastest speed
	 */
	void moveBackward(uint8_t speed);
	
	/**
	 * \instruction Tourner a droite
	 * \mnemonic trd
	 * \bytecode 0x64
	 * \brief make a 90 degree turn to the right
	 */
	void turnRight();
	
	/**
	 * \instruction Tourner a gauche
	 * \mnemonic trg
	 * \bytecode 0x65
	 * \brief make a 90 degree turn to the left
	 */
	void turnLeft();
	
	/**
	 * \instruction Debut de boucle
	 * \mnemonic dbc
	 * \bytecode 0xC0
	 * \brief save the address of the beginning of the loop and set the loop
	 *        counter to nIterations
	 * \param nIterations number of times the loop will re-execute. As such, the
	 *        code inside the loop will be executed nIterations+1 times.
	 */
	void beginLoop(uint8_t nIterations);
	
	/**
	 * \instruction Fin de boucle
	 * \mnemonic fbc
	 * \bytecode 0xC1
	 * \brief if the loop counter is not 0, decrement and jump to the 
	 *        beginning of the loop
	 */
	void endLoop();
	
	/**
	 * \instruction Fin
	 * \mnemonic fin
	 * \bytecode 0xFF
	 * \brief stop the execution of the bytecode
	 */
	void end();
	
	// Mnemonics for instruction binary values
	static const uint8_t DBT = 0x01;
	static const uint8_t ATT = 0x02;
	static const uint8_t DAL = 0x44;
	static const uint8_t DET = 0x45;
	static const uint8_t SGO = 0x48;
	static const uint8_t SAR = 0x09;
	static const uint8_t MAR = 0x60;
	static const uint8_t MAR2 = 0x61;
	static const uint8_t MAV = 0x62;
	static const uint8_t MRE = 0x63;
	static const uint8_t TRD = 0x64;
	static const uint8_t TRG = 0x65;
	static const uint8_t DBC = 0xC0;
	static const uint8_t FBC = 0xC1;
	static const uint8_t FIN = 0xFF;
	
	// The object through which the bytecode is obtained
	Memory bytecode_;
	
	// Size of the program, including the 16 bit used to store the size
	uint16_t bytecodeSize_;
	
	// Boolean value, indicates if the dbt instruction has been found.
	uint8_t beginningFound_;
	
	// Keeps track of the current address
	uint16_t currentAddress_;
	
	// Keeps track of the address of the beginning of the loop
	uint16_t loopBeginningAddress_;
	
	// Counts down, keeps track of how many times the loop has been executed
	uint8_t loopCounter_;
	
	Timer timer_;
	Led led_;
	Piezo piezo_;
	Motor motor_;
	Memory memory_;
};

#endif
