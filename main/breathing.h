#ifndef BREATHING_H
#define BREATHING_H

#include <FastLED.h>


class Breathing {

private:
  CHSV *colors;
  int numColors;
  CHSV currentColor;
  int currentColorIdx;
  uint8_t theta;
  CRGB *leds;
  int numLeds;

public:
  Breathing(CHSV *colors, int numColors, CRGB *leds, int numLeds);
  void exec();

};


#endif
