#ifndef BREATHING_H
#define BREATHING_H

#include "mode.h"

#include <FastLED.h>


class Breathing : public Mode {

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
