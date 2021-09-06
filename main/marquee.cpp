#include "marquee.h"


Marquee::Marquee(CHSV color, CRGB *leds, int numLeds) {
  this->color = color;
  this->leds = leds;
  this->numLeds = numLeds;
  alternate = 0;
}


void Marquee::exec() {
  Serial.println(alternate);
  for (int i = 0; i < numLeds; i++) {
    if (i % 3 == alternate)
      leds[i] = color;
    else
      leds[i] = CHSV(0, 0, 0);
  }
  alternate = (alternate + 1) % 3;
  FastLED.show();
  delay(75);
}
