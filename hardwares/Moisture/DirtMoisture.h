#pragma once
#include <Arduino.h>

#define DIRT_MOISTURE_PIN A0

#define AirValue 920
#define WaterValue 750

inline float GetDirtMoisture()
{
  float cur = analogRead(DIRT_MOISTURE_PIN);
  return ( AirValue - cur ) / (AirValue - WaterValue);
}