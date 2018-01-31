/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        j_tp4_p2.cpp
 * Description: 
 * 
 *              Pinout : Main board PORTC ( 0 1 2 3 4 5 6 7 )
 *                                          | |
 *                           H Bridge JM1 ( E D )
 * 
 * Version: 1.0
\******************************************************************************/

/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

// in us
const uint16_t LOOP_TIME_400HZ = 2'500;
const uint16_t LOOP_TIME_60HZ = 16'666;
const uint16_t SLEEP_PRECISION = 50;
    
// Constants for the H bridge in port 0..1
const uint8_t OFF  = 0x00;
const uint8_t FRWD = 0x01;
const uint8_t BACK = 0x03;

void sleep_us (uint16_t us) {
    
    uint16_t nLoopIterations = us / SLEEP_PRECISION; 
    
    for (uint16_t i = 0; i < nLoopIterations; i++) {
        _delay_us(SLEEP_PRECISION);
    }
}

void driveMotors (uint8_t direction, uint8_t speed, uint32_t time,
                  uint16_t pwmFreqInv) {
    
    uint32_t nLoopIterations = time / pwmFreqInv;
    uint16_t onTime = pwmFreqInv * (speed / 255.0);
    uint16_t offTime = pwmFreqInv - onTime;
    
    for (uint32_t i = 0; i < nLoopIterations; i++) {
        PORTC = direction;
        sleep_us(onTime);
        PORTC = OFF;
        sleep_us(offTime);
    }
}

/******************************************************************************\
 * Main
\******************************************************************************/
int main () {
    
    // C PORT output
    DDRC = 0xff;
    
    // D PORT input
    DDRD = 0x00;
    
    driveMotors(FRWD, 0x00, 2'000'000, LOOP_TIME_60HZ);
    driveMotors(FRWD, 0x40, 2'000'000, LOOP_TIME_60HZ);
    driveMotors(FRWD, 0x80, 2'000'000, LOOP_TIME_60HZ);
    driveMotors(FRWD, 0xc0, 2'000'000, LOOP_TIME_60HZ);
    driveMotors(FRWD, 0xff, 2'000'000, LOOP_TIME_60HZ);
    driveMotors(FRWD, 0x00, 2'000'000, LOOP_TIME_400HZ);
    driveMotors(FRWD, 0x40, 2'000'000, LOOP_TIME_400HZ);
    driveMotors(FRWD, 0x80, 2'000'000, LOOP_TIME_400HZ);
    driveMotors(FRWD, 0xc0, 2'000'000, LOOP_TIME_400HZ);
    driveMotors(FRWD, 0xff, 2'000'000, LOOP_TIME_400HZ);
    
    return 0;
}

