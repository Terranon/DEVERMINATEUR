/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.cpp
 * Description: Simplify the use of a Piezo
 * Version: 2.0
\******************************************************************************/

#include "Piezo.h"

/**
 * \brief constructor for the Piezo; the DDRC register will be set to enable
 *        output on the appropriate pins
 * \return a Piezo
 */
Piezo::Piezo() {
      : prescalerMode_()
        eightBitValue_() ;
          
        DDRC |= (1 << DDC6); // sets PORTC6 to output
        DDRC |= (1 << DDC7); // sets PORTC7 to output
        PORTC &= ~(1 << DDC6); // sets output value of PORTC7 to zero
        
        TCCR2A &= ~(1 << COM2A1); // non-pwm, toggle OC2A on Compare Match
        TCCR2A |=  (1 << COM2A0);
        
        TCCR2A |=  (1 << WGM21); // CTC, TOP = OCR2A
        TCCR2A &= ~(1 << WGM20);
        TCCR2B &= ~(1 << WGM22);
}

/**
 * \brief destructor for the Piezo
 */
Piezo::~Piezo() {
}

/**
 * \brief plays a note for ten miliseconds
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA_ONE:110Hz to LA_FOUR:880Hz
 */
void Piezo::playFastNote(Note note) {
    
    TCCR2A &= ~(1 << COM2A1); // non-pwm, toggle OC2A on Compare Match
    TCCR2A |=  (1 << COM2A0);
    
    switch(note) {
        case LA_ONE:
            prescalerMode_ = LA_ONE.prescalerMode;
            eightBitValue_ = LA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_ONE.prescalerMode << CS20);
            OCR2A = LA_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_ONE:
            prescalerMode_ = LASHARP_ONE.prescalerMode;
            eightBitValue_ = LASHARP_ONE.eightBitValue;
            TCCR2B |= (LASHARP_ONE.prescalerMode << CS20);
            OCR2A = LASHARP_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_ONE:
            prescalerMode_ = SI_ONE.prescalerMode;
            eightBitValue_ = SI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_ONE.prescalerMode << CS20);
            OCR2A = SI_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_ONE:
            prescalerMode_ = DO_ONE.prescalerMode;
            eightBitValue_ = DO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_ONE.prescalerMode << CS20);
            OCR2A = DO_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_ONE:
            prescalerMode_ = DOSHARP_ONE.prescalerMode;
            eightBitValue_ = DOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_ONE.prescalerMode << CS20);
            OCR2A = DOSHARP_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_ONE:
            prescalerMode_ = RE_ONE.prescalerMode;
            eightBitValue_ = RE_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_ONE.prescalerMode << CS20);
            OCR2A = RE_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_ONE:
            prescalerMode_ = RESHARP_ONE.prescalerMode;
            eightBitValue_ = RESHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_ONE.prescalerMode << CS20);
            OCR2A = RESHARP_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_ONE:
            prescalerMode_ = MI_ONE.prescalerMode;
            eightBitValue_ = MI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_ONE.prescalerMode << CS20);
            OCR2A = MI_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_ONE:
            prescalerMode_ = FA_ONE.prescalerMode;
            eightBitValue_ = FA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_ONE.prescalerMode << CS20);
            OCR2A = FA_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_ONE:
            prescalerMode_ = FASHARP_ONE.prescalerMode;
            eightBitValue_ = FASHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_ONE.prescalerMode << CS20);
            OCR2A = FASHARP_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_ONE:
            prescalerMode_ = SO_ONE.prescalerMode;
            eightBitValue_ = SO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_ONE.prescalerMode << CS20);
            OCR2A = SO_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_ONE:
            prescalerMode_ = SOSHARP_ONE.prescalerMode;
            eightBitValue_ = SOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_ONE.prescalerMode << CS20);
            OCR2A = SOSHARP_ONE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        
            
        case LA_TWO:
            prescalerMode_ = LA_TWO.prescalerMode;
            eightBitValue_ = LA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_TWO.prescalerMode << CS20);
            OCR2A = LA_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_TWO:
            prescalerMode_ = LASHARP_TWO.prescalerMode;
            eightBitValue_ = LASHARP_TWO.eightBitValue;
            TCCR2B |= (LASHARP_TWO.prescalerMode << CS20);
            OCR2A = LASHARP_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_TWO:
            prescalerMode_ = SI_TWO.prescalerMode;
            eightBitValue_ = SI_TWO.eightBitValue
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_TWO.prescalerMode << CS20);
            OCR2A = SI_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_TWO:
            prescalerMode_ = DO_TWO.prescalerMode;
            eightBitValue_ = DO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_TWO.prescalerMode << CS20);
            OCR2A = DO_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_TWO:
            prescalerMode_ = DOSHARP_TWO.prescalerMode;
            eightBitValue_ = DOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_TWO.prescalerMode << CS20);
            OCR2A = DOSHARP_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_TWO:
            prescalerMode_ = RE_TWO.prescalerMode;
            eightBitValue_ = RE_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_TWO.prescalerMode << CS20);
            OCR2A = RE_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_TWO:
            prescalerMode_ = RESHARP_TWO.prescalerMode;
            eightBitValue_ = RESHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_TWO.prescalerMode << CS20);
            OCR2A = RESHARP_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_TWO:
            prescalerMode_ = MI_TWO.prescalerMode;
            eightBitValue_ = MI_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_TWO.prescalerMode << CS20);
            OCR2A = MI_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_TWO:
            prescalerMode_ = FA_TWO.prescalerMode;
            eightBitValue_ = FA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_TWO.prescalerMode << CS20);
            OCR2A = FA_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_TWO:
            prescalerMode_ = FASHARP_TWO.prescalerMode;
            eightBitValue_ = FASHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_TWO.prescalerMode << CS20);
            OCR2A = FASHARP_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_TWO:
            prescalerMode_ = SO_TWO.prescalerMode;
            eightBitValue_ = SO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_TWO.prescalerMode << CS20);
            OCR2A = SO_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_TWO:
            prescalerMode_ = SOSHARP_TWO.prescalerMode;
            eightBitValue_ = SOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_TWO.prescalerMode << CS20);
            OCR2A = SOSHARP_TWO.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_THREE:
            prescalerMode_ = LA_THREE.prescalerMode;
            eightBitValue_ = LA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_THREE.prescalerMode << CS20);
            OCR2A = LA_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_THREE:
            prescalerMode_ = LASHARP_THREE.prescalerMode;
            eightBitValue_ = LASHARP_THREE.eightBitValue;
            TCCR2B |= (LASHARP_THREE.prescalerMode << CS20);
            OCR2A = LASHARP_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_THREE:
            prescalerMode_ = SI_THREE.prescalerMode;
            eightBitValue_ = SI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_THREE.prescalerMode << CS20);
            OCR2A = SI_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_THREE:
            prescalerMode_ = DO_THREE.prescalerMode;
            eightBitValue_ = DO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_THREE.prescalerMode << CS20);
            OCR2A = DO_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_THREE:
            prescalerMode_ = DOSHARP_THREE.prescalerMode;
            eightBitValue_ = DOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_THREE.prescalerMode << CS20);
            OCR2A = DOSHARP_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_THREE:
            prescalerMode_ = RE_THREE.prescalerMode;
            eightBitValue_ = RE_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_THREE.prescalerMode << CS20);
            OCR2A = RE_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_THREE:
            prescalerMode_ = RESHARP_THREE.prescalerMode;
            eightBitValue_ = RESHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_THREE.prescalerMode << CS20);
            OCR2A = RESHARP_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_THREE:
            prescalerMode_ = MI_THREE.prescalerMode;
            eightBitValue_ = MI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_THREE.prescalerMode << CS20);
            OCR2A = MI_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_THREE:
            prescalerMode_ = FA_THREE.prescalerMode;
            eightBitValue_ = FA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_THREE.prescalerMode << CS20);
            OCR2A = FA_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_THREE:
            prescalerMode_ = FASHARP_THREE.prescalerMode;
            eightBitValue_ = FASHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_THREE.prescalerMode << CS20);
            OCR2A = FASHARP_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_THREE:
            prescalerMode_ = SO_THREE.prescalerMode;
            eightBitValue_ = SO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_THREE.prescalerMode << CS20);
            OCR2A = SO_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_THREE:
            prescalerMode_ = SOSHARP_THREE.prescalerMode;
            eightBitValue_ = SOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_THREE.prescalerMode << CS20);
            OCR2A = SOSHARP_THREE.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_FOUR:
            prescalerMode_ = LA_FOUR.prescalerMode;
            eightBitValue_ = LA_FOUR.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_FOUR.prescalerMode << CS20);
            OCR2A = LA_FOUR.eightBitValue;
            _delay_ms(FAST);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
    }
}

