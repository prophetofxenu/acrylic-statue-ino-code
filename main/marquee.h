#ifndef MARQUEE_H
#define MARQUEE_H

#include "mode.h"

#include <FastLED.h>


class Marquee : public Mode {

private:
  CHSV color;
  CRGB *leds;
  int numLeds;
  int alternate;

public:
  Marquee(CHSV color, CRGB *leds, int numLeds);
  void exec();

};


#endif
