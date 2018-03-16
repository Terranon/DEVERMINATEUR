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
    * \brief plays a note for one milisecond
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playFastNote(Note note);

    /**
    * \brief plays a note for one 250 miliseconds or one sixteenth note
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playSixteenthNote(Note note);

    /**
    * \brief plays a note for one 500 miliseconds or one eighth note
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playEighthNote(Note note);

    /**
    * \brief plays a note for one 1000 miliseconds or one quarter note
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playQuarterNote(Note note);

    /**
    * \brief plays melody of the song Gucci Gang
    */
    void gucciGang();
    
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
    static const Note DOSHARP_ONE = {7,27};
    static const Note RE_ONE = {5,212};
    static const Note RESHARP_ONE = {7,24};
    static const Note MI_ONE = {6,94};
    static const Note FA_ONE = {5,178};
    static const Note FASHARP_ONE = {5,168};
    static const Note SO_ONE = {7,19};
    static const Note SOSHARP_ONE = {7,18};
    
    static const Note LA_TWO = {6,70};
    static const Note LASHARP_TWO = {6,68};
    static const Note SI_TWO = {4,252}
    static const Note DO_TWO = {7,14};
    static const Note DOSHARP_TWO = {7,13};
    static const Note RE_TWO = {4,212};
    static const Note RESHARP_TWO = {4,200};
    static const Note MI_TWO = {7,11};
    static const Note FA_TWO = {4,178};
    static const Note FASHARP_TWO = {4,168};
    static const Note SO_TWO = {7,9};
    static const Note SOSHARP_TWO = {5,74};
    
    static const Note LA_THREE = {5,70};
    static const Note LASHARP_THREE = {5,66};
    static const Note SI_THREE = {7,7};
    static const Note DO_THREE = {3,238};
    static const Note DOSHARP_THREE = {7,6};
    static const Note RE_THREE = {3,212};
    static const Note RESHARP_THREE = {6,24};
    static const Note MI_THREE = {7,5};
    static const Note FA_THREE = {3,178};
    static const Note FASHARP_THREE = {3,168};
    static const Note SO_THREE = {7,4};
    static const Note SOSHARP_THREE {6,18};
    
    static const Note LA_FOUR = {5,71};
    
    /**
     * \brief These constants define the lengths of the tones in miliseconds
     */
    static const uint16_t QUARTER = 1000;
    static const uint16_t EIGHTH = 500;
    static const uint16_t SIXTEENTH = 250;
    static const uint16_t FAST = 10;
    
private:

    uint8_t prescalerMode_;
    uint8_t eightBitValue_;
};
    
#endif // PIEZO_H
