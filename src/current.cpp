
#include "Arduino.h"
#include "./hw_setup.h"
#include "./current.h"


void initCurrentSense() {
    pinMode(PIN_CURRENT, ANALOG);
    analogReadResolution(10);
};


float getCurrent(){
    float raw = getCurrentRaw() / ADC_RESOLUTION;
    raw -= ADC_OFFSET;
    return (raw * ADC_REF) / ADC_V_PER_AMP;
};



int getCurrentRaw(){
    int raw = analogRead(PIN_CURRENT);
    return raw;
};

