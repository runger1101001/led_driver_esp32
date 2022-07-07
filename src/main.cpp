
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include "SPI.h"


const uint16_t PixelCount = 6 * 16;
const uint8_t PixelPin = 18;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PixelCount, PixelPin, NEO_GRB + NEO_KHZ800);

uint32_t off  = strip.Color(0, 0, 0);
uint32_t green = strip.Color(0, 255, 0);


void setup() {
   Serial.begin(115200);
    while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    pinMode(19, OUTPUT);
    digitalWrite(19, HIGH);

    // this resets all the neopixels to an off state
    strip.begin();
    strip.setBrightness(50);
    strip.show(); // Initialize all pixels to 'off'

    Serial.println();
    Serial.println("Running...");
}



void setPixels(int num, uint32_t col) {
  int i;
  for (i=0;i<num;i++) {
    strip.setPixelColor(i, col);
  }
  for (;i<PixelCount;i++) {
    strip.setPixelColor(i, off);
  }
  strip.show();
}


uint16_t iter = 0;

void loop() {
  //setPixels(iter, strip.Color(rand()%256, rand()%256, rand()%256));
  strip.setPixelColor(iter, strip.Color(rand()%256, rand()%256, rand()%256));
  strip.show();
  if (++iter > PixelCount) {
    strip.clear();
    iter = 0;
  }
  delay(1000);
  Serial.println("Running...");
}