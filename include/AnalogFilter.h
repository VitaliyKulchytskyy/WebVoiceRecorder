#pragma once
#include <Arduino.h>

/**
 * @note Appropriate analogRead() for reading data from the microphone
 * @param pin set an analog pin to read the data.
 * @return An analog value.
 */
uint16_t getAmplitude(uint8_t pin);

/**
 * @note The median filtering algorithm.
 * @param adcValue set a value of an analog signal.
 * @return Analog value got by the median filtering algorithm.
 */
uint16_t median(uint16_t adcValue);

/**
 * @note Appropriate analogRead() function with filtering analog signal.
 * @param analogPin set an analog pin to read the data.
 * @param analogMinValue set a threshold value.
 * @return A filtered analog value.
 */
uint16_t analogReadFiltered(uint8_t analogPin, uint16_t analogMinValue);