/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        Piezo.h
 * Description: Simplify the use of a Piezo
 * Version: 1.0
\******************************************************************************/

#include <avr/io.h>
#include <avr/delay.h>

#ifndef PIEZO_H
#define PIEZO_H
    
class Piezo {
public:
    
    /**
    * \brief constructor for the Led; the DDRC register will be set to enable
    *        output on the appropriate pins
    * \param pwmFreq sets begining frequency of the pwm in Hz
    * \return a Piezo
    */
    Piezo(uint16_t pwmFreq);
    
    /**
    * \brief destructor for the Piezo
    */
    Piezo::~Piezo();

    /**
    * \brief sets pwmFrequency_ to specified frequency
    * \param pwmFreq frequency that pwmFrequency_ will be set to
    *                ; can use preset notes in chromatic scale
    *                LA to SOSHARP
    */
    void Piezo::setPwmFrequency(uint16_t pwmFreq);

    /**
    * \brief plays tone set in pwmFrequency_ for 500 miliseconds
    */
    void Piezo::playTone();

    /**
    * \brief plays a note for one milisecond
    * \param pwmFreq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void Piezo::playFastNote(uint16_t pwmFreq);

    /**
    * \brief plays a note for one 250 miliseconds or one sixteenth note
    * \param pwmFreq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void Piezo::playSixteenthNote(uint16_t pwmFreq);

    /**
    * \brief plays a note for one 500 miliseconds or one eighth note
    * \param pwmFreq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void Piezo::playEighthNote(uint16_t pwmFreq);

    /**
    * \brief plays a note for one 1000 miliseconds or one quarter note
    * \param pwmFreq frequency that the Piezo will play; can use preset notes
    *                in chromatic scale LA to SOSHARP
    */
    void Piezo::playQuarterNote(uint16_t pwmFreq);

    /**
    * \brief plays melody of the song Gucci Gang
    */
    void Piezo::gucciGang();

    /**
    * \brief plays a vroom vroom sound
    */
    void Piezo::vroomVroom();

    /**
    * \brief getter for pwmFrequency_
    * \return pwmFrequency_
    */
    uint16_t Piezo::getPwmFrequency();
    
    /** 
     * \brief These constants defines the frequencies of pwmFrequency_
     */
    static const uint16_t LA = 440;
    static const uint16_t LASHARP = 466;
    static const uint16_t SI = 494;
    static const uint16_t DO = 523;
    static const uint16_t DOSHARP = 554;
    static const uint16_t RE = 587;
    static const uint16_t RESHARP = 622;
    static const uint16_t MI = 659;
    static const uint16_t FA = 698;
    static const uint16_t FASHARP = 740;
    static const uint16_t SO = 784;
    static const uint16_t SOSHARP = 831;
    
    /** 
     * \brief These constants defines the polarity of the amplitude of the piezo
     */
    static const uint8_t posAmplitude = 1;
    static const uint8_t negAmplitude = 2;
    
private:

    uint16_t pwmFrequency_;
};
    
#endif // PIEZO_H
