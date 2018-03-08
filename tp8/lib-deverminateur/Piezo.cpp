/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.cpp
 * Description: Simplify the use of a Piezo
 * Version: 1.0
\******************************************************************************/

#include "Piezo.h"

/**
 * \brief constructor for the Piezo; the DDRC register will be set to enable
 *        output on the appropriate pins
 * \param pwmFreq sets begining frequency of the pwm in Hz
 * \return a Piezo
 */
Piezo::Piezo(uint16_t pwmFreq)
    : pwmFrequency_(pwmFreq) {
          
        DDRC |= (1 << DDC0); // sets PORTC0 to output
        DDRC |= (1 << DDC1); // sets PORTC1 to output
}

/**
 * \brief destructor for the Piezo
 */
Piezo::~Piezo() {
}

/**
 * \brief sets pwmFrequency_ to specified frequency
 * \param pwmFreq frequency that pwmFrequency_ will be set to
 *                ; can use preset notes in chromatic scale
 *                LA to SOSHARP
 */
void Piezo::setPwmFrequency(uint16_t pwmFreq) {
    
    pwmFrequency_ = pwmFreq;
}

/**
 * \brief plays tone set in pwmFrequency_ for 500 miliseconds
 */
void Piezo::playTone() {
    
    uint32_t lengthOfTone = pwmFrequency_ * 500;
    uint16_t highTime = 1000.0 / (pwmFrequency_/2);
    uint16_t lowTime = 1000.0 - ontime;
    
    for(uint32_t i = 0; i < lengthOfTone; i++) {
        
        PORTC |= (posAmplitude << DDC0);
        delay_ms(highTime);
        PORTC |= (negAmplitude << DDC0);
        delay_ms(lowTime);
    }
}

/**
 * \brief plays a note for one milisecond
 * \param pwmFreq frequency that the Piezo will play; can use preset notes
 *                in chromatic scale LA to SOSHARP
 */
void Piezo::playFastNote(uint16_t pwmFreq) {
    
    pwmFrequency_ = pwmFreq;
    
    uint32_t nLoopIterations = pwmFreq * 1;
    uint16_t highTime = 1000.0 / (pwmFreq/2);
    uint16_t lowTime = 1000.0 - ontime;
    
    for(uint32_t i = 0; i < nLoopIterations; i++) {
        
        PORTC = posAmplitude;
        delay_ms(highTime);
        PORTC = negAmplitude;
        delay_ms(lowTime);
    }
}

/**
 * \brief plays a note for one 250 miliseconds or one sixteenth note
 * \param pwmFreq frequency that the Piezo will play; can use preset notes
 *                in chromatic scale LA to SOSHARP
 */
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

/**
 * \brief plays a note for one 500 miliseconds or one eighth note
 * \param pwmFreq frequency that the Piezo will play; can use preset notes
 *                in chromatic scale LA to SOSHARP
 */
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

/**
 * \brief plays a note for one 1000 miliseconds or one quarter note
 * \param pwmFreq frequency that the Piezo will play; can use preset notes
 *                in chromatic scale LA to SOSHARP
 */
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

/**
 * \brief plays melody of the song Gucci Gang
 */
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
    
    for(uint8_t i = 0; i < 12; i++) { // repetition of same note for 12 half bars
        playEighthNote(MI);
        playEighthNote(LA);
        playEighthNote(DO);
        playEighthNote(LA);
    }
}

/**
 * \brief plays a vroom vroom sound
 */
void Piezo::vroomVroom() {
    
    for(uint16_t i = 30; i < 1030; i++) { // rev up sound
        
        playFastNote(i);
    }
    for(uint16_t j = 1030; i > 30; j--) { // rev down sound
        
        playFastNote(j);
}

/**
 * \brief getter for pwmFrequency_
 * \return pwmFrequency_
 */
uint16_t Piezo::getPwmFrequency() {
    
    return pwmFrequency_;
}
