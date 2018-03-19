/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.cpp
 * Description: Simplify the use of a Piezo
 * Version: 2.1
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
 * \brief stops the playback of a note
 */
void Piezo::stopPlayingNote() {
    
    TCCR2B &= ~(7 << CS20); // no clock source timer stopped
}

/**
 * \brief starts the playback of a note
 * \param note frequency that the Piezo will play; can use preset notes
 *             in chromatic scale LA_ONE:110Hz to LA_FOUR:880Hz
 */
void Piezo::playNote(Note note) {
    
    TCCR2B &= ~(7 << CS20); // sets all bits to 0
    
    switch(note) {
        case LA_ONE:
            prescalerMode_ = LA_ONE.prescalerMode;
            eightBitValue_ = LA_ONE.eightBitValue;
            TCCR2B |= (LA_ONE.prescalerMode << CS20);
            OCR2A = LA_ONE.eightBitValue;
            break;
        case LASHARP_ONE:
            prescalerMode_ = LASHARP_ONE.prescalerMode;
            eightBitValue_ = LASHARP_ONE.eightBitValue;
            TCCR2B |= (LASHARP_ONE.prescalerMode << CS20);
            OCR2A = LASHARP_ONE.eightBitValue;
            break;
        case SI_ONE:
            prescalerMode_ = SI_ONE.prescalerMode;
            eightBitValue_ = SI_ONE.eightBitValue;
            TCCR2B |= (SI_ONE.prescalerMode << CS20);
            OCR2A = SI_ONE.eightBitValue;
            break;
        case DO_ONE:
            prescalerMode_ = DO_ONE.prescalerMode;
            eightBitValue_ = DO_ONE.eightBitValue;
            TCCR2B |= (DO_ONE.prescalerMode << CS20);
            OCR2A = DO_ONE.eightBitValue;
            break;
        case DOSHARP_ONE:
            prescalerMode_ = DOSHARP_ONE.prescalerMode;
            eightBitValue_ = DOSHARP_ONE.eightBitValue;
            TCCR2B |= (DOSHARP_ONE.prescalerMode << CS20);
            OCR2A = DOSHARP_ONE.eightBitValue;
            break;
        case RE_ONE:
            prescalerMode_ = RE_ONE.prescalerMode;
            eightBitValue_ = RE_ONE.eightBitValue;
            TCCR2B |= (RE_ONE.prescalerMode << CS20);
            OCR2A = RE_ONE.eightBitValue;
            break;
        case RESHARP_ONE:
            prescalerMode_ = RESHARP_ONE.prescalerMode;
            eightBitValue_ = RESHARP_ONE.eightBitValue;
            TCCR2B |= (RESHARP_ONE.prescalerMode << CS20);
            OCR2A = RESHARP_ONE.eightBitValue;
            break;
        case MI_ONE:
            prescalerMode_ = MI_ONE.prescalerMode;
            eightBitValue_ = MI_ONE.eightBitValue;
            TCCR2B |= (MI_ONE.prescalerMode << CS20);
            OCR2A = MI_ONE.eightBitValue;
            break;
        case FA_ONE:
            prescalerMode_ = FA_ONE.prescalerMode;
            eightBitValue_ = FA_ONE.eightBitValue;
            TCCR2B |= (FA_ONE.prescalerMode << CS20);
            OCR2A = FA_ONE.eightBitValue;
            break;
        case FASHARP_ONE:
            prescalerMode_ = FASHARP_ONE.prescalerMode;
            eightBitValue_ = FASHARP_ONE.eightBitValue;
            TCCR2B |= (FASHARP_ONE.prescalerMode << CS20);
            OCR2A = FASHARP_ONE.eightBitValue;
            break;
        case SO_ONE:
            prescalerMode_ = SO_ONE.prescalerMode;
            eightBitValue_ = SO_ONE.eightBitValue;
            TCCR2B |= (SO_ONE.prescalerMode << CS20);
            OCR2A = SO_ONE.eightBitValue;
            break;
        case SOSHARP_ONE:
            prescalerMode_ = SOSHARP_ONE.prescalerMode;
            eightBitValue_ = SOSHARP_ONE.eightBitValue;
            TCCR2B |= (SOSHARP_ONE.prescalerMode << CS20);
            OCR2A = SOSHARP_ONE.eightBitValue;
            break;
        
            
        case LA_TWO:
            prescalerMode_ = LA_TWO.prescalerMode;
            eightBitValue_ = LA_TWO.eightBitValue;
            TCCR2B |= (LA_TWO.prescalerMode << CS20);
            OCR2A = LA_TWO.eightBitValue;
            break;
        case LASHARP_TWO:
            prescalerMode_ = LASHARP_TWO.prescalerMode;
            eightBitValue_ = LASHARP_TWO.eightBitValue;
            TCCR2B |= (LASHARP_TWO.prescalerMode << CS20);
            OCR2A = LASHARP_TWO.eightBitValue;
            break;
        case SI_TWO:
            prescalerMode_ = SI_TWO.prescalerMode;
            eightBitValue_ = SI_TWO.eightBitValue;
            TCCR2B |= (SI_TWO.prescalerMode << CS20);
            OCR2A = SI_TWO.eightBitValue;
            break;
        case DO_TWO:
            prescalerMode_ = DO_TWO.prescalerMode;
            eightBitValue_ = DO_TWO.eightBitValue;
            TCCR2B |= (DO_TWO.prescalerMode << CS20);
            OCR2A = DO_TWO.eightBitValue;
            break;
        case DOSHARP_TWO:
            prescalerMode_ = DOSHARP_TWO.prescalerMode;
            eightBitValue_ = DOSHARP_TWO.eightBitValue;
            TCCR2B |= (DOSHARP_TWO.prescalerMode << CS20);
            OCR2A = DOSHARP_TWO.eightBitValue;
            break;
        case RE_TWO:
            prescalerMode_ = RE_TWO.prescalerMode;
            eightBitValue_ = RE_TWO.eightBitValue;
            TCCR2B |= (RE_TWO.prescalerMode << CS20);
            OCR2A = RE_TWO.eightBitValue;
            break;
        case RESHARP_TWO:
            prescalerMode_ = RESHARP_TWO.prescalerMode;
            eightBitValue_ = RESHARP_TWO.eightBitValue;
            TCCR2B |= (RESHARP_TWO.prescalerMode << CS20);
            OCR2A = RESHARP_TWO.eightBitValue;
            break;
        case MI_TWO:
            prescalerMode_ = MI_TWO.prescalerMode;
            eightBitValue_ = MI_TWO.eightBitValue;
            TCCR2B |= (MI_TWO.prescalerMode << CS20);
            OCR2A = MI_TWO.eightBitValue;
            break;
        case FA_TWO:
            prescalerMode_ = FA_TWO.prescalerMode;
            eightBitValue_ = FA_TWO.eightBitValue;
            TCCR2B |= (FA_TWO.prescalerMode << CS20);
            OCR2A = FA_TWO.eightBitValue;
            break;
        case FASHARP_TWO:
            prescalerMode_ = FASHARP_TWO.prescalerMode;
            eightBitValue_ = FASHARP_TWO.eightBitValue;
            TCCR2B |= (FASHARP_TWO.prescalerMode << CS20);
            OCR2A = FASHARP_TWO.eightBitValue;
            break;
        case SO_TWO:
            prescalerMode_ = SO_TWO.prescalerMode;
            eightBitValue_ = SO_TWO.eightBitValue;
            TCCR2B |= (SO_TWO.prescalerMode << CS20);
            OCR2A = SO_TWO.eightBitValue;
            break;
        case SOSHARP_TWO:
            prescalerMode_ = SOSHARP_TWO.prescalerMode;
            eightBitValue_ = SOSHARP_TWO.eightBitValue;
            TCCR2B |= (SOSHARP_TWO.prescalerMode << CS20);
            OCR2A = SOSHARP_TWO.eightBitValue;
            break;
            
            
        case LA_THREE:
            prescalerMode_ = LA_THREE.prescalerMode;
            eightBitValue_ = LA_THREE.eightBitValue;
            TCCR2B |= (LA_THREE.prescalerMode << CS20);
            OCR2A = LA_THREE.eightBitValue;
            break;
        case LASHARP_THREE:
            prescalerMode_ = LASHARP_THREE.prescalerMode;
            eightBitValue_ = LASHARP_THREE.eightBitValue;
            TCCR2B |= (LASHARP_THREE.prescalerMode << CS20);
            OCR2A = LASHARP_THREE.eightBitValue;
            break;
        case SI_THREE:
            prescalerMode_ = SI_THREE.prescalerMode;
            eightBitValue_ = SI_THREE.eightBitValue;
            TCCR2B |= (SI_THREE.prescalerMode << CS20);
            OCR2A = SI_THREE.eightBitValue;
            break;
        case DO_THREE:
            prescalerMode_ = DO_THREE.prescalerMode;
            eightBitValue_ = DO_THREE.eightBitValue;
            TCCR2B |= (DO_THREE.prescalerMode << CS20);
            OCR2A = DO_THREE.eightBitValue;
            break;
        case DOSHARP_THREE:
            prescalerMode_ = DOSHARP_THREE.prescalerMode;
            eightBitValue_ = DOSHARP_THREE.eightBitValue;
            TCCR2B |= (DOSHARP_THREE.prescalerMode << CS20);
            OCR2A = DOSHARP_THREE.eightBitValue;
            break;
        case RE_THREE:
            prescalerMode_ = RE_THREE.prescalerMode;
            eightBitValue_ = RE_THREE.eightBitValue;
            TCCR2B |= (RE_THREE.prescalerMode << CS20);
            OCR2A = RE_THREE.eightBitValue;
            break;
        case RESHARP_THREE:
            prescalerMode_ = RESHARP_THREE.prescalerMode;
            eightBitValue_ = RESHARP_THREE.eightBitValue;
            TCCR2B |= (RESHARP_THREE.prescalerMode << CS20);
            OCR2A = RESHARP_THREE.eightBitValue;
            break;
        case MI_THREE:
            prescalerMode_ = MI_THREE.prescalerMode;
            eightBitValue_ = MI_THREE.eightBitValue;
            TCCR2B |= (MI_THREE.prescalerMode << CS20);
            OCR2A = MI_THREE.eightBitValue;
            break;
        case FA_THREE:
            prescalerMode_ = FA_THREE.prescalerMode;
            eightBitValue_ = FA_THREE.eightBitValue;
            TCCR2B |= (FA_THREE.prescalerMode << CS20);
            OCR2A = FA_THREE.eightBitValue;
            break;
        case FASHARP_THREE:
            prescalerMode_ = FASHARP_THREE.prescalerMode;
            eightBitValue_ = FASHARP_THREE.eightBitValue;
            TCCR2B |= (FASHARP_THREE.prescalerMode << CS20);
            OCR2A = FASHARP_THREE.eightBitValue;
            break;
        case SO_THREE:
            prescalerMode_ = SO_THREE.prescalerMode;
            eightBitValue_ = SO_THREE.eightBitValue;
            TCCR2B |= (SO_THREE.prescalerMode << CS20);
            OCR2A = SO_THREE.eightBitValue;
            break;
        case SOSHARP_THREE:
            prescalerMode_ = SOSHARP_THREE.prescalerMode;
            eightBitValue_ = SOSHARP_THREE.eightBitValue;
            TCCR2B |= (SOSHARP_THREE.prescalerMode << CS20);
            OCR2A = SOSHARP_THREE.eightBitValue;
            break;
            
            
        case LA_FOUR:
            prescalerMode_ = LA_FOUR.prescalerMode;
            eightBitValue_ = LA_FOUR.eightBitValue;
            TCCR2B |= (LA_FOUR.prescalerMode << CS20);
            OCR2A = LA_FOUR.eightBitValue;
            break;
    }
}

