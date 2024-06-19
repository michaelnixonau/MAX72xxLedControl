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
