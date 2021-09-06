#ifndef SPECTRUMCYCLE_H
#define SPECTRUMCYCLE_H

#include "mode.h"

#include <FastLED.h>


class SpectrumCycle : public Mode {

private:
  CHSV color;
  CRGB *leds;
  int numLeds;

public:
  SpectrumCycle(CRGB *leds, int numLeds);
  void exec();

};


#endif
