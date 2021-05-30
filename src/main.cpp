#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <HX711.h>
#include <TaskScheduler.h>


// How many NeoPixels are attached to the Arduino?
int numPixels   = 8; // Popular NeoPixel ring size

// NeoPixel color format & data rate. See the strandtest example for
// information on possible values.
int pixelFormat = NEO_GRB + NEO_KHZ800;

// Which LED_PIN on the Arduino is connected to the NeoPixels?
const int LED_PIN            =  4;
const int LOADCELL_DOUT_PIN   = 2;
const int LOADCELL_SCK_PIN    = 32;

// Pointer for pixels to control
Adafruit_NeoPixel *pixels;
HX711 scale;
Scheduler r;

// How often to check for changes
#define WEIGHT_CHECK_DELAY 500
#define LED_UPDATE_DELAY 10

// How many seconds to take
#define NOTIF_FADE_SPEED 4

#define SECONDS 1000


void updateLedCallback() {

    if(millis() >  3 * SECONDS && millis() <  6 * SECONDS) {

        double multiplier = abs(sin(millis() * (PI * 0.001 / NOTIF_FADE_SPEED)));

        for(int i=0; i<numPixels; i++) {
            pixels->setPixelColor(i, pixels->Color(0 * multiplier,70 * multiplier,255 * multiplier));
        }
    } else if(millis() <  13 * SECONDS) {
        pixels->clear();
    } else if(millis() <  18 * SECONDS) {

        double multiplier = abs(sin(millis() * (PI * 0.001 / NOTIF_FADE_SPEED)));
        for(int i=0; i<numPixels; i++) {
            pixels->setPixelColor(i, pixels->Color(255 * multiplier,0 * multiplier,0 * multiplier));
        }
    } else if(millis() <  24 * SECONDS) {
        pixels->clear();
    } else if(millis() <  27 * SECONDS) {

        double multiplier = abs(sin(millis() * (PI * 0.001 / NOTIF_FADE_SPEED * 4)));
        for(int i=0; i<numPixels; i++) {
            pixels->setPixelColor(i, pixels->Color(0 * multiplier,255 * multiplier,0 * multiplier));
        }
    } else {

        pixels->clear();
    }


    pixels->show();
}

void checkWeightCallback() {

    if (scale.wait_ready_retry(10)) {
        long reading = scale.read();
        Serial.print("HX711 reading: ");
        Serial.println(reading);
    } else {
        Serial.println("HX711 not found.");
    }
}

Task neopixelsTask(LED_UPDATE_DELAY, -1, &updateLedCallback);
Task checkWeightTask(WEIGHT_CHECK_DELAY, -1, &checkWeightCallback);

void setup() {
    // put your setup code here, to run once:
    pixels = new Adafruit_NeoPixel(numPixels, LED_PIN, pixelFormat);

    Serial.begin(9600);
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

    pixels->begin();

    r.init();
    Serial.println("Initialized scheduler");

    Serial.println("Adding tasks");

    r.addTask(neopixelsTask);
    r.addTask(checkWeightTask);

    r.enableAll();
}

void loop() {
    r.execute();
}