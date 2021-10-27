
int currentMode;
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
