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

void setup() {

  matrix.begin();
  matrix.setTextWrap(false);

  matrix.setCursor(2, 15);
  uint8_t w = 0;
  char Str1[ ] = "$2";
  char Str2[ ] = ",";
  char Str3[ ] = "000";

  matrix.setFont(&FreeMono9pt7b);
  matrix.setTextSize(1);
  matrix.print(Str1);

//  Comma not in monospace
  matrix.setFont(&FreeSans9pt7b);
  matrix.print(Str2);
  
  matrix.setFont(&FreeMono9pt7b);
  matrix.print(Str3);
}

void loop() {
  // do nothing
}

