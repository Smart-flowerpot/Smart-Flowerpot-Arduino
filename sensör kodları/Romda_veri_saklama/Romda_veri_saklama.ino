#include <EEPROM.h>

int i;
void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  Serial.println("Start");
  EEPROM.write(0,10);
  EEPROM.write(1,20);
  EEPROM.write(2,30);
  EEPROM.write(3,40);
  Serial.println("Finish");
  delay(3000);
}

void loop() {
  for (int i=0; i<4; i++){
    Serial.println((EEPROM.read(i)));
    delay(1000);
  }

}
