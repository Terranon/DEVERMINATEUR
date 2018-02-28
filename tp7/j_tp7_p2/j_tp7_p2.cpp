/*****************************************************************************\
 * Authors:     Jean-Raphael Matte, Maximilien Bianchi
 * Name:        j_tp7_p2.cpp
 * Description: Flash the LED according to the reading of a light sensor
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

/******************************************************************************\
 * Preprocessor instructions
\******************************************************************************/

#include "j_tp7_p2.h"

/******************************************************************************\
 * Global variables
\******************************************************************************/

// Global variables to catch interruptions
volatile uint8_t timerExpired;

/******************************************************************************\
 * Initialization functions
\******************************************************************************/

/**
 * \brief initialize the special registers for intputs / outputs
 */
void initIO() {
    
    // DDRx - Data Direction Register for port x
    
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | DDx7   DDx6   DDx5   DDx4   DDx3   DDx2   DDx1   DDx0
    // 
    // bit n DDxn Data Direction x n
    
    // DDxn Data Direction x n
    // values | behavior
    // 0      | Port is set to input 
    // 1      | Port is set to output
    
    DDRA |= (0 << DDA7); // ADC7
    DDRA |= (0 << DDA6); // ADC6
    DDRA |= (0 << DDA5); // ADC5
    DDRA |= (0 << DDA4); // ADC4
    DDRA |= (0 << DDA3); // ADC3
    DDRA |= (0 << DDA2); // ADC2
    DDRA |= (0 << DDA1); // ADC1
    DDRA |= (0 << DDA0); // ADC0
    
    DDRB |= (0 << DDB7);
    DDRB |= (0 << DDB6);
    DDRB |= (0 << DDB5);
    DDRB |= (0 << DDB4); // OC0B
    DDRB |= (0 << DDB3); // OC0A
    DDRB |= (0 << DDB2); // INT2
    DDRB |= (0 << DDB1); // T1
    DDRB |= (0 << DDB0); // T0
    
    DDRC |= (0 << DDC7);
    DDRC |= (0 << DDC6);
    DDRC |= (0 << DDC5);
    DDRC |= (0 << DDC4);
    DDRC |= (0 << DDC3);
    DDRC |= (0 << DDC2);
    DDRC |= (0 << DDC1);
    DDRC |= (0 << DDC0); 
    
    DDRD |= (0 << DDD7); // OC2A
    DDRD |= (0 << DDD6); // OC2B
    DDRD |= (0 << DDD5); // OC1A
    DDRD |= (0 << DDD4); // OC1B
    DDRD |= (0 << DDD3); // INT1
    DDRD |= (0 << DDD2); // INT0
    DDRD |= (0 << DDD1); // TXD0
    DDRD |= (0 << DDD0); // RXD0

}

/**
 * \brief Initialize external interruptions
 */
void initEInt() {
    
    // EIMSK - External Interrupt Mask Register
    
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | --     --     --     --     --     INT2   INT1   INT0
    // 
    // bits 7:3 are unused
    // bit 2 INT2 External Interrupt Request 2 Enable
    // bit 1 INT1 External Interrupt Request 1 Enable
    // bit 0 INT0 External Interrupt Request 0 Enable
    
    // INTn External Interrupt Request n Enable
    // values | behavior
    // 0      | Disable interrupts for INTn 
    // 1      | Enable interrupts for INTn
    
    EIMSK |= (0 << INT2);
    EIMSK |= (0 << INT1);
    EIMSK |= (0 << INT0);
    
    
    // EICRA - External Interrupt Control Register A
    
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | --     --     ISC21  ISC20  ISC11  ISC10  ISC01  ISC00
    // 
    // bits 7:6 are unused
    // bits 5:4 ISC2[1:0] External Interrupt 2 Sense Control Bits
    // bits 3:2 ISC1[1:0] External Interrupt 1 Sense Control Bits
    // bits 1:0 ISC0[1:0] External Interrupt 0 Sense Control Bits
    
    // ISCn[1:0] External Interrupt n Sense Control Bits
    // values | behavior
    // 0      | The low level generates an interrupt request.
    // 1      | Any logical change generates an interrupt request.
    // 2      | The falling edge generates an interrupt request.
    // 3      | The rising edge generates an interrupt request.

    EICRA |= (0 << ISC20);// INT2
    EICRA |= (0 << ISC10);// INT1
    EICRA |= (0 << ISC00);// INT0
    
}

