
#include "./pixels.h"
#include "./hw_setup.h"

uint16_t PixelCount = 16; // * 6;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PixelCount, PIN_PIXEL, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel* initStrip() {
    pinMode(PIN_PIXEL, OUTPUT);
    digitalWrite(PIN_PIXEL, HIGH);

    // this resets all the neopixels to an off state
    strip.begin();
    strip.setBrightness(50);
    strip.show(); // Initialize all pixels to 'off'
    return &strip;
};


bool animation = false;
long animationTs = millis();
int animationDelay = 1000;

void handleAnimation() {
    long now = millis();
    if (now - animationTs > animationDelay) {
        if (animation) {
            randomFill();
        }
        animationTs = now;
    }
};


void setAnimation(bool animate, int delayMs){
    animationDelay = delayMs;
    animation = animate;
};

bool isAnimation(){
    return animation;
};
int getAnimationDelayMs(){
    return animationDelay;
};


void setAllPixelsOff(){
    strip.setBrightness(0);
    strip.show();
};


void clearPixels(){
    strip.clear();
    strip.show();
};


void showPixels(){
    strip.show();
};


void setAllPixels(uint8_t r, uint8_t g, uint8_t b){
    strip.fill(strip.Color(r, g, b));
    strip.show();
};


void setPixel(int pixel, uint8_t r, uint8_t g, uint8_t b){
    strip.setPixelColor(pixel, strip.Color(r, g, b));
    strip.show();
};


void setBrightness(uint8_t brightness){
    strip.setBrightness(brightness);
};

int getBrightness(){
    return strip.getBrightness();
};


uint32_t getPixel(int pixel){
    if (pixel < 0 || pixel >= PixelCount)
        return 0;
    return strip.getPixelColor(pixel);
};

uint16_t iter = 0;

void randomFill() {
    //Serial.println("randomFill animation step");
    strip.setPixelColor(iter, strip.Color(rand()%256, rand()%256, rand()%256));
    strip.show();
    if (++iter > PixelCount) {
        strip.clear();
        iter = 0;
    }
};