/**
 * \brief plays a note for 250 miliseconds
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA_ONE:110Hz to LA_FOUR:880Hz
 */
void Piezo::playSixteenthNote(Note note) {
    
    TCCR2A &= ~(1 << COM2A1); // non-pwm, toggle OC2A on Compare Match
    TCCR2A |=  (1 << COM2A0);
    
    switch(note) {
        case LA_ONE:
            prescalerMode_ = LA_ONE.prescalerMode;
            eightBitValue_ = LA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_ONE.prescalerMode << CS20);
            OCR2A = LA_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_ONE:
            prescalerMode_ = LASHARP_ONE.prescalerMode;
            eightBitValue_ = LASHARP_ONE.eightBitValue;
            TCCR2B |= (LASHARP_ONE.prescalerMode << CS20);
            OCR2A = LASHARP_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_ONE:
            prescalerMode_ = SI_ONE.prescalerMode;
            eightBitValue_ = SI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_ONE.prescalerMode << CS20);
            OCR2A = SI_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_ONE:
            prescalerMode_ = DO_ONE.prescalerMode;
            eightBitValue_ = DO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_ONE.prescalerMode << CS20);
            OCR2A = DO_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_ONE:
            prescalerMode_ = DOSHARP_ONE.prescalerMode;
            eightBitValue_ = DOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_ONE.prescalerMode << CS20);
            OCR2A = DOSHARP_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_ONE:
            prescalerMode_ = RE_ONE.prescalerMode;
            eightBitValue_ = RE_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_ONE.prescalerMode << CS20);
            OCR2A = RE_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_ONE:
            prescalerMode_ = RESHARP_ONE.prescalerMode;
            eightBitValue_ = RESHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_ONE.prescalerMode << CS20);
            OCR2A = RESHARP_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_ONE:
            prescalerMode_ = MI_ONE.prescalerMode;
            eightBitValue_ = MI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_ONE.prescalerMode << CS20);
            OCR2A = MI_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_ONE:
            prescalerMode_ = FA_ONE.prescalerMode;
            eightBitValue_ = FA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_ONE.prescalerMode << CS20);
            OCR2A = FA_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_ONE:
            prescalerMode_ = FASHARP_ONE.prescalerMode;
            eightBitValue_ = FASHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_ONE.prescalerMode << CS20);
            OCR2A = FASHARP_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_ONE:
            prescalerMode_ = SO_ONE.prescalerMode;
            eightBitValue_ = SO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_ONE.prescalerMode << CS20);
            OCR2A = SO_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_ONE:
            prescalerMode_ = SOSHARP_ONE.prescalerMode;
            eightBitValue_ = SOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_ONE.prescalerMode << CS20);
            OCR2A = SOSHARP_ONE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        
            
        case LA_TWO:
            prescalerMode_ = LA_TWO.prescalerMode;
            eightBitValue_ = LA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_TWO.prescalerMode << CS20);
            OCR2A = LA_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_TWO:
            prescalerMode_ = LASHARP_TWO.prescalerMode;
            eightBitValue_ = LASHARP_TWO.eightBitValue;
            TCCR2B |= (LASHARP_TWO.prescalerMode << CS20);
            OCR2A = LASHARP_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_TWO:
            prescalerMode_ = SI_TWO.prescalerMode;
            eightBitValue_ = SI_TWO.eightBitValue
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_TWO.prescalerMode << CS20);
            OCR2A = SI_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_TWO:
            prescalerMode_ = DO_TWO.prescalerMode;
            eightBitValue_ = DO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_TWO.prescalerMode << CS20);
            OCR2A = DO_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_TWO:
            prescalerMode_ = DOSHARP_TWO.prescalerMode;
            eightBitValue_ = DOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_TWO.prescalerMode << CS20);
            OCR2A = DOSHARP_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_TWO:
            prescalerMode_ = RE_TWO.prescalerMode;
            eightBitValue_ = RE_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_TWO.prescalerMode << CS20);
            OCR2A = RE_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_TWO:
            prescalerMode_ = RESHARP_TWO.prescalerMode;
            eightBitValue_ = RESHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_TWO.prescalerMode << CS20);
            OCR2A = RESHARP_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_TWO:
            prescalerMode_ = MI_TWO.prescalerMode;
            eightBitValue_ = MI_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_TWO.prescalerMode << CS20);
            OCR2A = MI_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_TWO:
            prescalerMode_ = FA_TWO.prescalerMode;
            eightBitValue_ = FA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_TWO.prescalerMode << CS20);
            OCR2A = FA_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_TWO:
            prescalerMode_ = FASHARP_TWO.prescalerMode;
            eightBitValue_ = FASHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_TWO.prescalerMode << CS20);
            OCR2A = FASHARP_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_TWO:
            prescalerMode_ = SO_TWO.prescalerMode;
            eightBitValue_ = SO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_TWO.prescalerMode << CS20);
            OCR2A = SO_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_TWO:
            prescalerMode_ = SOSHARP_TWO.prescalerMode;
            eightBitValue_ = SOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_TWO.prescalerMode << CS20);
            OCR2A = SOSHARP_TWO.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_THREE:
            prescalerMode_ = LA_THREE.prescalerMode;
            eightBitValue_ = LA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_THREE.prescalerMode << CS20);
            OCR2A = LA_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_THREE:
            prescalerMode_ = LASHARP_THREE.prescalerMode;
            eightBitValue_ = LASHARP_THREE.eightBitValue;
            TCCR2B |= (LASHARP_THREE.prescalerMode << CS20);
            OCR2A = LASHARP_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_THREE:
            prescalerMode_ = SI_THREE.prescalerMode;
            eightBitValue_ = SI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_THREE.prescalerMode << CS20);
            OCR2A = SI_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_THREE:
            prescalerMode_ = DO_THREE.prescalerMode;
            eightBitValue_ = DO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_THREE.prescalerMode << CS20);
            OCR2A = DO_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_THREE:
            prescalerMode_ = DOSHARP_THREE.prescalerMode;
            eightBitValue_ = DOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_THREE.prescalerMode << CS20);
            OCR2A = DOSHARP_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_THREE:
            prescalerMode_ = RE_THREE.prescalerMode;
            eightBitValue_ = RE_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_THREE.prescalerMode << CS20);
            OCR2A = RE_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_THREE:
            prescalerMode_ = RESHARP_THREE.prescalerMode;
            eightBitValue_ = RESHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_THREE.prescalerMode << CS20);
            OCR2A = RESHARP_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_THREE:
            prescalerMode_ = MI_THREE.prescalerMode;
            eightBitValue_ = MI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_THREE.prescalerMode << CS20);
            OCR2A = MI_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_THREE:
            prescalerMode_ = FA_THREE.prescalerMode;
            eightBitValue_ = FA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_THREE.prescalerMode << CS20);
            OCR2A = FA_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_THREE:
            prescalerMode_ = FASHARP_THREE.prescalerMode;
            eightBitValue_ = FASHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_THREE.prescalerMode << CS20);
            OCR2A = FASHARP_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_THREE:
            prescalerMode_ = SO_THREE.prescalerMode;
            eightBitValue_ = SO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_THREE.prescalerMode << CS20);
            OCR2A = SO_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_THREE:
            prescalerMode_ = SOSHARP_THREE.prescalerMode;
            eightBitValue_ = SOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_THREE.prescalerMode << CS20);
            OCR2A = SOSHARP_THREE.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_FOUR:
            prescalerMode_ = LA_FOUR.prescalerMode;
            eightBitValue_ = LA_FOUR.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_FOUR.prescalerMode << CS20);
            OCR2A = LA_FOUR.eightBitValue;
            _delay_ms(SIXTEENTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
    }
}

