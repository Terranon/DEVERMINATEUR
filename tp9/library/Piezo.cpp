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
void Piezo::playNote(uint8_t note) {
    
    TCCR2B &= ~(7 << CS20); // sets all bits to 0
    
    switch(note) {
        case LA_ONE:
            prescalerMode_ = 6;
            eightBitValue_ = LA_ONE;
            TCCR2B |= (6 << CS20);
            OCR2A = LA_ONE;
            break;
        case LASHARP_ONE:
            prescalerMode_ = 6;
            eightBitValue_ = LASHARP_ONE;
            TCCR2B |= (6 << CS20);
            OCR2A = LASHARP_ONE;
            break;
        case SI_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = SI_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = SI_ONE;
            break;
        case DO_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = DO_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = DO_ONE;
            break;
        case DOSHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = DOSHARP_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = DOSHARP_ONE;
            break;
        case RE_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = RE_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = RE_ONE;
            break;
        case RESHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = RESHARP_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = RESHARP_ONE;
            break;
        case MI_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = MI_ONEe;
            TCCR2B |= (5 << CS20);
            OCR2A = MI_ONE;
            break;
        case FA_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = FA_ONE;
            TCCR2B |= (5<< CS20);
            OCR2A = FA_ONE;
            break;
        case FASHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = FASHARP_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = FASHARP_ONE;
            break;
        case SO_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = SO_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = SO_ONE;
            break;
        case SOSHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = SOSHARP_ONE;
            TCCR2B |= (5 << CS20);
            OCR2A = SOSHARP_ONE;
            break;
        
            
        case LA_TWO:
            prescalerMode_ = 5;
            eightBitValue_ = LA_TWO;
            TCCR2B |= (5 << CS20);
            OCR2A = LA_TWO;
            break;
        case LASHARP_TWO:
            prescalerMode_ = 5;
            eightBitValue_ = LASHARP_TWO;
            TCCR2B |= (5 << CS20);
            OCR2A = LASHARP_TWO;
            break;
        case SI_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = SI_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = SI_TWO;
            break;
        case DO_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = DO_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = DO_TWO;
            break;
        case DOSHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = DOSHARP_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = DOSHARP_TWO;
            break;
        case RE_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = RE_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = RE_TWO;
            break;
        case RESHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = RESHARP_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = RESHARP_TWO;
            break;
        case MI_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = MI_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = MI_TWO;
            break;
        case FA_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = FA_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = FA_TWO;
            break;
        case FASHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = FASHARP_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = FASHARP_TWO;
            break;
        case SO_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = SO_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = SO_TWO;
            break;
        case SOSHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = SOSHARP_TWO;
            TCCR2B |= (4 << CS20);
            OCR2A = SOSHARP_TWO;
            break;
            
            
        case LA_THREE:
            prescalerMode_ = 4;
            eightBitValue_ = LA_THREE;
            TCCR2B |= (4 << CS20);
            OCR2A = LA_THREE;
            break;
        case LASHARP_THREE:
            prescalerMode_ = 4;
            eightBitValue_ = LASHARP_THREE;
            TCCR2B |= (4 << CS20);
            OCR2A = LASHARP_THREE;
            break;
        case SI_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = SI_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = SI_THREE;
            break;
        case DO_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = DO_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = DO_THREE;
            break;
        case DOSHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = DOSHARP_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = DOSHARP_THREE;
            break;
        case RE_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = RE_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = RE_THREE;
            break;
        case RESHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = RESHARP_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = RESHARP_THREE;
            break;
        case MI_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = MI_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = MI_THREE;
            break;
        case FA_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = FA_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = FA_THREE;
            break;
        case FASHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = FASHARP_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = FASHARP_THREE;
            break;
        case SO_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = SO_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = SO_THREE;
            break;
        case SOSHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = SOSHARP_THREE;
            TCCR2B |= (3 << CS20);
            OCR2A = SOSHARP_THREE;
            break;
            
            
        case LA_FOUR:
            prescalerMode_ = 3;
            eightBitValue_ = LA_FOUR;
            TCCR2B |= (3 << CS20);
            OCR2A = LA_FOUR;
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
