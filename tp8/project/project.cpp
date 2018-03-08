#include <Led.h>
#include <Adc.h>

/******************************************************************************\
 * Main
\******************************************************************************/

/**
 * \brief main function
 * \return exit code
 */
int main () {
    
    Led led(1, 3, Led::C);
    Adc adc;
    
    // Pin on which the photoresistor module is connected
    const uint8_t ADC_PIN = 0;
    
    const uint8_t LOW_THRESHOLD = 200;
    const uint8_t HIGH_THRESHOLD = 235;
    
    uint8_t adcReading;
    
    led.setColor(Led::GREEN);
    
    while (1) {
        
        adcReading = (adc.read(ADC_PIN) >> 2);
        
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