/**
 * \brief plays a note for 500 miliseconds
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA_ONE:110Hz to LA_FOUR:880Hz
 */
void Piezo::playEighthNote(Note note) {
    
    TCCR2A &= ~(1 << COM2A1); // non-pwm, toggle OC2A on Compare Match
    TCCR2A |=  (1 << COM2A0);
    
    switch(note) {
        case LA_ONE:
            prescalerMode_ = LA_ONE.prescalerMode;
            eightBitValue_ = LA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_ONE.prescalerMode << CS20);
            OCR2A = LA_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_ONE:
            prescalerMode_ = LASHARP_ONE.prescalerMode;
            eightBitValue_ = LASHARP_ONE.eightBitValue;
            TCCR2B |= (LASHARP_ONE.prescalerMode << CS20);
            OCR2A = LASHARP_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_ONE:
            prescalerMode_ = SI_ONE.prescalerMode;
            eightBitValue_ = SI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_ONE.prescalerMode << CS20);
            OCR2A = SI_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_ONE:
            prescalerMode_ = DO_ONE.prescalerMode;
            eightBitValue_ = DO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_ONE.prescalerMode << CS20);
            OCR2A = DO_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_ONE:
            prescalerMode_ = DOSHARP_ONE.prescalerMode;
            eightBitValue_ = DOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_ONE.prescalerMode << CS20);
            OCR2A = DOSHARP_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_ONE:
            prescalerMode_ = RE_ONE.prescalerMode;
            eightBitValue_ = RE_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_ONE.prescalerMode << CS20);
            OCR2A = RE_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_ONE:
            prescalerMode_ = RESHARP_ONE.prescalerMode;
            eightBitValue_ = RESHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_ONE.prescalerMode << CS20);
            OCR2A = RESHARP_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_ONE:
            prescalerMode_ = MI_ONE.prescalerMode;
            eightBitValue_ = MI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_ONE.prescalerMode << CS20);
            OCR2A = MI_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_ONE:
            prescalerMode_ = FA_ONE.prescalerMode;
            eightBitValue_ = FA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_ONE.prescalerMode << CS20);
            OCR2A = FA_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_ONE:
            prescalerMode_ = FASHARP_ONE.prescalerMode;
            eightBitValue_ = FASHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_ONE.prescalerMode << CS20);
            OCR2A = FASHARP_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_ONE:
            prescalerMode_ = SO_ONE.prescalerMode;
            eightBitValue_ = SO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_ONE.prescalerMode << CS20);
            OCR2A = SO_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_ONE:
            prescalerMode_ = SOSHARP_ONE.prescalerMode;
            eightBitValue_ = SOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_ONE.prescalerMode << CS20);
            OCR2A = SOSHARP_ONE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        
            
        case LA_TWO:
            prescalerMode_ = LA_TWO.prescalerMode;
            eightBitValue_ = LA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_TWO.prescalerMode << CS20);
            OCR2A = LA_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_TWO:
            prescalerMode_ = LASHARP_TWO.prescalerMode;
            eightBitValue_ = LASHARP_TWO.eightBitValue;
            TCCR2B |= (LASHARP_TWO.prescalerMode << CS20);
            OCR2A = LASHARP_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_TWO:
            prescalerMode_ = SI_TWO.prescalerMode;
            eightBitValue_ = SI_TWO.eightBitValue
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_TWO.prescalerMode << CS20);
            OCR2A = SI_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_TWO:
            prescalerMode_ = DO_TWO.prescalerMode;
            eightBitValue_ = DO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_TWO.prescalerMode << CS20);
            OCR2A = DO_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_TWO:
            prescalerMode_ = DOSHARP_TWO.prescalerMode;
            eightBitValue_ = DOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_TWO.prescalerMode << CS20);
            OCR2A = DOSHARP_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_TWO:
            prescalerMode_ = RE_TWO.prescalerMode;
            eightBitValue_ = RE_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_TWO.prescalerMode << CS20);
            OCR2A = RE_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_TWO:
            prescalerMode_ = RESHARP_TWO.prescalerMode;
            eightBitValue_ = RESHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_TWO.prescalerMode << CS20);
            OCR2A = RESHARP_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_TWO:
            prescalerMode_ = MI_TWO.prescalerMode;
            eightBitValue_ = MI_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_TWO.prescalerMode << CS20);
            OCR2A = MI_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_TWO:
            prescalerMode_ = FA_TWO.prescalerMode;
            eightBitValue_ = FA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_TWO.prescalerMode << CS20);
            OCR2A = FA_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_TWO:
            prescalerMode_ = FASHARP_TWO.prescalerMode;
            eightBitValue_ = FASHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_TWO.prescalerMode << CS20);
            OCR2A = FASHARP_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_TWO:
            prescalerMode_ = SO_TWO.prescalerMode;
            eightBitValue_ = SO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_TWO.prescalerMode << CS20);
            OCR2A = SO_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_TWO:
            prescalerMode_ = SOSHARP_TWO.prescalerMode;
            eightBitValue_ = SOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_TWO.prescalerMode << CS20);
            OCR2A = SOSHARP_TWO.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_THREE:
            prescalerMode_ = LA_THREE.prescalerMode;
            eightBitValue_ = LA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_THREE.prescalerMode << CS20);
            OCR2A = LA_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_THREE:
            prescalerMode_ = LASHARP_THREE.prescalerMode;
            eightBitValue_ = LASHARP_THREE.eightBitValue;
            TCCR2B |= (LASHARP_THREE.prescalerMode << CS20);
            OCR2A = LASHARP_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_THREE:
            prescalerMode_ = SI_THREE.prescalerMode;
            eightBitValue_ = SI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_THREE.prescalerMode << CS20);
            OCR2A = SI_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_THREE:
            prescalerMode_ = DO_THREE.prescalerMode;
            eightBitValue_ = DO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_THREE.prescalerMode << CS20);
            OCR2A = DO_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_THREE:
            prescalerMode_ = DOSHARP_THREE.prescalerMode;
            eightBitValue_ = DOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_THREE.prescalerMode << CS20);
            OCR2A = DOSHARP_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_THREE:
            prescalerMode_ = RE_THREE.prescalerMode;
            eightBitValue_ = RE_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_THREE.prescalerMode << CS20);
            OCR2A = RE_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_THREE:
            prescalerMode_ = RESHARP_THREE.prescalerMode;
            eightBitValue_ = RESHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_THREE.prescalerMode << CS20);
            OCR2A = RESHARP_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_THREE:
            prescalerMode_ = MI_THREE.prescalerMode;
            eightBitValue_ = MI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_THREE.prescalerMode << CS20);
            OCR2A = MI_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_THREE:
            prescalerMode_ = FA_THREE.prescalerMode;
            eightBitValue_ = FA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_THREE.prescalerMode << CS20);
            OCR2A = FA_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_THREE:
            prescalerMode_ = FASHARP_THREE.prescalerMode;
            eightBitValue_ = FASHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_THREE.prescalerMode << CS20);
            OCR2A = FASHARP_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_THREE:
            prescalerMode_ = SO_THREE.prescalerMode;
            eightBitValue_ = SO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_THREE.prescalerMode << CS20);
            OCR2A = SO_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_THREE:
            prescalerMode_ = SOSHARP_THREE.prescalerMode;
            eightBitValue_ = SOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_THREE.prescalerMode << CS20);
            OCR2A = SOSHARP_THREE.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_FOUR:
            prescalerMode_ = LA_FOUR.prescalerMode;
            eightBitValue_ = LA_FOUR.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_FOUR.prescalerMode << CS20);
            OCR2A = LA_FOUR.eightBitValue;
            _delay_ms(EIGHTH);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
    }
}

