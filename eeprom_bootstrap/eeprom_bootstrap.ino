#include <EEPROM.h>
#define EEPROM_MODE 0

void setup() {
  // put your setup code here, to run once:
  EEPROM.update(EEPROM_MODE, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}