/**
 * \brief plays melody of the song Gucci Gang
 */
void Piezo::gucciGang() {
    
    playNote(LA_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(MI_THREE);
    _delay_ms(250);
    playNote(FA_THREE);
    _delay_ms(250);
    playNote(MI_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(DO_THREE);
    _delay_ms(500);
    
    playNote(LA_THREE);
    _delay_ms(1000);
    playNote(LA_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(MI_THREE);
    _delay_ms(250);
    playNote(FA_THREE);
    _delay_ms(250);
    playNote(MI_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(SO_THREE);
    _delay_ms(1000);
    
    playNote(LA_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(MI_THREE);
    _delay_ms(250);
    playNote(FA_THREE);
    _delay_ms(250);
    playNote(MI_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(DO_THREE);
    _delay_ms(500);
    
    playNote(LA_THREE);
    _delay_ms(1000);
    playNote(LA_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(MI_THREE);
    _delay_ms(250);
    playNote(FA_THREE);
    _delay_ms(250);
    playNote(MI_THREE);
    _delay_ms(500);
    playNote(RE_THREE);
    _delay_ms(500);
    playNote(SO_THREE);
    _delay_ms(500);
    
    for(uint8_t i = 0; i < 12; i++) { // repetition of same note for 12 half-bars
        playNote(MI_TWO);
        _delay_ms(500);
        playNote(LA_TWO);
        _delay_ms(500);
        playNote(DO_TWO);
        _delay_ms(500);
        playNote(LA_TWO);
        _delay_ms(500);
    }
}

/**
 * \brief plays melody of the song Africa by Toto
 */
void Piezo::africaToto() {
    
    
    for(int i = 0; i < 2; i++) {
        playNote(LA_ONE);
        _delay_ms(612);
        playNote(LA_ONE);
        _delay_ms(612);
        stopPlayingNote();
        _delay_ms(612);
        playNote(LA_ONE);
        _delay_ms(612);
        stopPlayingNote();
        _delay_ms(612);
        playNote(LA_ONE);
        _delay_ms(612);
        stopPlayingNote();
        _delay_ms(612);
        playNote(LA_ONE);
        _delay_ms(612);
        
        playNote(LA_ONE);
        _delay_ms(612);
        stopPlayingNote;
        _delay_ms(612);
        playNote(LA_ONE);
        _delay_ms(612);
        stopPlayingNote();
        _delay_ms(612);
        playNote(SOSHARP_ONE);
        _delay_ms(1225);
        playNote(FASHARP_TWO);
        _delay_ms(612);
        playNote(MI_TWO);
        _delay_ms(612);
        
        playNote(DOSHARP_TWO);
        _delay_ms(612);
        playNote(MI_TWO);
        _delay_ms(612);
        playNote(DOSHARP_TWO);
        _delay_ms(612);
        playNote(FASHARP_TWO);
        _delay_ms(612);
        stopPlayingNote();
        _delay_ms(612);
        playNote(MI_TWO);
        _delay_ms(612);
        playNote(DOSHARP_TWO);
        _delay_ms(612);
        playNote(MI_TWO);
        _delay_ms(612);
        
        playNote(FASHARP_TWO);
        _delay_ms(612);
        playNote(MI_TWO);
        _delay_ms(612);
        playNote(DOSHARP_TWO);
        _delay_ms(612);
        playNote(SI_TWO);
        _delay_ms(612);
        playNote(DOSHARP_TWO):
        _delay_ms(612);
        playNote(MI_TWO);
        _delay_ms(612);
        playNote(DOSHARP_TWO);
        _delay_ms(612);
        stopPlayingNote();
        _delay_ms(612);
    }
}
