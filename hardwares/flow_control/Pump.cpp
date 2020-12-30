#include "Pump.h"

volatile int flow_frequency; // Measures flow meter pulses
bool PUMP_SWITCH = true;

void flow() // Interrupt function
{
   flow_frequency++;
}

void PumpSetUp()
{
   pinMode(PUMP_PIN, OUTPUT);
   pinMode(FLOWMETER_PIN, INPUT);
   attachInterrupt(digitalPinToInterrupt(FLOWMETER_PIN), flow, RISING); 
   sei();
}

float ReadFlowMeter()
{
   // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
   float ml = (( flow_frequency / 7.5 ) * 1000) / 60;
   flow_frequency = 0;
   return ml;
}

void PumpTick()
{
   if(PUMP_SWITCH)
   {
      analogWrite(PUMP_PIN, 255);
   }
   else
   {
      analogWrite(PUMP_PIN, 0);
   }
}

void OnPump()
{
   PUMP_SWITCH = true;
   Serial.println("{turn on}");
}

void OffPump()
{
   PUMP_SWITCH = false;
   Serial.println("{turn off}");
}
