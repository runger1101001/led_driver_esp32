
#pragma once

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel* initStrip();
void handleAnimation();
void setAnimation(bool animate, int delayMs = 1000);
bool isAnimation();
int getAnimationDelayMs();
void setAllPixelsOff();
void showPixels();
void clearPixels();
void setAllPixels(uint8_t r, uint8_t g, uint8_t b);
void setBrightness(uint8_t brightness);
int getBrightness();
void setPixel(int pixel, uint8_t r, uint8_t g, uint8_t b);
uint32_t getPixel(int pixel);

void randomFill();