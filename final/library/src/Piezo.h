/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.h
 * Description: Simplify the use of a Piezo
 * Version: 2.0
\******************************************************************************/

#ifndef PIEZO_H
#define PIEZO_H
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
    
class Piezo {
public:
    
    /**
     * \brief These constants define the respective value to set OCR2A to
     *        the appropriate note
     */    
    static const uint8_t LA_ONE = 45;
    static const uint8_t LASHARP_ONE = 46;
    static const uint8_t SI_ONE = 47;
    static const uint8_t DO_ONE = 48;
    static const uint8_t DOSHARP_ONE = 49;
    static const uint8_t RE_ONE = 50;
    static const uint8_t RESHARP_ONE = 51;
    static const uint8_t MI_ONE = 52;
    static const uint8_t FA_ONE = 53;
    static const uint8_t FASHARP_ONE = 54;
    static const uint8_t SO_ONE = 55;
    static const uint8_t SOSHARP_ONE = 56;
    
    static const uint8_t LA_TWO = 57;
    static const uint8_t LASHARP_TWO = 58;
    static const uint8_t SI_TWO = 59;
    static const uint8_t DO_TWO = 60;
    static const uint8_t DOSHARP_TWO = 61;
    static const uint8_t RE_TWO = 62;
    static const uint8_t RESHARP_TWO = 63;
    static const uint8_t MI_TWO = 64;
    static const uint8_t FA_TWO = 65;
    static const uint8_t FASHARP_TWO = 66;
    static const uint8_t SO_TWO = 67;
    static const uint8_t SOSHARP_TWO = 68;
    
    static const uint8_t LA_THREE = 69;
    static const uint8_t LASHARP_THREE = 70;
    static const uint8_t SI_THREE = 71;
    static const uint8_t DO_THREE = 72;
    static const uint8_t DOSHARP_THREE = 73;
    static const uint8_t RE_THREE = 74;
    static const uint8_t RESHARP_THREE = 75;
    static const uint8_t MI_THREE = 76;
    static const uint8_t FA_THREE = 77;
    static const uint8_t FASHARP_THREE = 78;
    static const uint8_t SO_THREE = 79;
    static const uint8_t SOSHARP_THREE = 80;
    
    static const uint8_t LA_FOUR = 81;

    
    /**
    * \brief constructor for the Led; the DDRC register will be set to enable
    *        output on the appropriate pins
    * \param freq sets begining frequency of Piezo
    *             ; uses preset notes in chromatic scale
    *                LA to LA
    * \return a Piezo
    */
    Piezo();
    
    /**
    * \brief destructor for the Piezo
    */
    ~Piezo();

    /**
    * \brief stops the playback of a note
    */
    void stopPlayingNote();

    /**
    * \brief starts the playback of a note
    * \param note frequency that the Piezo will play; can use preset notes
    *             in chromatic scale LA_ONE:110Hz to LA_FOUR:880Hz
    */
    void playNote(uint8_t note);
    
    /**
    * \brief plays success sound from zelda
    */
    void tanaNaNaaa();

    /**
    * \brief plays melody of the song Gucci Gang
    */
    void gucciGang();
    
private:

    uint8_t prescalerMode_;
    uint8_t eightBitValue_;
};
    
#endif // PIEZO_H
