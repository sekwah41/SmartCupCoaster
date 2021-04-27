#include <Arduino.h>

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

const uint16_t PixelCount = 8; // make sure to set this to the number of pixels in your strip
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266

void setup() {
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
}