/**
 * \brief plays a note for 1000 miliseconds
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA_ONE:110Hz to LA_FOUR:880Hz
 */
void Piezo::playQuarterNote(Note note) {
    
    TCCR2A &= ~(1 << COM2A1); // non-pwm, toggle OC2A on Compare Match
    TCCR2A |=  (1 << COM2A0);
    
    switch(note) {
        case LA_ONE:
            prescalerMode_ = LA_ONE.prescalerMode;
            eightBitValue_ = LA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_ONE.prescalerMode << CS20);
            OCR2A = LA_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_ONE:
            prescalerMode_ = LASHARP_ONE.prescalerMode;
            eightBitValue_ = LASHARP_ONE.eightBitValue;
            TCCR2B |= (LASHARP_ONE.prescalerMode << CS20);
            OCR2A = LASHARP_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_ONE:
            prescalerMode_ = SI_ONE.prescalerMode;
            eightBitValue_ = SI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_ONE.prescalerMode << CS20);
            OCR2A = SI_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_ONE:
            prescalerMode_ = DO_ONE.prescalerMode;
            eightBitValue_ = DO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_ONE.prescalerMode << CS20);
            OCR2A = DO_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_ONE:
            prescalerMode_ = DOSHARP_ONE.prescalerMode;
            eightBitValue_ = DOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_ONE.prescalerMode << CS20);
            OCR2A = DOSHARP_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_ONE:
            prescalerMode_ = RE_ONE.prescalerMode;
            eightBitValue_ = RE_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_ONE.prescalerMode << CS20);
            OCR2A = RE_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_ONE:
            prescalerMode_ = RESHARP_ONE.prescalerMode;
            eightBitValue_ = RESHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_ONE.prescalerMode << CS20);
            OCR2A = RESHARP_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_ONE:
            prescalerMode_ = MI_ONE.prescalerMode;
            eightBitValue_ = MI_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_ONE.prescalerMode << CS20);
            OCR2A = MI_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_ONE:
            prescalerMode_ = FA_ONE.prescalerMode;
            eightBitValue_ = FA_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_ONE.prescalerMode << CS20);
            OCR2A = FA_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_ONE:
            prescalerMode_ = FASHARP_ONE.prescalerMode;
            eightBitValue_ = FASHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_ONE.prescalerMode << CS20);
            OCR2A = FASHARP_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_ONE:
            prescalerMode_ = SO_ONE.prescalerMode;
            eightBitValue_ = SO_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_ONE.prescalerMode << CS20);
            OCR2A = SO_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_ONE:
            prescalerMode_ = SOSHARP_ONE.prescalerMode;
            eightBitValue_ = SOSHARP_ONE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_ONE.prescalerMode << CS20);
            OCR2A = SOSHARP_ONE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        
            
        case LA_TWO:
            prescalerMode_ = LA_TWO.prescalerMode;
            eightBitValue_ = LA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_TWO.prescalerMode << CS20);
            OCR2A = LA_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_TWO:
            prescalerMode_ = LASHARP_TWO.prescalerMode;
            eightBitValue_ = LASHARP_TWO.eightBitValue;
            TCCR2B |= (LASHARP_TWO.prescalerMode << CS20);
            OCR2A = LASHARP_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_TWO:
            prescalerMode_ = SI_TWO.prescalerMode;
            eightBitValue_ = SI_TWO.eightBitValue
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_TWO.prescalerMode << CS20);
            OCR2A = SI_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_TWO:
            prescalerMode_ = DO_TWO.prescalerMode;
            eightBitValue_ = DO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_TWO.prescalerMode << CS20);
            OCR2A = DO_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_TWO:
            prescalerMode_ = DOSHARP_TWO.prescalerMode;
            eightBitValue_ = DOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_TWO.prescalerMode << CS20);
            OCR2A = DOSHARP_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_TWO:
            prescalerMode_ = RE_TWO.prescalerMode;
            eightBitValue_ = RE_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_TWO.prescalerMode << CS20);
            OCR2A = RE_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_TWO:
            prescalerMode_ = RESHARP_TWO.prescalerMode;
            eightBitValue_ = RESHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_TWO.prescalerMode << CS20);
            OCR2A = RESHARP_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_TWO:
            prescalerMode_ = MI_TWO.prescalerMode;
            eightBitValue_ = MI_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_TWO.prescalerMode << CS20);
            OCR2A = MI_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_TWO:
            prescalerMode_ = FA_TWO.prescalerMode;
            eightBitValue_ = FA_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_TWO.prescalerMode << CS20);
            OCR2A = FA_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_TWO:
            prescalerMode_ = FASHARP_TWO.prescalerMode;
            eightBitValue_ = FASHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_TWO.prescalerMode << CS20);
            OCR2A = FASHARP_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_TWO:
            prescalerMode_ = SO_TWO.prescalerMode;
            eightBitValue_ = SO_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_TWO.prescalerMode << CS20);
            OCR2A = SO_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_TWO:
            prescalerMode_ = SOSHARP_TWO.prescalerMode;
            eightBitValue_ = SOSHARP_TWO.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_TWO.prescalerMode << CS20);
            OCR2A = SOSHARP_TWO.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_THREE:
            prescalerMode_ = LA_THREE.prescalerMode;
            eightBitValue_ = LA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_THREE.prescalerMode << CS20);
            OCR2A = LA_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case LASHARP_THREE:
            prescalerMode_ = LASHARP_THREE.prescalerMode;
            eightBitValue_ = LASHARP_THREE.eightBitValue;
            TCCR2B |= (LASHARP_THREE.prescalerMode << CS20);
            OCR2A = LASHARP_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SI_THREE:
            prescalerMode_ = SI_THREE.prescalerMode;
            eightBitValue_ = SI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SI_THREE.prescalerMode << CS20);
            OCR2A = SI_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DO_THREE:
            prescalerMode_ = DO_THREE.prescalerMode;
            eightBitValue_ = DO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DO_THREE.prescalerMode << CS20);
            OCR2A = DO_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case DOSHARP_THREE:
            prescalerMode_ = DOSHARP_THREE.prescalerMode;
            eightBitValue_ = DOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (DOSHARP_THREE.prescalerMode << CS20);
            OCR2A = DOSHARP_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RE_THREE:
            prescalerMode_ = RE_THREE.prescalerMode;
            eightBitValue_ = RE_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RE_THREE.prescalerMode << CS20);
            OCR2A = RE_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case RESHARP_THREE:
            prescalerMode_ = RESHARP_THREE.prescalerMode;
            eightBitValue_ = RESHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (RESHARP_THREE.prescalerMode << CS20);
            OCR2A = RESHARP_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case MI_THREE:
            prescalerMode_ = MI_THREE.prescalerMode;
            eightBitValue_ = MI_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (MI_THREE.prescalerMode << CS20);
            OCR2A = MI_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FA_THREE:
            prescalerMode_ = FA_THREE.prescalerMode;
            eightBitValue_ = FA_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FA_THREE.prescalerMode << CS20);
            OCR2A = FA_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case FASHARP_THREE:
            prescalerMode_ = FASHARP_THREE.prescalerMode;
            eightBitValue_ = FASHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (FASHARP_THREE.prescalerMode << CS20);
            OCR2A = FASHARP_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SO_THREE:
            prescalerMode_ = SO_THREE.prescalerMode;
            eightBitValue_ = SO_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SO_THREE.prescalerMode << CS20);
            OCR2A = SO_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
        case SOSHARP_THREE:
            prescalerMode_ = SOSHARP_THREE.prescalerMode;
            eightBitValue_ = SOSHARP_THREE.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (SOSHARP_THREE.prescalerMode << CS20);
            OCR2A = SOSHARP_THREE.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
            
            
        case LA_FOUR:
            prescalerMode_ = LA_FOUR.prescalerMode;
            eightBitValue_ = LA_FOUR.eightBitValue;
            PORTC &= ~(1 << DDC6);
            TCCR2B |= (LA_FOUR.prescalerMode << CS20);
            OCR2A = LA_FOUR.eightBitValue;
            _delay_ms(QUARTER);
            TCCR2A &= ~(1 << COM2A1); // stop playing note;
            TCCR2A &= ~(1 << COM2A0);
            break;
    }
}

