/*
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LedControl_h
#define LedControl_h

#include <avr/pgmspace.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/*
 * Segments to be switched on for characters and digits on
 * 7-Segment Displays
 */
const static byte charTable [] PROGMEM  = {
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B10000000,B00000001,B10000000,B00000000,
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00000000,B00000000,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00010101,B00011101,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
};

/**
 * @class LedControl
 * @brief A class for controlling LEDs with a MAX7219/MAX7221
 */
#ifdef _ADAFRUIT_GFX_H
class LedControl : public Adafruit_GFX {
#else
class LedControl {
#endif
    private :
        /* The array for shifting the data to the devices */
        byte spidata[16];
        /* Send out a single command to the device */
        void spiTransfer(int addr, byte opcode, byte data);

        /* We keep track of the led-status for all 8 devices in this array */
        byte status[64];
        /* Data is shifted out of this pin*/
        int SPI_MOSI;
        /* The clock is signaled on this pin */
        int SPI_CLK;
        /* This one is driven LOW for chip selectzion */
        int SPI_CS;
        /* The maximum number of devices we use */
        int maxDevices;

    public:
        /**
         * @brief Constructor for the LedControl class.
         * 
         * @param dataPin       Pin where the data gets shifted out.
         * @param clkPin        Pin for the clock.
         * @param csPin         Pin for selecting the device.
         * @param numDevices    Number of devices connected.
         */
        LedControl(int dataPin, int clkPin, int csPin, int numDevices=1);

        /**
         * @brief Initialises the display.
         */
        void begin();
        
        /**
         * @brief Initialises the display.
         * 
         * @param intensity Initial brightness of the display (0-15).
         */
        void begin(int intensity);

        /**
         * @brief Gets the number of devices attached to this LedControl.
         * 
         * @return int Number of devices.
         */
        int getDeviceCount();

        /**
         * @brief Set the shutdown (power saving) mode for the device.
         * 
         * @param addr  Address of the display to control.
         * @param b     If true, the device goes into power-down mode. Set to false for normal operation.
         */
        void shutdown(int addr, bool status);

        /**
         * @brief Set the number of digits (or rows) to be displayed.
         * 
         * @param addr  Address of the display to control.
         * @param limit Number of digits to be displayed (1-8).
         */
        void setScanLimit(int addr, int limit);

        /**
         * @brief Set the brightness of the display.
         * 
         * @param addr      Address of the display to control.
         * @param intensity Brightness of the display (0-15).
         */
        void setIntensity(int addr, int intensity);

        /**
         * @brief Switch all LEDs on the display off.
         * 
         * @param addr Address of the display to control.
         */
        void clearDisplay(int addr);

        /**
         * @brief Switch all LEDs off (all displays).
         */
        void clear();

        /**
         * @brief Set the status of a single LED.
         * 
         * @param addr      Address of the display to control.
         * @param row       Row of the LED (0-7).
         * @param column    Column of the LED (0-7).
         * @param state     State of the LED (true/false).
         */
        void setLed(int addr, int row, int col, boolean state);

        /* Adafruit GFX method*/
        #ifdef _ADAFRUIT_GFX_H
        virtual void drawPixel(int16_t x, int16_t y, uint16_t color);

        template<typename T>
        void scroll(const T& input);
        #endif

        /**
         * @brief Set all 8 LEDs in a row to a new state.
         * 
         * @param addr  Address of the display to control.
         * @param row   Row of the LEDs (0-7).
         * @param value Each bit set to 1 will light up the corresponding LED.
         */
        void setRow(int addr, int row, byte value);

        /**
         * @brief Set all 8 LEDs in a column to a new state.
         * 
         * @param addr  Address of the display to control.
         * @param col   Column of the LEDs (0-7).
         * @param value Each bit set to 1 will light up the corresponding LED.
         */
        void setColumn(int addr, int col, byte value);

        /**
         * @brief Display a hexadecimal number on a 7-segment display.
         * 
         * @param addr  Address of the display to control.
         * @param digit Position of the digit on the display (0-7).
         * @param value Value to be displayed (0x00-0x0F).
         * @param dp    Sets the decimal point (true/false).
         */
        void setDigit(int addr, int digit, byte value, boolean dp);

        /**
         * @brief Display a character on a 7-Segment display.
         *  There are only a few characters that make sense here :
         *	'0','1','2','3','4','5','6','7','8','9','0',
         *  'A','b','c','d','E','F','H','L','P',
         *  '.','-','_',' ' 
         * @param addr      Address of the display to control.
         * @param opcode    Command to be sent.
         * @param data      Data to be sent.
         */
        void setChar(int addr, int digit, char value, boolean dp);
};

#endif	//LedControl.h



