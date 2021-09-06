#include "solid.h"


Solid::Solid(CRGB color, CRGB *leds, int numLeds) {
  this->color = color;
  this->leds = leds;
  this->numLeds = numLeds;
}


void Solid::exec() {
  for (int i = 0; i < numLeds; i++) {
    leds[i] = color;
  }
  FastLED.show();
  delay(100);
}
