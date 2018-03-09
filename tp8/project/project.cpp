/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Simple test program for the library 'deverminateur'
 * 
 * Pinout :                              LED (+ -)
 *                                            | |                          
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  1 3 5 7    PORTD  1 3 5 7        
 *        0 2 4 6           0 2 4 6           0 2 4 6           0 2 4 6        
 *        |          
 *       (D) Light sensor Module     
 * 
 * Version: 1.0
\******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <PhotoCell.h>
#include <Adc.h>
#include <Motor.h>
#include <Piezo.h>
#include <Led.h>

/******************************************************************************\
 * Main
\******************************************************************************/

/**
 * \brief main function
 * \return exit code
 */
int main () {
    
    Led led;
    PhotoCell sensor;
    Motor wheels;
    Piezo alarm(Piezo::LA);
    
    const uint8_t LOW_THRESHOLD = 200;
    const uint8_t HIGH_THRESHOLD = 220;
    
    uint8_t sensorReading;
    
    led.setColor(Led::GREEN);
    
    alarm.playSixteenthNote(Piezo::LA);
    
    while (1) {
        
        sensorReading = sensor.getValeurIntensite();
        
        if (sensorReading < LOW_THRESHOLD) {
            led.setColor(Led::GREEN);
            wheels.setSpeed(200);
            wheels.setDirection(Motor::BACK);
            wheels.driveMotors();
        } else if (sensorReading > HIGH_THRESHOLD) {
            led.setColor(Led::RED);
            wheels.setSpeed(200);
            wheels.setDirection(Motor::FRWD);
            wheels.driveMotors();
        } else {
            led.toggleColor();
            wheels.setSpeed(0);
            wheels.driveMotors();
        }
        
    }
        
    return 0;
}

