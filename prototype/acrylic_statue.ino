#include <FastLED.h>
#include <EEPROM.h>

#define LED_PIN 3
#define NUM_LEDS 4

#define EEPROM_MODE 0
#define EEPROM_RESET 1


enum Mode {
  SOLID,
  BREATHING,
  CANDLE,
  RAINBOW
};
Mode nextMode(Mode mode);


CRGB leds[4];
Mode mode = BREATHING;
bool reset = true;


void solidColor(void);
void breathing(void);
void candle(void);
void rainbow(void);


void setup() {
  // put your setup code here, to run once:
  // seed RNG
  randomSeed(analogRead(0));
  // init LEDs
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  // read mode
  mode = EEPROM.read(EEPROM_MODE);
  // check if mode switch triggered
  int reset = EEPROM.read(EEPROM_RESET);
  if (reset == 1) {
    mode = nextMode(mode);
    EEPROM.update(EEPROM_MODE, mode);
  }
  // reset mode switch
  EEPROM.update(EEPROM_RESET, 1);
}


void loop() {
  // put your main code here, to run repeatedly:

  switch (mode) {
    
    case SOLID:
      solidColor();
      break;

    case BREATHING:
      breathing();
      break;

    case CANDLE:
      candle();
      break;

    case RAINBOW:
      rainbow();
      break;
      
  }

  // check if mode switch can be disabled
  if (reset && millis() > 5000) {
    EEPROM.update(EEPROM_RESET, 0);
    reset = false;
  }
}


Mode nextMode(Mode mode) {
  int m = (int) mode;
  m = (m + 1) % 4; // add 1, mod by number of modes
  return (Mode) m;
}


void solidColor(void) {
  static bool set = false;
  if (!set) {
    CHSV color_hsv(96, 255, 255);
    CRGB color_rgb;
    hsv2rgb_rainbow(color_hsv, color_rgb);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = color_rgb;
    }
    FastLED.show();
    set = true;
  }
  delay(1000);
}


void breathing(void) {
  static CHSV color(96, 255, 255);
  static uint8_t theta = 0;

  color.v = abs(cos8(theta));
  theta++;
  // skip values that are basically off
  if (theta == 100)
    theta = 162;

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
  delay(50);
}


void candle(void) {
  static CHSV color(96, 255, 200);
  const int minV = 100;
  const int maxVelocity = 5;
  static int velocity = 0;
  
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

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
  delay(100);
}


void rainbow(void) {
  static CHSV color(96, 255, 255);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
  color.h++;
  delay(100);
}
