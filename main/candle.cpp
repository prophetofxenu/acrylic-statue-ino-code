#include "candle.h"


CandleM::CandleM(CRGB color, CRGB *leds, int numLeds) {
  this->color = rgb2hsv_approximate(color);
  this->leds = leds;
  this->numLeds = numLeds;
  velocity = 0;
}


void CandleM::exec() {
  int next = random(7) - 3;
  velocity += next;
  if (velocity > maxVelocity)
    velocity = maxVelocity;
  else if (velocity < -1 * maxVelocity)
    velocity = -1 * maxVelocity;

  if (color.v + velocity > 255) {
    color.v = 255;
    velocity = -1 * maxVelocity;
  } else if (color.v + velocity < minV) {
    color.v = minV;
    velocity = maxVelocity;
  } else {
    color.v += velocity;
  }

  for (int i = 0; i < numLeds; i++) {
    leds[i] = color;
  }
  FastLED.show();
  delay(100);

}
