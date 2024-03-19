#include <Arduino.h>
#include "AnalogFilter.h"
#include "handler.h"


void setup() {
    Serial.begin(9600);

    pinMode(32, OUTPUT);
    setupTimer();
    setupHandlers();
}

void loop() {
}