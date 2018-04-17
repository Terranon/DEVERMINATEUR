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
Piezo::Piezo() :
		prescalerMode_(0),
        eightBitValue_(0) 
        {	  
        DDRD |= (1 << DDD6); // sets PORTC6 to output
        DDRD |= (1 << DDD7); // sets PORTC7 to output
        
        PORTD &= ~(1 << PORTD6); // sets output value of PORTC6 to zero
        
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
            eightBitValue_ = 141;
            TCCR2B |= (6 << CS20);
            OCR2A = 141;
            break;
        case LASHARP_ONE:
            prescalerMode_ = 6;
            eightBitValue_ = 133;
            TCCR2B |= (6 << CS20);
            OCR2A = 133;
            break;
        case SI_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 252;
            TCCR2B |= (5 << CS20);
            OCR2A = 252;
            break;
        case DO_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 238;
            TCCR2B |= (5 << CS20);
            OCR2A = 238;
            break;
        case DOSHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 224;
            TCCR2B |= (5 << CS20);
            OCR2A = 224;
            break;
        case RE_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 212;
            TCCR2B |= (5 << CS20);
            OCR2A = 212;
            break;
        case RESHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 200;
            TCCR2B |= (5 << CS20);
            OCR2A = 200;
            break;
        case MI_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 189;
            TCCR2B |= (5 << CS20);
            OCR2A = 189;
            break;
        case FA_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 178;
            TCCR2B |= (5<< CS20);
            OCR2A = 178;
            break;
        case FASHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 168;
            TCCR2B |= (5 << CS20);
            OCR2A = 168;
            break;
        case SO_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 158;
            TCCR2B |= (5 << CS20);
            OCR2A = 158;
            break;
        case SOSHARP_ONE:
            prescalerMode_ = 5;
            eightBitValue_ = 149;
            TCCR2B |= (5 << CS20);
            OCR2A = 149;
            break;
        
            
        case LA_TWO:
            prescalerMode_ = 5;
            eightBitValue_ = 141;
            TCCR2B |= (5 << CS20);
            OCR2A = 141;
            break;
        case LASHARP_TWO:
            prescalerMode_ = 5;
            eightBitValue_ = 133;
            TCCR2B |= (5 << CS20);
            OCR2A = 133;
            break;
        case SI_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 252;
            TCCR2B |= (4 << CS20);
            OCR2A = 252;
            break;
        case DO_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 238;
            TCCR2B |= (4 << CS20);
            OCR2A = 238;
            break;
        case DOSHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 224;
            TCCR2B |= (4 << CS20);
            OCR2A = 224;
            break;
        case RE_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 212;
            TCCR2B |= (4 << CS20);
            OCR2A = 212;
            break;
        case RESHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 200;
            TCCR2B |= (4 << CS20);
            OCR2A = 200;
            break;
        case MI_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 189;
            TCCR2B |= (4 << CS20);
            OCR2A = 189;
            break;
        case FA_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 178;
            TCCR2B |= (4 << CS20);
            OCR2A = 178;
            break;
        case FASHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 168;
            TCCR2B |= (4 << CS20);
            OCR2A = 168;
            break;
        case SO_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 158;
            TCCR2B |= (4 << CS20);
            OCR2A = 158;
            break;
        case SOSHARP_TWO:
            prescalerMode_ = 4;
            eightBitValue_ = 149;
            TCCR2B |= (4 << CS20);
            OCR2A = 149;
            break;
            
            
        case LA_THREE:
            prescalerMode_ = 4;
            eightBitValue_ = 141;
            TCCR2B |= (4 << CS20);
            OCR2A = 141;
            break;
        case LASHARP_THREE:
            prescalerMode_ = 4;
            eightBitValue_ = 133;
            TCCR2B |= (4 << CS20);
            OCR2A = 133;
            break;
        case SI_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 252;
            TCCR2B |= (3 << CS20);
            OCR2A = 252;
            break;
        case DO_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 238;
            TCCR2B |= (3 << CS20);
            OCR2A = 238;
            break;
        case DOSHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 224;
            TCCR2B |= (3 << CS20);
            OCR2A = 224;
            break;
        case RE_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 212;
            TCCR2B |= (3 << CS20);
            OCR2A = 212;
            break;
        case RESHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 200;
            TCCR2B |= (3 << CS20);
            OCR2A = 200;
            break;
        case MI_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 189;
            TCCR2B |= (3 << CS20);
            OCR2A = 189;
            break;
        case FA_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 178;
            TCCR2B |= (3 << CS20);
            OCR2A = 178;
            break;
        case FASHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 168;
            TCCR2B |= (3 << CS20);
            OCR2A = 168;
            break;
        case SO_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 158;
            TCCR2B |= (3 << CS20);
            OCR2A = 158;
            break;
        case SOSHARP_THREE:
            prescalerMode_ = 3;
            eightBitValue_ = 149;
            TCCR2B |= (3 << CS20);
            OCR2A = 149;
            break;
            
            
        case LA_FOUR:
            prescalerMode_ = 3;
            eightBitValue_ = 141;
            TCCR2B |= (3 << CS20);
            OCR2A = 141;
            break;
    }
}

/**
 * \brief plays success sound from zelda
 */
void Piezo::tanaNaNaaa(){
    playNote(LA_THREE);
    _delay_ms(200);
    playNote(LASHARP_THREE);
    _delay_ms(200);
    playNote(SI_THREE);
    _delay_ms(200);
    playNote(DO_THREE);
    _delay_ms(500);
    stopPlayingNote();
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
