# Firmware for Trixel Controller v1

Version 1.0, barely tested :warning:

- Works with Trixel Controller v1.0 ESP32-C3 board
- PlatformIO project, use VSCode + PlatformIO + ESP32 packages + Arduino to compile

## Features

- Serial interface for debugging via USB
- HomeKit integration thanks to [HomeSpan](https://github.com/HomeSpan/HomeSpan)
- Connect to pre-defined WLAN
- REST API for pixel control and animation control
- 1 implemented animation
- Brightness control
- Current sensing, logged to serial output

## How to use

Set up your trixels. How to do this is described here. If its your first time setup, it might be a good idea to start with a small, simple panel. You can always get more complicated later.

Connect to USB an use serial terminal to see debug output and monitor current if desired.

Connect with HomeKit (Code: 11223344) to control.

Connect via web (http) to retrieve web-ui for configuration and advanced control.

## Immediate TODOs, Problems

- Measure currents to calibrate current sensing
- Complete basic web UI
- Load and store configuration


## Roadmap / future functionality

A list of ideas for future functionality

- Current sensing: implement over-current protection
- Current data logging: improve format (SUMP?)
- I2C master interface and drivers for
  - Motion sensor (LED-eye v1)
  - Light sensor
  - RTC
  - Microphone / ambient noise sensor
- OSC interface for trixel control via USB
- Serve web UI for configuration and trixel control
- Hue / Home Assistant compatibility
- I2C device interface for control via I2C
