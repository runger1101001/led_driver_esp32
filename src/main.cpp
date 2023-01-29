
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "SPI.h"

#include "./hw_setup.h"
#include "./wifi.h"
#include "./homekit.h"
#include "./pixels.h"
#include "./current.h"

Adafruit_NeoPixel* pixels;

long ts;
int panelDetected;

void setup() {
    Serial.begin(115200);
    delay(3000);
    //while (!Serial); // wait for serial attach

    Serial.println();
    Serial.println("Initializing...");
    //Serial.flush();

    initCurrentSense();
    pixels = initStrip();
    init_homekit(pixels); // also takes care of wifi

    pinMode(PIN_SENSE, INPUT);
    panelDetected = digitalRead(PIN_SENSE);
    Serial.println("Sense input is: " + String(panelDetected));

    setAnimation(true, 1000);

    Serial.println();
    Serial.println("Running...");
    ts = millis();
}



void loop() {
  homeSpan.poll();
  handleWebserver();
  handleAnimation();
  long now = millis();
  if (now - ts > 1000) {
    Serial.print("Current: ");
    Serial.print(getCurrentRaw());
    Serial.print(" = ");
    Serial.print(getCurrent());
    Serial.println("A");
    ts = now;
  }
}
