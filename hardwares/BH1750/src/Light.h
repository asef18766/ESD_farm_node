#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "BH1750lib/BH1750.h"

void LightInit();
float ReadLux();