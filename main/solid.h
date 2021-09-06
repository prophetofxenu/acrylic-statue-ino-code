#ifndef SOLID_H
#define SOLID_H

#include <Arduino.h>
#include <FastLED.h>


class Solid {

private:
  CRGB color;
  CRGB *leds;
  int numLeds;

public:
  Solid(CRGB color, CRGB *leds, int numLeds);
  void exec();

};


#endif
