#include "breathing.h"


Breathing::Breathing(CHSV *colors, int numColors, CRGB *leds, int numLeds) {
  this->colors = colors;
  this->numColors = numColors;
  currentColorIdx = 0;
  currentColor = rgb2hsv_approximate(colors[currentColorIdx++]);
  theta = 162;
  this->leds = leds;
  this->numLeds = numLeds;
}


void Breathing::exec() {
  if (theta == 128) {
    currentColor = rgb2hsv_approximate(colors[currentColorIdx++]);
    if (currentColorIdx >= numColors)
      currentColorIdx = 0;
  }
  currentColor.v = abs(cos8(theta++));
  for (int i = 0; i < numLeds; i++) {
    leds[i] = currentColor;
  }
  FastLED.show();
  delay(50);
}
