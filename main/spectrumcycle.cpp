#include "spectrumcycle.h"


SpectrumCycle::SpectrumCycle(CRGB *leds, int numLeds) {
  this->color = CHSV(0, 255, 255);
  this->leds = leds;
  this->numLeds = numLeds;
}


void SpectrumCycle::exec() {
  for (int i = 0; i < numLeds; i++)
    leds[i] = color;
  color.h++;
  FastLED.show();
  delay(100);
}
