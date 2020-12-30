#include "src/TempHumid.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  TempHumidInit();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  Serial.println(ReadHumid());
  Serial.println(ReadTemp());
  
}