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
* \param freq sets begining frequency of Piezo
*             ; uses preset notes in chromatic scale
*             LA to SOSHARP
 * \return a Piezo
 */
Piezo::Piezo(uint16_t freq) {
        frequency_ = freq;
          
        DDRC |= (1 << DDC0); // sets PORTC0 to output
        DDRC |= (1 << DDC1); // sets PORTC1 to output
}

/**
 * \brief destructor for the Piezo
 */
Piezo::~Piezo() {
}

/**
 * \brief sets frequency_ to specified frequency
 * \param freq frequency that frequency_ will be set to
 *                ; can use preset notes in chromatic scale
 *                LA to SOSHARP
 */
void Piezo::setFrequency(uint16_t freq) {
    
    frequency_ = freq;
}

/**
 * \brief plays a note for one milisecond
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA to SOSHARP
 */
void Piezo::playFastNote(uint16_t note) {
    
    for(uint32_t i = 0; i < FAST; i++) {
        switch(note) {
            case LA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LA);
                break;
            case LASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LASHARP);
                break;
            case SI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SI);
                break;
            case DO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DO);
                break;
            case DOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DOSHARP);
                break;
            case RE:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RE);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RE);
                break;
            case RESHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RESHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RESHARP);
                break;
            case MI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(MI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(MI);
                break;
            case FA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FA);
                break;
            case FASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FASHARP);
                break;
            case SO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SO);
                break;
            case SOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SOSHARP);
                break;
        }
    }
}

/**
 * \brief plays a note for 250 miliseconds
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA to SOSHARP
 */
void Piezo::playSixteenthNote(uint16_t note) {
    
    for(uint32_t i = 0; i < SIXTEENTH; i++) {
        switch(note) {
            case LA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LA);
                break;
            case LASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LASHARP);
                break;
            case SI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SI);
                break;
            case DO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DO);
                break;
            case DOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DOSHARP);
                break;
            case RE:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RE);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RE);
                break;
            case RESHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RESHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RESHARP);
                break;
            case MI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(MI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(MI);
                break;
            case FA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FA);
                break;
            case FASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FASHARP);
                break;
            case SO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SO);
                break;
            case SOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SOSHARP);
                break;
        }
    }
}

/**
 * \brief plays a note for 500 miliseconds
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA to SOSHARP
 */
void Piezo::playEighthNote(uint16_t note) {
    
    for(uint32_t i = 0; i < EIGHTH; i++) {
        switch(note) {
            case LA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LA);
                break;
            case LASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LASHARP);
                break;
            case SI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SI);
                break;
            case DO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DO);
                break;
            case DOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DOSHARP);
                break;
            case RE:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RE);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RE);
                break;
            case RESHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RESHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RESHARP);
                break;
            case MI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(MI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(MI);
                break;
            case FA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FA);
                break;
            case FASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FASHARP);
                break;
            case SO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SO);
                break;
            case SOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SOSHARP);
                break;
        }
    }
}

/**
 * \brief plays a note for 1000 miliseconds
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA to SOSHARP
 */
void Piezo::playQuarterNote(uint16_t note) {
    
    for(uint32_t i = 0; i < QUARTER; i++) {
        switch(note) {
            case LA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LA);
                break;
            case LASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(LASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(LASHARP);
                break;
            case SI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SI);
                break;
            case DO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DO);
                break;
            case DOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(DOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(DOSHARP);
                break;
            case RE:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RE);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RE);
                break;
            case RESHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(RESHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(RESHARP);
                break;
            case MI:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(MI);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(MI);
                break;
            case FA:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FA);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FA);
                break;
            case FASHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(FASHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(FASHARP);
                break;
            case SO:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SO);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SO);
                break;
            case SOSHARP:
                PORTC |= (posAmplitude << DDC0);
                PORTC &= ~(posAmplitude << DDC1);
                _delay_us(SOSHARP);
                PORTC &= ~(posAmplitude << DDC0);
                PORTC |= (posAmplitude << DDC1);
                _delay_us(SOSHARP);
                break;
        }
    }
}

/**
 * \brief plays melody of the song Gucci Gang
 */
void Piezo::gucciGang() {
    
    playEighthNote(LA);
    playEighthNote(RE);
    playSixteenthNote(MI);
    playSixteenthNote(FA);
    playEighthNote(MI);
    playEighthNote(RE);
    playEighthNote(DO);
    
    playQuarterNote(LA);
    playEighthNote(LA);
    playEighthNote(RE);
    playSixteenthNote(MI);
    playSixteenthNote(FA);
    playEighthNote(MI);
    playEighthNote(RE);
    playQuarterNote(SO);
    
    playEighthNote(LA);
    playEighthNote(RE);
    playSixteenthNote(MI);
    playSixteenthNote(FA);
    playEighthNote(MI);
    playEighthNote(RE);
    playEighthNote(DO);
    
    playQuarterNote(LA);
    playEighthNote(LA);
    playEighthNote(RE);
    playSixteenthNote(MI);
    playSixteenthNote(FA);
    playEighthNote(MI);
    playEighthNote(RE);
    playEighthNote(SO);
    
    for(uint8_t i = 0; i < 12; i++) { // repetition of same note for 12 half bars
        playEighthNote(MI);
        playEighthNote(LA);
        playEighthNote(DO);
        playEighthNote(LA);
    }
}

/**
 * \brief getter for frequency_
 * \return frequency_
 */
uint16_t Piezo::getFrequency() {
    
    return frequency_;
}
