#include "rainbow.h"


Rainbow::Rainbow(CRGB *leds, int numLeds) {
  color = CHSV(0, 255, 255);
  this->leds = leds;
  this->numLeds = numLeds;
}


void Rainbow::exec() {
  for (int i = 0; i < numLeds; i++) {
    CHSV tmp = color;
    tmp.h += i * 35;
    leds[i] = tmp;
  }
  color.h++;
  FastLED.show();
  delay(100);
}
