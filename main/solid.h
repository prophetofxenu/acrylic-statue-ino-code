#ifndef SOLID_H
#define SOLID_H

#include "mode.h"

#include <FastLED.h>


class Solid : public Mode {

private:
  CRGB color;
  CRGB *leds;
  int numLeds;

public:
  Solid(CRGB color, CRGB *leds, int numLeds);
  void exec();

};


#endif