/**
 * \brief Initialize the registers for the timer
 */
void initTimer() {
    
    // TCCR1A/TCCR1B/TCCR1C are the Timer/Counter Control Registers 1 A/B/C
    
    // ~~~TCCR1A~~~
    //
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | COM1A1 COM1A0 COM1B1 COM1B0 --     --     WGM11  WGM10
    // 
    // bits 7:6 COM1A[1:0] Compare Output Mode for Channel A
    // bits 5:4 COM1B[1:0] Compare Output Mode for Channel B
    // bits 3:2 are unused
    // bits 1:0 WGM1[1:0] Waveform Generation Mode
        
    // COM1x[1:0] Compare Output Mode for Channel x
    //
    // Non-PWM
    // v | behavior
    // 0 | Normal port operation, OC1x disconnected.
    // 1 | Toggle OC1x on Compare Match.
    // 2 | Clear OC1x on Compare Match (Set output to low level).
    // 3 | Set OC1x on Compare Match (Set output to high level).
    //
    // Fast PWM
    // v | behavior
    // 0 | Normal port operation, OC1x disconnected.
    // 1 | WGM1 14-15: Toggle OC1A on Compare Match, OC1B disconnected.
    // 2 | Clear OC1x on Compare Match, set OC1x at BOTTOM (non-inverting)
    // 3 | Set OC1x on Compare Match, clear OC1x at BOTTOM (inverting mode)
    //
    // Phase correct and phase and frequency correct PWM
    // v | behavior
    // 0 | Normal port operation, OC1x disconnected.
    // 1 | WGM1 9-11: Toggle OC1A on Compare Match, OC1B disconnected.
    // 2 | Clear OC1x when up-count match. Set OC1x when downcount match.
    // 3 | Set OC1x when up-count match. Clear OC1x when downcount match.
    
    TCCR1A |= (0 << COM1A0);
    TCCR1A |= (0 << COM1B0);
    
    // WGM1[1:0] Waveform Generation Mode
    // -> See Description for WGM[3:0] below
    
    
    // ~~~TCCR1B~~~
    //
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | ICNC1  ICES1  --     WGM13  WGM12  CS12   CS11   CS10
    // 
    // bits 7   ICNC1 Input Capture Noise Canceler
    // bits 6   ICES1 Input Capture Edge Select
    // bits 5   is unused, must be 0
    // bits 4:3 WGM1[3:2] Waveform Generation Mode
    // bits 2:0 CS1[2:0] Clock Select
    
    // ICNC1 Input Capture Noise Canceler
    // values | behavior
    // 0      | Input from the Input Capture Pin (ICP1) is unfiltered
    // 1      | Input from the Input Capture Pin (ICP1) is filtered,
    //          require four successive equal valued samples of the ICP1 pin
    //          for changing its output.
    
    TCCR1B |= (0 << ICNC1);
    
    // ICES1 Input Capture Edge Select
    // values | behavior
    // 0      | Falling edge on ICP1 is used as trigger for a capture
    // 1      | Rising edge on ICP1 is used as trigger for a capture
    // NOTE : When a capture is triggered according to the ICESn setting,
    // the counter value is copied into the Input Capture Register (ICR1). 
    // The event will also set the Input Capture Flag (ICF1), and this can 
    // be used to cause an Input Capture Interrupt, if this interrupt is 
    // enabled.
    // When the ICR1 is used as TOP value (see description of the WGM1[3:0] 
    // bits located in the TCCR1A and the TCCR1B Register), the ICP1 is 
    // disconnected and consequently the Input Capture function is disabled.
    
    TCCR1B |= (0 << ICES1);
    
    // WGM1[3:2] Waveform Generation Mode
    // -> See Description for WGM[3:0] below
    
    // CS1[2:0] Clock Select
    // v | behavior
    // 0 | No clock source (Timer/Counter stopped).
    // 1 | clkI/O /1 (No prescaling)
    // 2 | clkI/O /8 (From prescaler)
    // 3 | clkI/O /64 (From prescaler)
    // 4 | clkI/O /256 (From prescaler)
    // 5 | clkI/O /1024 (From prescaler)
    // 6 | External clock source on T1 pin. Clock on falling edge.
    // 7 | External clock source on T1 pin. Clock on rising edge.
    
    TCCR1B |= (5 << CS10);
    
    // ~~~TCCR1C~~~
    //
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | FOC1A  FOC1B  --     --     --     --     --     -- 
    // 
    // bits 7   FOC1A Force Output Compare for Channel A
    // bits 6   FOC1B Force Output Compare for Channel B
    // bits 5:0 are unused
    
    // FOC1x Force Output Compare for Channel x
    // values | behavior
    // 0      | Initialize when in PWM mode
    // 1      | Force the comparison of COM1x and TCNT1 when this bit is set
    // NOTE : The FOC1x bits are only active when the WGM1[3:0] bits 
    // specifies a non-PWM mode. However, for ensuring compatibility with 
    // future devices, these bits must be set to zero when TCCR1A is written 
    // when operating in a PWM mode. When writing a logical one to the FOC1x 
    // bit, an immediate compare match is forced on the Waveform Generation 
    // unit. The OC1x output is changed according to its COM1x[1:0] bits 
    // setting. Note that the FOC1x bits are implemented as strobes. 
    // Therefore it is the value present in the COM1x[1:0] bits that 
    // determine the effect of the forced compare.
    // A FOC1x strobe will not generate any interrupt nor will it clear the 
    // timer in Clear Timer on Compare match (CTC) mode using OCR1A as TOP. 
    // The FOC1x bits are always read as zero.
    
    TCCR1C = (0 << FOC1A);
    TCCR1C = (0 << FOC1B);
        
    // ~~~WGM1[3:0]~~
    //
    // Mode | Timer/Counter mode           | TOP    | Update of | TOV1 flag  
    //      |                              |        | OCR1x at  | set on     
    //      |                              |        |           |              
    // 0    | normal                       | 0xFFFF | Immediate | MAX
    // 1    | PWM, Phase Correct, 8-bit    | 0x00FF | TOP       | BOTTOM
    // 2    | PWM, Phase Correct, 9-bit    | 0x01FF | TOP       | BOTTOM
    // 3    | PWM, Phase Correct, 10-bit   | 0x03FF | TOP       | BOTTOM
    // 4    | Clear Timer on Compare Match | OCR1A  | Immediate | MAX
    // 5    | Fast PWM, 8-bit              | 0x00FF | BOTTOM    | TOP
    // 6    | Fast PWM, 9-bit              | 0x01FF | BOTTOM    | TOP
    // 7    | Fast PWM, 10-bit             | 0x03FF | BOTTOM    | TOP
    // 8    | PWM, Phase and Freq. Correct | ICR1   | BOTTOM    | BOTTOM
    // 9    | PWM, Phase and Freq. Correct | OCR1A  | BOTTOM    | BOTTOM
    // 10   | PWM, Phase Correct           | ICR1   | TOP       | BOTTOM
    // 11   | PWM, Phase Correct           | OCR1A  | TOP       | BOTTOM
    // 12   | Clear Timer on Compare Match | ICR1   | Immediate | MAX
    // 13   | (Reserved)                   | --     | --        | --
    // 14   | Fast PWM                     | ICR1   | BOTTOM    | TOP
    // 15   | Fast PWM                     | OCR1A  | BOTTOM    | TOP
    
    // Modify this line
    const uint8_t WGM1_val = 4;
    
    // Do not modify
    TCCR1B |= ((WGM1_val >> 2) << WGM12);
    TCCR1A |= ((WGM1_val & 0x03) << WGM10);
    
    
    
    // TIMSK1 - Timer Interrupt Mask Register 1
    
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | --     --     ICIE1  --     --     OCIE1B OCIE1A TOIE1
    // 
    // bits 7:6 are unused
    // bit 5 ICIE1 Input Capture Interrupt Enable 1
    // bits 4:3 are unused
    // bit 2 OCIE1B Output Compare B Match Interrupt Enable 1
    // bit 1 OCIE1A Output Compare A Match Interrupt Enable 1
    // bit 0 
    
    // ICIE1 Input Capture Interrupt Enable 1
    // values | behavior
    // 0      | Disable interrupts for ICIE1
    // 1      | Enable interrupts for ICIE1
    
    TIMSK1 |= (0 << ICIE1);
    
    // OCIE1x Output Compare match Interrupt 1 x Enable
    // values | behavior
    // 0      | Disable interrupts for OCIE1x
    // 1      | Enable interrupts for OCIE1x
    
    TIMSK1 |= (0 << OCIE1B);
    TIMSK1 |= (1 << OCIE1A);
    
    // TOIE1 Timer/counter Overflow Interrupt Enable 1
    // values | behavior
    // 0      | Disable interrupts for TOIE1
    // 1      | Enable interrupts for TOIE1 
    
    TIMSK1 |= (0 << TOIE1);
        
}

