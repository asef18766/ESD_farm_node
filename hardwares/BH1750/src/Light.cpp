#include "Light.h"

BH1750 lightMeter;
void LightInit()
{
    // Initialize the I2C bus (BH1750 library doesn't do this automatically)
    Wire.begin();
    // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

    lightMeter.begin();
}

float ReadLux()
{  
  return lightMeter.readLightLevel();
}