# MAX72xxLedControl
A fork of Eberhard Fahle's excellent [LedControl](https://github.com/wayoda/LedControl/tree/master) library.

MAX72xxLedControl is an [Arduino](http://arduino.cc) library for MAX7219 and MAX7221 Led display drivers.
The code also works with the [Teensy (3.1)](https://www.pjrc.com/teensy/)

## Install
The library can be installed using the [standard Arduino library install procedure](http://arduino.cc/en/Guide/Libraries).

## Getting Started

```
#include<MAX72xxLedControl.h>

// Initialise the LED matrix
LedControl matrix = LedControl(12, 11, 10);

void setup() {
    // Wake up display and set to default brightness
    matrix.begin();
}

void loop() {
    // Turn on LED at (x, y) = (1, 3)
    matrix.setLed(0, 1, 3, HIGH);
}
```

## Adafruit GFX
This library is compatible with the [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) graphics library, which enables more advanced graphics functionality on 8x8 LED displays.

Simply include Adafruit GFX to get started:

```
#include <Adafruit_GFX.h>
```

[Learn more about the commands available with Adafruit GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview).
