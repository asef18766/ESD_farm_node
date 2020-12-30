#pragma once
#define FLOWMETER_PIN 2
#define PUMP_PIN 6
#include <Arduino.h>

void PumpSetUp();
void OnPump();
void OffPump();
void PumpTick();
float ReadFlowMeter();
