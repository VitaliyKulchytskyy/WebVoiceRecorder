#include "AnalogFilter.h"

uint16_t getAmplitude(uint8_t pin) {
    const uint16_t sampleWindow = 1000;
    uint16_t sample = 0;
    unsigned long startMillis = micros();
    uint16_t signalMax = 0;
    uint16_t signalMin = 1024;

    while (micros() - startMillis < sampleWindow) {
        sample = analogRead(pin);
        signalMin = min(signalMin, sample);
        signalMax = max(signalMax, sample);
    }

    return signalMax - signalMin;
}

uint16_t analogReadFiltered(uint8_t analogPin, uint16_t analogMinValue) {
    const uint16_t inputAnalog = getAmplitude(analogPin);
    static uint16_t output = inputAnalog;
    output = (output >> 1) + (inputAnalog >> 1);
    return (output >= analogMinValue) ? output : 0;
}
