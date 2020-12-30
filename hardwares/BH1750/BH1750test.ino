#include "src/Light.h"

void setup(){
  LightInit();
  Serial.begin(9600);
  Serial.println("BH1750 Test begin");
}


void loop() {
  delay(1000);
  Serial.println(ReadLux());
}
