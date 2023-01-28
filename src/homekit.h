

#pragma once

#include "Arduino.h"
#include "WiFi.h"
#include "WiFiClient.h"
#include "WiFiServer.h"
#include "WiFiUdp.h"
#include <Adafruit_NeoPixel.h>
#include "HomeSpan.h" 

void init_homekit(Adafruit_NeoPixel* strip);


class DEV_NeoLED : Service::LightBulb {       // RGB LED (Command Cathode)
public:
    SpanCharacteristic *power;                   // reference to the On Characteristic
    SpanCharacteristic *H;                       // reference to the Hue Characteristic
    SpanCharacteristic *S;                       // reference to the Saturation Characteristic
    SpanCharacteristic *V;                       // reference to the Brightness Characteristic
  
    Adafruit_NeoPixel* _strip;

    DEV_NeoLED(Adafruit_NeoPixel* strip);

    boolean update();

};