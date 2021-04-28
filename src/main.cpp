#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <HX711.h>
#include <TaskScheduler.h>

// Which pin on the Arduino is connected to the NeoPixels?
int pin        =  4;

// How many NeoPixels are attached to the Arduino?
int numPixels   = 8; // Popular NeoPixel ring size

// NeoPixel color format & data rate. See the strandtest example for
// information on possible values.
int pixelFormat = NEO_GRB + NEO_KHZ800;

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

// Pointer for pixels to control
Adafruit_NeoPixel *pixels;
HX711 scale;
Scheduler r;

// How often to check for changes
#define DELAY 500

#define NOTIF_FADE_SPEED

void updateLedCallback() {
    Serial.println("TASK 1");

    millis()


    if(pixelStage >= numPixels) {
        pixelStage = 0;
        pixels->clear();
    }

    pixels->setPixelColor(pixelStage++, pixels->Color(0,150,0));

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

Task neopixelsTask(500, -1, &updateLedCallback);
Task checkWeightTask(100, -1, &checkWeightCallback);

void setup() {
    // put your setup code here, to run once:
    pixels = new Adafruit_NeoPixel(numPixels, pin, pixelFormat);

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