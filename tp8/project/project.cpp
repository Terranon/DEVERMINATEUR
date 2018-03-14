/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi, Thomas Dufour,
 *              William Chartrand
 * Name:        project.cpp
 * Description: Simple test program for the library 'deverminateur'. Robot will
 *              play a note when program first begins then will move forward
 *              when the photocell senses high luminosity and backwards when it
 *              senses low luminosity. The Led will also respond to luminosity.
 * 
 * Pinout :                            PIEZO (- +|- +) LED              JM2(D E)
 *                                            | | | |                       | |
 * PORTA  1 3 5 7    PORTB  1 3 5 7    PORTC  0 1 2 3 4 5 6 7    PORTD  1 3 5 7        
 *        0 2 4 6           0 2 4 6                                     0 2 4 6        
 *        |                                                                 | |
 *       (D) Light sensor Module                                        JM1(D E)
 * 
 *       ( |   | ) TENSION CONNECTED TO PHOTOCELL
 * PORTA (VCC GND)
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
    
    Led led;                // initialize Led class
    PhotoCell sensor;       // initialize PhotoCell class
    Motor wheels;           // initialize Motor class
    Piezo alarm(Piezo::LA); // initialize Piezo class with initial note LA: 440Hz
    
    const uint8_t LOW_THRESHOLD = 200;   // fixed variables for comparison with
    const uint8_t HIGH_THRESHOLD = 220;  // input from PhotoCell
    
    uint8_t sensorReading;  // this variable will hold the value of the intensity
                            // set by PhotoCell class
    
    led.setColor(Led::GREEN); // initial color of the Led is green
    
    alarm.playSixteenthNote(Piezo::LA); // robot plays a LA:440Hz
    
    while (1) {
        
        sensorReading = sensor.getValeurIntensite();
        
        if (sensorReading < LOW_THRESHOLD) {         // If the sensor reading 
            led.setColor(Led::GREEN);                // is below the low 
            wheels.setSpeed(200);                    // threshhold, set Led to
            wheels.setDirection(Motor::BACK);        // green and set motors in
            wheels.driveMotors();                    // reverse.
        } 
        else if (sensorReading > HIGH_THRESHOLD) {   // If the sensor reading
            led.setColor(Led::RED);                  // is above the high
            wheels.setSpeed(200);                    // threshhold, set Led to
            wheels.setDirection(Motor::FRWD);        // red and set motors to
            wheels.driveMotors();                    // move forward.
        } 
        else {                                       // If the sensor reading 
            led.toggleColor();                       // is between both
            wheels.setSpeed(0);                      // threshholds, set Led to
            wheels.driveMotors();                    // amber and set motors to
        }                                            // stop.
        
    }
        
    return 0;
}

