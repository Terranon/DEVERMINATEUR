/*****************************************************************************\
 * Author:      Jean-Raphael Matte
 * Name:        Timer.h
 * Description: General purpose 16 bit timer/counter
 * Version: 1.0
\******************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

class Timer {
public:
    
    /**
     * \brief Initializes the registers for the Timer/Counter1
     * \return a Timer, stopped
     */
    Timer();
    
    /**
     * \brief Destructor: Stop the timer and reset all its registers
     */
    ~Timer();
    
    /**
     * \brief Stop the timer from incrementing
     */
    void stop();
    
    /**
     * \brief Start the timer
     */
    void start();
    
    /**
     * \brief Clear the value of the timer
     */
    void clear();
    
    /**
     * \brief Set the value at which the timer will expire
     * \param top the new value for the top, 0-65535
     */
    void setTop(uint16_t top);
    
    /**
     * \brief Gives the value at which the timer expires
     */
    uint16_t getTop();
    
    /**
     * \brief Schedule when the timer will expire
     * \param duration number of ms before the timer expires. MAX : 8389
     */
    void schedule(uint16_t duration);
    
    /**
     * \brief Check if the timer has expired
     * \return True if the timer expired, False if it hasen't.
     */
    uint8_t isExpired();
    
    /**
     * \brief Resets the expired state of the timer
     */
    void resetExpiration();
    
private:
    
    /**
     * \brief Gives the prescaler, in powers of 2
     * \return 0, 3, 6, 8 or 10 for prescaler off, 8, 64, 256 or 1024,
     *         respectively
     */
    uint8_t getPrescalerValue();
    
    uint8_t prescalerMode_;
    
};

#endif
