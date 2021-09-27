#include "marquee.h"


Marquee::Marquee(CHSV color, int delay, CRGB *leds, int numLeds) {
  this->color = color;
  _delay = delay;
  this->leds = leds;
  this->numLeds = numLeds;
  alternate = 0;
}


void Marquee::exec() {
  for (int i = 0; i < numLeds; i++) {
    if (i % 3 == alternate)
      leds[i] = color;
    else
      leds[i] = CHSV(0, 0, 0);
  }
  alternate = (alternate + 1) % 3;
  FastLED.show();
  delay(_delay);
}
