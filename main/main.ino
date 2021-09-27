#include "mode.h"
#include "solid.h"
#include "breathing.h"
#include "candle.h"
#include "spectrumcycle.h"
#include "rainbow.h"
#include "marquee.h"

#include <FastLED.h>
#include <EEPROM.h>

#define LED_PIN 3
#define NUM_LEDS 4
#define PWR_BTN 5
#define MODE_BTN 4

#define EEPROM_MODE 0

CRGB leds[NUM_LEDS];

CHSV orange(28, 255, 255);
CHSV blue(133, 255, 255);
CHSV yellow(39, 255, 255);
CHSV green(87, 255, 255);

#define MARQUEE_DELAY 150

Solid solidOrange(
  orange,
  leds,
  NUM_LEDS
);
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
Solid solidGreen(
  green,
  leds,
  NUM_LEDS
);
CandleM candleOrange(
  orange,
  leds,
  NUM_LEDS
);
CandleM candleBlue(
  blue,
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
Marquee marqueeOrange(
  orange,
  MARQUEE_DELAY,
  leds,
  NUM_LEDS
);
Marquee marqueeBlue(
  blue,
  MARQUEE_DELAY,
  leds,
  NUM_LEDS
);
Marquee marqueeYellow(
  yellow,
  MARQUEE_DELAY,
  leds,
  NUM_LEDS
);
Marquee marqueeGreen(
  green,
  MARQUEE_DELAY,
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
SpectrumCycle spectrumCycle(
  leds,
  NUM_LEDS
);
Rainbow rainbow(
  leds,
  NUM_LEDS
);

int currentMode;
Mode *modes[] = {
  &solidOrange,
  &solidBlue,
  &solidYellow,
  &solidGreen,
  &candleOrange,
  &candleBlue,
  &candleYellow,
  &candleGreen,
  &marqueeOrange,
  &marqueeBlue,
  &marqueeYellow,
  &marqueeGreen,
  &breathingCycle,
  &spectrumCycle,
  &rainbow
};
void nextMode() {
  currentMode = (currentMode + 1) % (sizeof(modes) / sizeof(Mode*));
  EEPROM.update(EEPROM_MODE, currentMode);
}


void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  // seed RNG
  randomSeed(analogRead(0));
  // init LEDs
  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);
  // read mode, init if necessary
  currentMode = EEPROM.read(EEPROM_MODE);
  if (currentMode >= sizeof(modes) / sizeof(Mode*)) {
    EEPROM.update(EEPROM_MODE, 0);
    currentMode = 0;
  }
  // setup buttons
  pinMode(PWR_BTN, INPUT);
  digitalWrite(PWR_BTN, HIGH);
  pinMode(MODE_BTN, INPUT);
  digitalWrite(MODE_BTN, HIGH);

  // clear LEDs just to be safe
  FastLED.clear();
  FastLED.show();

  Serial.println("setup done");
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
    modes[currentMode]->exec();
  } else {
    FastLED.clear(true);
    FastLED.show();
    delay(100);
  }
}
