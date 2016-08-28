#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS     20
#define DELAYVAL      250

/* choose brightness of LEDS
 * =========================
  Examples: 0   = off
            50  = 50% brightness
            100 = full brightness */
#define BRIGHTNESS    20


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float brightness = BRIGHTNESS;
int color = brightness / 100.00 * 255;
float totalNew;
float totalOldPixel;
float totalNewPixel;
float change;


void setup() {
  Serial.begin(9600);
  pixels.begin();

  // little light show to let users know this is working
  for (int i = 0; i < 2; i++) {
    pixels.setPixelColor(0, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
    pixels.show();
    delay(DELAYVAL);
  };
};


void loop() {

  if (Serial.available() > 1) {

    totalNew = getDisplayTotal();
    totalNewPixel = truncateToPixel(totalNew);
    change = totalNewPixel - totalOldPixel;

    // if funds decreasing, turn off lights
    if (change < 0) {
      for (int i = totalOldPixel; i >= totalNewPixel; i--) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(DELAYVAL);
      };
    }

    // if funds increasing, turn on lights
    else if (change > 0) {
      for (int i = totalOldPixel; i < totalNewPixel; i++) {
        pixels.setPixelColor(i, pixels.Color(color, color, color));
        pixels.show();
        delay(DELAYVAL);
      };
    };


    // if funds are empty, turn first light red
    if (totalNew <= 0) {
      pixels.setPixelColor(0, pixels.Color(color, 0, 0));
      pixels.show();
    }
    
    // if funds are less than $100, turn first light yellow
    else if (totalNew < 100) {
      pixels.setPixelColor(0, pixels.Color(color, color, 0));
      pixels.show();
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
