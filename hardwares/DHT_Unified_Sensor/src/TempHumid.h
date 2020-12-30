#pragma once

#include "DHTlib/DHT.h"
#include "Arduino.h"

#define DHTTYPE DHT22
#define DHTPIN 8

void TempHumidInit();
float ReadTemp();
float ReadHumid();