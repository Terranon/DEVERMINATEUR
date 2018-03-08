/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.h
 * Description: Simplify the use of a Piezo
 * Version: 1.0
\******************************************************************************/

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/delay.h>

#ifndef PIEZO_H
#define PIEZO_H
    
class Piezo {
public:
    
    /**
    * \brief constructor for the Led; the DDRC register will be set to enable
    *        output on the appropriate pins
    * \param freq sets begining frequency of Piezo
    *             ; uses preset notes in chromatic scale
    *                LA to SOSHARP
    * \return a Piezo
    */
    Piezo(uint16_t freq);
    
    /**
    * \brief destructor for the Piezo
    */
    ~Piezo();

    /**
    * \brief sets frequency_ to specified frequency
    * \param freq frequency that frequency_ will be set to
    *                ; uses preset notes in chromatic scale
    *                LA to SOSHARP
    */
    void setFrequency(uint16_t freq);

    /**
    * \brief plays a note for one milisecond
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playFastNote(uint16_t note);

    /**
    * \brief plays a note for one 250 miliseconds or one sixteenth note
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playSixteenthNote(uint16_t note);

    /**
    * \brief plays a note for one 500 miliseconds or one eighth note
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playEighthNote(uint16_t note);

    /**
    * \brief plays a note for one 1000 miliseconds or one quarter note
    * \param freq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void playQuarterNote(uint16_t note);

    /**
    * \brief plays melody of the song Gucci Gang
    */
    void gucciGang();

    /**
    * \brief getter for frequency_
    * \return frequency_
    */
    uint16_t getFrequency();
    
    /**
     * \brief These constants define the periods of the delays in microseconds
     */
    static const uint16_t LA = 4545;
    static const uint16_t LASHARP = 4291;
    static const uint16_t SI = 4048;
    static const uint16_t DO = 3824;
    static const uint16_t DOSHARP = 3610;
    static const uint16_t RE = 3407;
    static const uint16_t RESHARP = 3215;
    static const uint16_t MI = 3044;
    static const uint16_t FA = 2865;
    static const uint16_t FASHARP = 2702;
    static const uint16_t SO = 2551;
    static const uint16_t SOSHARP = 2408;
    
    /**
     * \brief These constants define the lengths of the tones in miliseconds
     */
    static const uint16_t QUARTER = 1000;
    static const uint16_t EIGHTH = 500;
    static const uint16_t SIXTEENTH = 250;
    static const uint16_t FAST = 1;
    
    /** 
     * \brief This constant defines the polarity of the amplitude of the piezo
     */
    static const uint8_t posAmplitude = 1;
    
private:

    uint16_t frequency_;
};
    
#endif // PIEZO_H
