#include "solid.h"
#include "breathing.h"
#include "candle.h"

#include <FastLED.h>
#include <EEPROM.h>

#define LED_PIN 3
#define NUM_LEDS 4
#define PWR_BTN 5
#define MODE_BTN 4

#define EEPROM_MODE 0

CRGB leds[NUM_LEDS];

#define NUM_MODES 6
enum Mode {
  SOLID_BLUE,
  SOLID_YELLOW,
  BREATHING_CYCLE,
  CANDLE_ORANGE,
  CANDLE_YELLOW,
  CANDLE_GREEN
};

Mode mode = SOLID_BLUE;
void nextMode() {
  int m = (int) mode;
  m = (m + 1) % NUM_MODES;
  EEPROM.update(EEPROM_MODE, m);
  mode = (Mode) m;
}

CHSV orange(28, 255, 255);
CHSV blue(133, 255, 255);
CHSV yellow(39, 255, 255);
CHSV green(87, 255, 255);

Solid solidBlue(
  blue,
  leds,
  NUM_LEDS
);
Solid solidYellow(
  yellow,
  leds,
  NUM_LEDS
);
CHSV breathingCycleColors[] = { orange, yellow, green };
Breathing breathingCycle(
  breathingCycleColors,
  sizeof(breathingCycleColors) / sizeof(CHSV),
  leds,
  NUM_LEDS
);
CandleM candleOrange(
  orange,
  leds,
  NUM_LEDS
);
CandleM candleYellow(
  yellow,
  leds,
  NUM_LEDS
);
CandleM candleGreen(
  green,
  leds,
  NUM_LEDS
);


void setup() {
  // seed RNG
  randomSeed(analogRead(0));
  // init LEDs
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);
  // read mode, init if necessary
  mode = EEPROM.read(EEPROM_MODE);
  if (mode >= NUM_MODES) {
    EEPROM.update(EEPROM_MODE, 0);
    mode = 0;
  }
  // setup buttons
  pinMode(PWR_BTN, INPUT);
  digitalWrite(PWR_BTN, HIGH);
  pinMode(MODE_BTN, INPUT);
  digitalWrite(MODE_BTN, HIGH);

  Serial.begin(9600);
}


bool poweredOn = true;


void loop() {

  if (digitalRead(PWR_BTN) == LOW) {
    poweredOn = !poweredOn;
    do {
      delay(100);
    } while (digitalRead(PWR_BTN) == LOW);
  } else if (digitalRead(MODE_BTN) == LOW) {
    nextMode();
    do {
      delay(100);
    } while (digitalRead(MODE_BTN) == LOW);
  }

  if (poweredOn) {
    switch(mode) {
      case SOLID_BLUE:
        solidBlue.exec();
        break;
      case SOLID_YELLOW:
        solidYellow.exec();
        break;
      case BREATHING_CYCLE:
        breathingCycle.exec();
        break;
      case CANDLE_ORANGE:
        candleOrange.exec();
        break;
      case CANDLE_YELLOW:
        candleYellow.exec();
        break;
      case CANDLE_GREEN:
        candleGreen.exec();
        break;
    }
  } else {
    FastLED.clear(true);
    FastLED.show();
    delay(100);
  }
}
