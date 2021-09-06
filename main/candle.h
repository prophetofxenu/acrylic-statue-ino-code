#ifndef CANDLE_H
#define CANDLE_H

#include <FastLED.h>


class CandleM {

private:
  const int minV = 100;
  const int maxVelocity = 5;

  CHSV color;
  CRGB *leds;
  int numLeds;
  int velocity;

public:
  CandleM(CRGB color, CRGB *leds, int numLeds);
  void exec();

};


#endif
