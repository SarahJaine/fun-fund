#include <Adafruit_GFX.h>   // Core graphics library
#include <gfxfont.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <RGBmatrixPanel.h> // Hardware-specific library

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
String total;
String displayTotal;
int displayLength;
int hortizontalStart;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  // Set my text style
  matrix.begin();
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setFont(&FreeMono9pt7b);
}

void loop() {
  if (Serial.available() > 0) {
    total = getTotal();
    Serial.println(total);
    displayTotal = getDisplayTotal(total);
    displayLength = getDisplayLength(displayTotal);

    // clear screen and set cursor
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    hortizontalStart = (4 - displayLength) * 6.6 + 2;
    matrix.setCursor(hortizontalStart, 19);

    matrix.print('$');
    matrix.print(displayTotal[0]);

    // change to sans for comma
    if (displayLength == 4) {
      matrix.setFont(&FreeSans9pt7b);
      matrix.print(",");
      matrix.setFont(&FreeMono9pt7b);
    };

    matrix.print(displayTotal[1]);
    matrix.print(displayTotal[2]);
    matrix.print(displayTotal[3]);
  };
};

String getTotal() {
  String incomingTotal;
  incomingTotal = Serial.readStringUntil("\n");
  incomingTotal.trim();
  return incomingTotal;
}

String getDisplayTotal(String rawTotal) {
  int digits = 0;
  digits = rawTotal.length();
  if (digits > 4) {
    return "9999";
  }
  else {
    return rawTotal;
  };
};

int getDisplayLength(String x) {
  return (x.length());
};
