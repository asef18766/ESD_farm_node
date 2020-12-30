#include "TempHumid.h"

DHT dht(DHTPIN, DHTTYPE);

void TempHumidInit()
{
    dht.begin();
}

float ReadTemp()
{
    return dht.readTemperature();
}

float ReadHumid()
{
    return dht.readHumidity();
}