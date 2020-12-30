#include "DirtMoisture.h"

void setup()
{
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
}
void loop()
{
  Serial.print("[ dirt moisture : ");
  Serial.print(GetDirtMoisture() * 100.0);
  Serial.println(" % ]");
  delay(100);
}