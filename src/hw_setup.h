
// pinout for ESP32-C3 LED trixel controller board v1.0
// trixels v1 are based on SK6812 RGB LEDs

#pragma once

#define PIN_PIXEL 10
#define PIN_SDA 5
#define PIN_SCL 6
#define PIN_CURRENT 3
#define PIN_SENSE 4

#define PIN_RX 20
#define PIN_TX 21
#define PIN_GPIO0 0
#define PIN_GPIO1 1
#define PIN_GPIO7 7
#define PIN_GPIO8 8

// amps
#define DEFAULT_CURRENT_MAX 2.0f

#define ADC_OFFSET 0.505f
#define ADC_V_PER_AMP 0.266666f
#define ADC_RESOLUTION 1024.0f
#define ADC_REF 3.333f
