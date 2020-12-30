#include "Pump.h"
#include "Utils.h"

unsigned long tBuf;
void setup()
{
   PumpSetUp();
   Serial.begin(9600);
   tBuf = millis();
}
void loop()
{
   PumpTick();
   delay(1000);
   if (DelayAsync(tBuf, 1000))
   {
      Serial.print(ReadFlowMeter()), Serial.println(" ml");
   }
   while(Serial.available())
   {
      String res = Serial.readString();
      res.trim();

      if (res == "on")
      {
         OnPump();
      }
      else if(res == "off")
      {
         OffPump();
      }
   }
}