/**
 * \brief master initialization function
 */
void initialize() {
    
    // disable interruptions
    cli();
    
    initIO();
    initTimer();
    initEInt();
    
    // enable interruptions
    sei();
}

/******************************************************************************\
 * Functions
\******************************************************************************/

/**
 * \brief Schedule a TIMER_COMPA interrupt
 * \param duration time before the interrupt occurs, in ms. MAX : 8389
 */
void startTimer (uint32_t duration) {
    
    // The timer will stop incrementing
    TCCR1B |= (0 << CS10);

    // Value of Timer/Counter 1, 16 bits
    TCNT1 = 0;
    
    // Output Compare Register 1 A
    OCR1A = (duration * (F_CPU >> 10)) / 1000;
    
    // The timer will start incrementing
    TCCR1B |= (5 << CS10);
    
}

/******************************************************************************\
 * Interrupt Subroutines
\******************************************************************************/

/**
 * \brief This subroutine is executed whenever the timer sends an interruption
 * \param TIMER1_COMPA the function will run when comparator A is true for
 *                     timer 1
 */
ISR (TIMER1_COMPA_vect) {
    timerExpired = 1;
}

/******************************************************************************\
 * Main
\******************************************************************************/

/**
 * \brief main function
 * \return exit code
 */
int main () {
    
    initialize();
    
    Led led(1, 3, Led::C);
    Can adc;
    
    // Pin on which the photoresistor module is connected
    const uint8_t ADC_PIN = 0;
    
    const uint8_t LOW_THRESHOLD = 200;
    const uint8_t HIGH_THRESHOLD = 235;
    
    uint8_t adcReading;
    
    led.setColor(Led::GREEN);
    
    while (1) {
        
        adcReading = (adc.lecture(ADC_PIN) >> 2);
        
        if (adcReading < LOW_THRESHOLD) {
            led.setColor(Led::GREEN);
        } else if (adcReading > HIGH_THRESHOLD) {
            led.setColor(Led::RED);
        } else {
            led.toggleColor();
        }
        
    }
        
    return 0;
}

