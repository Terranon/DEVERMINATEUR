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
    * \brief constructor for the Piezo; the DDRB register will 
    *        be set to enable output
    * \param pwmFreq sets begining frequency of the pwm in Hz
    * \return an Led
    */
    Piezo(uint16_t pwmFreq);
    
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
    
private:

};
    
#endif // LED_H
