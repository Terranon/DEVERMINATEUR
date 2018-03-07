/*****************************************************************************\
 * Author:      Jean-Raphael Matte
 * Name:        Timer.cpp
 * Description: General purpose 16 bit CTC timer/counter
 * Version: 1.0
\******************************************************************************/

Timer::Timer()
    : prescalerMode_(5) {
    
    // disable interruptions
    cli();
    
    // DDRx - Data Direction Register for port x
    
    // bit      | 7      6      5      4      3      2      1      0
    // mnemonic | DDx7   DDx6   DDx5   DDx4   DDx3   DDx2   DDx1   DDx0
    // 
    // bit n DDxn Data Direction x n
    
    // DDxn Data Direction x n
    // values | behavior
    // 0      | Port is set to input 
    // 1      | Port is set to output
    
    // set OC1A pin to Output for possible debugging
    DDRD |= (1 << DDD5);
    
    
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
    
    // The A flag will be used to verifiy if the timer has expired.
    TCCR1A |= (3 << COM1A0);
    
    // The B flag is unused
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
    
    // Unused
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
    
    // Unused
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
    
    // Initialize the timer stopped
    TCCR1B |= (0 << CS10);
    
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
    
    // Unused, needs to be initialized
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
    
    // CTC mode for general purpose timer
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
    
    // Unused
    TIMSK1 |= (0 << ICIE1);
    
    // OCIE1x Output Compare match Interrupt 1 x Enable
    // values | behavior
    // 0      | Disable interrupts for OCIE1x
    // 1      | Enable interrupts for OCIE1x
    
    // Interruptions do not need to be enabled, as the OC1A and OC1B pins will
    // be read to determine if the timer has expired.
    TIMSK1 |= (0 << OCIE1B);
    TIMSK1 |= (0 << OCIE1A);
    
    // TOIE1 Timer/counter Overflow Interrupt Enable 1
    // values | behavior
    // 0      | Disable interrupts for TOIE1
    // 1      | Enable interrupts for TOIE1 
    
    // Unused
    TIMSK1 |= (0 << TOIE1);
    
    // enable interruptions
    sei();
    
}

Timer::~Timer() {
    
    // Stop the timer
    this->stop();
    
    // Disconnect OC1A
    TCCR1A |= (0 << COM1A0);
    
    // Waveform generator mode : normal
    TCCR1B |= (0 << WGM12);
    TCCR1A |= (0 << WGM10);
    
}

void Timer::stop() {
    TCCR1B |= (0 << CS10);
}

void Timer::start() {
    TCCR1B |= (prescalerMode_ << CS10);
}

void Timer::clear() {
    TCNT1 = 0;
}

void Timer::setTop(uint16_t top) {
    OCR1A = top;
}
    
uint16_t Timer::getTop() {
    return OCR1A;
}

void schedule(uint16_t duration) {
    // Value of Timer/Counter 1, 16 bits
    this->clear();
    
    // Output Compare Register 1 A
    this->setTop((duration * (F_CPU >> this->getPrescalerValue())) / 1000);
}

uint8_t Timer::isExpired() {
    return PIND & (1 << PIND5);
}

void resetExpiration() {
    PORTD &= ~(0 << PORTD5)
}

uint8_t Timer::getPrescalerValue() {
    
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
    switch (prescalerMode_) {
        case 1:
            return 0;
            break;
        case 2:
            return 3;
            break;
        case 3:
            return 6;
            break;
        case 4:
            return 8;
        case 5:
            return 10;
            break;
        default:
            return 0;
            break;
    }
    
}
