#ifndef MARQUEE_H
#define MARQUEE_H

#include "mode.h"

#include <FastLED.h>


class Marquee : public Mode {

private:
  CHSV color;
  int _delay;
  CRGB *leds;
  int numLeds;
  int alternate;

public:
  Marquee(CHSV color, int delay, CRGB *leds, int numLeds);
  Marquee(CHSV color, CRGB *leds, int numLeds) : 
    Marquee(color, 75, leds, numLeds) {}
  void exec();

};


#endif