/**
 * \brief plays melody of the song Gucci Gang
 */
void Piezo::gucciGang() {
    
    playEighthNote(LA_THREE);
    playEighthNote(RE_THREE);
    playSixteenthNote(MI_THREE);
    playSixteenthNote(FA_THREE);
    playEighthNote(MI_THREE);
    playEighthNote(RE_THREE);
    playEighthNote(DO_THREE);
    
    playQuarterNote(LA_THREE);
    playEighthNote(LA_THREE);
    playEighthNote(RE_THREE);
    playSixteenthNote(MI_THREE);
    playSixteenthNote(FA_THREE);
    playEighthNote(MI_THREE);
    playEighthNote(RE_THREE);
    playQuarterNote(SO_THREE);
    
    playEighthNote(LA_THREE);
    playEighthNote(RE_THREE);
    playSixteenthNote(MI_THREE);
    playSixteenthNote(FA_THREE);
    playEighthNote(MI_THREE);
    playEighthNote(RE_THREE);
    playEighthNote(DO_THREE);
    
    playQuarterNote(LA_THREE);
    playEighthNote(LA_THREE);
    playEighthNote(RE_THREE);
    playSixteenthNote(MI_THREE);
    playSixteenthNote(FA_THREE);
    playEighthNote(MI_THREE);
    playEighthNote(RE_THREE);
    playEighthNote(SO_THREE);
    
    for(uint8_t i = 0; i < 12; i++) { // repetition of same note for 12 half-bars
        playEighthNote(MI_TWO);
        playEighthNote(LA_TWO);
        playEighthNote(DO_TWO);
        playEighthNote(LA_TWO);
    }
}

/**
 * \brief getter for frequency_
 * \return frequency_
 */
uint16_t Piezo::getFrequency() {
    
    return frequency_;
}
