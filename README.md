# Firmware for Trixel Controller v1

Version 1.0, barely tested :warning:

- Firmware for [Trixel Controller v1.0](https://github.com/runger1101001/LED_Tile_Controller) ESP32-C3 based LED controller board
- PlatformIO project, use VSCode + PlatformIO + ESP32 packages + Arduino to compile

## Features

- Serial interface for debugging via USB
- HomeKit integration thanks to [HomeSpan](https://github.com/HomeSpan/HomeSpan)
- Connects to pre-defined WLAN
- REST API for pixel control and animation control
- 1 implemented animation
- Brightness control
- Current sensing, logged to serial output

## Compile and flash

Use Visual Studio Code and the PlatformIO development environment to compile this project and flash it to the trixel controller. After installing the ESP32 platform within PlatformIO, all the tools should be present to compile and flash this firmware.

Connect with USB to the trixel-controller, which will provide power and can be used for programming.

Upload the firmware and check in the serial monitor that it is running.

## How to use

Set up your trixels. How to do this is described here. If its your first time setup, it might be a good idea to start with a small, simple panel. You can always get more complicated later.

Connect via web (http) to retrieve web-ui for configuration and control.

You can also connect with HomeKit (Code: 11223344) to control the panel. HomeKit treats the panel as a light, allowing control of the color of all the trixels at the same time. You can't control individual trixels via HomeKit, use the web-ui for that.

You can connect to USB and use a serial terminal app to see debug output and monitor current levels if desired.

## REST API

Call URLs like `http://10.0.0.55/trixels/1?r=255&g=0&b=0&brightness=100`

:warning: Substitute your controller's IP address for the one used in the examples.

### GET /trixels/{n}

Set trixels or brightness

Parameters:
- n - trixel number (in path)
- r - red, 0-255
- g - green, 0-255
- b - blue, 0-255
- brightness - 0-255

Example:
```
http://10.0.0.55/trixels/1?r=255&g=0&b=0&brightness=100

{ "r":253, "g":0, "b":0, "brightness":100 }
```

### GET /animation

Control animation

Parameters:
- enable - switch animation on or off, `true`/`false` or `1`/`0`
- delay - delay between animation frames in ms, a non-negative integer

Example:
```
http://10.0.0.55/animation?delay=100&enable=true

{ "enabled":true, "delay":100 }
```


## Immediate TODOs, problems

- Measure currents to calibrate current sensing
- Complete basic web UI
- Load and store configuration


## Roadmap / future ideas

A list of ideas for future functionality

- Serve up web UI for configuration and trixel control directly
- More animation types built in
- Current sensing: implement over-current protection
- OSC interface for trixel control via USB
- Hue / Home Assistant compatibility
- I2C master interface and drivers for
  - Motion sensor (LED-eye v1)
  - Light sensor
  - RTC
  - Microphone / ambient noise sensor
- Current data logging: improve format (SUMP?)
- I2C device interface for control via I2C
