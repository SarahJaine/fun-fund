#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NUMPIXELS     20
#define DELAYVAL      250

/* choose brightness of LEDS
   =========================
  Examples: 0   = off
            50  = 50% brightness
            100 = full brightness */
#define BRIGHTNESS    10


Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, 8, NEO_GRB + NEO_KHZ800);

float brightness = BRIGHTNESS;
int color = brightness / 100.00 * 255;
float totalNew;
float totalOldPixel;
float totalNewPixel;
float change;

void setup() {
  Serial.begin(9600);
  pixels1.begin();
  pixels2.begin();
  pixels3.begin();
  turnOff(0);
  show();
};


void loop() {
  if (Serial.available() > 1) {

    totalNew = getDisplayTotal();
    totalNewPixel = truncateToPixel(totalNew);
    change = totalNewPixel - totalOldPixel;

    // if funds decreasing, turn off lights
    if (change < 0) {
      for (int i = totalOldPixel; i >= totalNewPixel; i--) {
        turnOff(i);
        delay(DELAYVAL);
      };
    }

    // if funds increasing, turn on lights
    else if (change > 0) {
      for (int i = totalOldPixel; i < totalNewPixel; i++) {
        turnOn(i);
        delay(DELAYVAL);
      };
    };


    // if funds are empty, turn first light red
    if (totalNew <= 0) {
      turnOneRed();
      show();
    }

    // if funds are less than $100, turn first light yellow
    else if (totalNew < 100) {
      turnOneYellow();
      show();
    };

    totalOldPixel = totalNewPixel;
  };
};

float getDisplayTotal() {
  float incoming;
  incoming = Serial.parseFloat();
  if (incoming > 2000) {
    return 2000.00;
  }
  else if (incoming < 0) {
    return 0.00;
  }
  else {
    return incoming;
  };
};

int truncateToPixel(float x) {
  return trunc(x / 100);
};

void show() {
  pixels1.show();
  pixels2.show();
  pixels3.show();
};

void turnOff(int z) {
  pixels1.setPixelColor(z, pixels1.Color(0, 0, 0));
  pixels2.setPixelColor(z, pixels2.Color(0, 0, 0));
  pixels3.setPixelColor(z, pixels3.Color(0, 0, 0));
  show();
};

void turnOn(int z) {
  pixels1.setPixelColor(z, pixels1.Color(color, color, color));
  pixels2.setPixelColor(z, pixels2.Color(color, color, color));
  pixels3.setPixelColor(z, pixels3.Color(color, color, color));
  show();
};

void turnOneRed() {
  pixels1.setPixelColor(0, pixels1.Color(color, 0, 0));
  pixels2.setPixelColor(0, pixels2.Color(color, 0, 0));
  pixels3.setPixelColor(0, pixels3.Color(color, 0, 0));
  show();
};

void turnOneYellow() {
  pixels1.setPixelColor(0, pixels1.Color(color, color, 0));
  pixels2.setPixelColor(0, pixels2.Color(color, color, 0));
  pixels3.setPixelColor(0, pixels3.Color(color, color, 0));
  show();
};
