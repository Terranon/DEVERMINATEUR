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
    void Piezo::stopPlayingNote();

    /**
    * \brief starts the playback of a note
    * \param note frequency that the Piezo will play; can use preset notes
    *             in chromatic scale LA_ONE:110Hz to LA_FOUR:880Hz
    */
    void Piezo::playNote(Note note);

    /**
    * \brief plays melody of the song Gucci Gang
    */
    void gucciGang();
    
    /**
    * \brief plays melody of the song Africa by Toto
    */
    void Piezo::africaToto();
    
    /**
     * \brief this struct represents a note with appropriate values
     *        using CTC mode for timer2
     */
    struct Note{
        uint8_t prescalerMode;
        uint8_t eightBitValue;
    }
    
    /**
     * \brief These constants define the respective value to set OCR2A to
     *        the appropriate note
     */    
    static const Note LA_ONE = {6,141};
    static const Note LASHARP_ONE = {6,133};
    static const Note SI_ONE = {5,252};
    static const Note DO_ONE = {5,238};
    static const Note DOSHARP_ONE = {5,224};
    static const Note RE_ONE = {5,212};
    static const Note RESHARP_ONE = {5,200};
    static const Note MI_ONE = {5,189};
    static const Note FA_ONE = {5,178};
    static const Note FASHARP_ONE = {5,168};
    static const Note SO_ONE = {5,158};
    static const Note SOSHARP_ONE = {5,149};
    
    static const Note LA_TWO = {5,141};
    static const Note LASHARP_TWO = {5,133};
    static const Note SI_TWO = {4,252}
    static const Note DO_TWO = {4,238};
    static const Note DOSHARP_TWO = {4,224};
    static const Note RE_TWO = {4,212};
    static const Note RESHARP_TWO = {4,200};
    static const Note MI_TWO = {4,189};
    static const Note FA_TWO = {4,178};
    static const Note FASHARP_TWO = {4,168};
    static const Note SO_TWO = {4,158};
    static const Note SOSHARP_TWO = {4,149};
    
    static const Note LA_THREE = {4,141};
    static const Note LASHARP_THREE = {4,133};
    static const Note SI_THREE = {3,252};
    static const Note DO_THREE = {3,238};
    static const Note DOSHARP_THREE = {3,224};
    static const Note RE_THREE = {3,212};
    static const Note RESHARP_THREE = {3,200};
    static const Note MI_THREE = {3,189};
    static const Note FA_THREE = {3,178};
    static const Note FASHARP_THREE = {3,168};
    static const Note SO_THREE = {3,158};
    static const Note SOSHARP_THREE {3,149};
    
    static const Note LA_FOUR = {3,141};
    
private:

    uint8_t prescalerMode_;
    uint8_t eightBitValue_;
};
    
#endif // PIEZO_H
