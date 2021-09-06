#ifndef RAINBOW_H
#define RAINBOW_H

#include "mode.h"

#include <FastLED.h>


class Rainbow : public Mode {

private:
  CHSV color;
  CRGB *leds;
  int numLeds;

public:
  Rainbow(CRGB *leds, int numLeds);
  void exec();

};


#endif
