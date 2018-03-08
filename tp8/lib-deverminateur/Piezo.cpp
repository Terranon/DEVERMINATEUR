/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.cpp
 * Description: Simplify the use of a Piezo
 * Version: 1.0
\******************************************************************************/

#include "Piezo.h"

/**
 * \brief constructor for the Led; the DDRC register will be set to enable
 *        output on the appropriate pins
 * \param pwmFreq sets begining frequency of the pwm in Hz
 * \return an Led
 */
Piezo::Piezo(uint16_t pwmFreq)
    : pwmFrequency_(pwmFreq) {
          
        DDRC = 0x03;              // sets PINC0 and PINC1 to output
}

void Piezo::playFastNote(uint16_t pwmFreq) {
    
    pwmFrequency_ = pwmFreq;
    
    uint32_t nLoopIterations = pwmFreq * 1;
    uint16_t highTime = 1000.0 / (pwmFreq/2);
    uint16_t lowTime = 1000.0 - ontime;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
        PORTC = 0x01
        delay_ms(highTime);
        PORTC = 0x02
        delay_ms(lowTime);
    }
}

void Piezo::playSixteenthNote(uint16_t pwmFreq) {
    
    pwmFrequency_ = pwmFreq;
    
    uint32_t nLoopIterations = pwmFreq * 250;
    uint16_t highTime = 1000.0 / (pwmFreq/2);
    uint16_t lowTime = 1000.0 - ontime;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
        PORTC = 0x01
        delay_ms(highTime);
        PORTC = 0x02
        delay_ms(lowTime);
    }
}

void Piezo::playEighthNote(uint16_t pwmFreq) {
    
    pwmFrequency_ = pwmFreq;
    
    uint32_t nLoopIterations = pwmFreq * 500;
    uint16_t highTime = 1000 / (pwmFreq/2);
    uint16_t lowTime = 1000 - ontime;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
        PORTC = 0x01
        delay_ms(highTime);
        PORTC = 0x02
        delay_ms(lowTime);
    }
}

void Piezo::playQuarterNote(uint16_t pwmFreq) {
    
    pwmFrequency_ = pwmFreq;
    
    uint32_t nLoopIterations = pwmFreq * 1000;
    uint16_t highTime = 1000.0 / (pwmFreq/2);
    uint16_t lowTime = 1000.0 - ontime;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
        PORTC = 0x01
        delay_ms(highTime);
        PORTC = 0x02
        delay_ms(lowTime);
    }
}

void Piezo::majorScale() {
    
}

void Piezo::arpegio() {
    
}

void Piezo::gucciGang() {
    
    playEighthNote(LA * 2);
    playEighthNote(RE * 2);
    playSixteenthNote(MI * 2);
    playSixteenthNote(FA * 2);
    playEighthNote(MI * 2);
    playEighthNote(RE * 2);
    playEighthNote(DO * 2);
    
    playQuarterNote(LA * 2);
    playEighthNote(LA * 2);
    playEighthNote(RE * 2);
    playSixteenthNote(MI * 2);
    playSixteenthNote(FA * 2);
    playEighthNote(MI * 2);
    playEighthNote(RE * 2);
    playQuarterNote(SO * 2);
    
    playEighthNote(LA * 2);
    playEighthNote(RE * 2);
    playSixteenthNote(MI * 2);
    playSixteenthNote(FA * 2);
    playEighthNote(MI * 2);
    playEighthNote(RE * 2);
    playEighthNote(DO * 2);
    
    playQuarterNote(LA * 2);
    playEighthNote(LA * 2);
    playEighthNote(RE * 2);
    playSixteenthNote(MI * 2);
    playSixteenthNote(FA * 2);
    playEighthNote(MI * 2);
    playEighthNote(RE * 2);
    playEighthNote(SO * 2);
    
    for(uint8_t i = 0; i < 12; i++) {
        playEighthNote(MI);
        playEighthNote(LA);
        playEighthNote(DO);
        playEighthNote(LA);
    }
}

void Piezo::vroomVroom() {
    
    for(uint16_t i = 30; i < 1030; i++) {
        
        playFastNote(i);
    }
    for(uint16_t j = 
}

/**
 * \brief destructor for the Led
 */
Led::~Led() {
}
