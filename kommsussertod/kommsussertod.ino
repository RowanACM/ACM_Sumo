#include <PololuBuzzer.h>
PololuBuzzer buzzer;
const char KOMMSUSSERTOD[] PROGMEM = "L4 V16 T130";
void setup() {
  // put your setup code here, to run once:
  buzzer.playFromProgramSpace(KOMMSUSSERTOD);
}

void loop() {}
