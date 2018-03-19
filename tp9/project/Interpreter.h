/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        interpreter.h
 * Description: Functions that will be used to implement bytecode instructions
 *              read from the external EEPROM
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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <Led.h>
#include <memoire_24.h>
#include <Piezo.h>
#include <Timer.h>
#include <Motor.h>

class Interpreter {
public:
	
	/**
	 * \instruction Debut
	 * \mnemonic dbt
	 * \bytecode 0x01
	 * \brief 
	 */
	void begin();
	
	/**
	 * \instruction Attendre
	 * \mnemonic att
	 * \bytecode 0x02
	 * \brief 
	 * \param time 
	 */
	void wait(uint8_t time);
	
	/**
	 * \instruction Allumer la DEL
	 * \mnemonic dal
	 * \bytecode 0x44
	 * \brief 
	 * \param ledArray 
	 */
	void turnOnLed(uint8_t ledArray);
	
	/**
	 * \instruction Eteindre les DEL
	 * \mnemonic det
	 * \bytecode 0x45
	 * \brief 
	 * \param ledArray 
	 */
	void turnOffLed(uint8_t ledArray);
	
	/**
	 * \instruction Jouer une sonorite
	 * \mnemonic sgo
	 * \bytecode 0x48
	 * \brief 
	 * \param note
	 */
	void playSound(uint8_t note);
	
	/**
	 * \instruction Arreter de jouer la sonorite
	 * \mnemonic sar
	 * \bytecode 0x09
	 * \brief 
	 */
	void stopSound();
	
	/**
	 * \instruction Arreter les moteurs
	 * \mnemonic mar
	 * \bytecode 0x60 or 0x61
	 * \brief 
	 */
	void stopMotors();
	
	/**
	 * \instruction Avancer
	 * \mnemonic mav
	 * \bytecode 0x62
	 * \brief 
	 * \param speed 
	 */
	void moveForward(uint8_t speed);
	
	/**
	 * \instruction Reculer
	 * \mnemonic mre
	 * \bytecode 0x63
	 * \brief 
	 * \param speed
	 */
	void moveBackward(uint8_t speed);
	
	/**
	 * \instruction Tourner a droite
	 * \mnemonic trd
	 * \bytecode 0x64
	 * \brief 
	 */
	void turnRight();
	
	/**
	 * \instruction Tourner a gauche
	 * \mnemonic trg
	 * \bytecode 0x65
	 * \brief 
	 */
	void turnLeft();
	
	/**
	 * \instruction Debut de boucle
	 * \mnemonic dbc
	 * \bytecode 0xC0
	 * \brief 
	 * \param nIterations 
	 */
	void beginLoop(uint8_t nIterations);
	
	/**
	 * \instruction Fin de boucle
	 * \mnemonic fbc
	 * \bytecode 0xC1
	 * \brief 
	 */
	void endLoop();
	
	/**
	 * \instruction Fin
	 * \mnemonic fin
	 * \bytecode 0xFF
	 * \brief 
	 */
	void end();
	
private:
	
	uint8_t beginningFound;
	uint16_t currentAdress;
	uint16_t loopBeginningAddress;
	uint8_t loopCounter;
	
};
