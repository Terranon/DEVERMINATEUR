/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.h
 * Description: Simplify the use of a Piezo
 * Version: 2.0
\******************************************************************************/

#ifndef PIEZO_H
#define PIEZO_H

#include <avr/io.h>
#include <util/delay.h>
    
class Piezo {
public:
    
    /**
     * \brief These constants define the respective value to set OCR2A to
     *        the appropriate note
     */    
    static const uint8_t LA_ONE = 141;
    static const uint8_t LASHARP_ONE = 133;
    static const uint8_t SI_ONE = 252;
    static const uint8_t DO_ONE = 238;
    static const uint8_t DOSHARP_ONE = 224;
    static const uint8_t RE_ONE = 212;
    static const uint8_t RESHARP_ONE = 200;
    static const uint8_t MI_ONE = 189;
    static const uint8_t FA_ONE = 178;
    static const uint8_t FASHARP_ONE = 168;
    static const uint8_t SO_ONE = 158;
    static const uint8_t SOSHARP_ONE = 149;
    
    static const uint8_t LA_TWO = 141;
    static const uint8_t LASHARP_TWO = 133;
    static const uint8_t SI_TWO = 252;
    static const uint8_t DO_TWO = 238;
    static const uint8_t DOSHARP_TWO = 224;
    static const uint8_t RE_TWO = 212;
    static const uint8_t RESHARP_TWO = 200;
    static const uint8_t MI_TWO = 189;
    static const uint8_t FA_TWO = 178;
    static const uint8_t FASHARP_TWO = 168;
    static const uint8_t SO_TWO = 158;
    static const uint8_t SOSHARP_TWO = 149;
    
    static const uint8_t LA_THREE = 141;
    static const uint8_t LASHARP_THREE = 133;
    static const uint8_t SI_THREE = 252;
    static const uint8_t DO_THREE = 238;
    static const uint8_t DOSHARP_THREE = 224;
    static const uint8_t RE_THREE = 212;
    static const uint8_t RESHARP_THREE = 200;
    static const uint8_t MI_THREE = 189;
    static const uint8_t FA_THREE = 178;
    static const uint8_t FASHARP_THREE = 168;
    static const uint8_t SO_THREE = 158;
    static const uint8_t SOSHARP_THREE 149;
    
    static const uint8_t LA_FOUR = 141;
    
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
    void playNote(Note note);

    /**
    * \brief plays melody of the song Gucci Gang
    */
    void gucciGang();
    
    /**
    * \brief plays melody of the song Africa by Toto
    */
    void africaToto();
    
    
private:

    uint8_t prescalerMode_;
    uint8_t eightBitValue_;
};
    
#endif // PIEZO_H
