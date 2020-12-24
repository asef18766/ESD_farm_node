#include "./device.h"

DeviceHandler *DeviceHandler::instance = nullptr; 
void BH1750handler(StaticJsonDocument<JSON_BUFFER_SIZE> &data);

// [NOTE] read device shall come first
// [NOTE] write device shall implement an interface to obtain work units
Device TARGET_DEVICE[] = {
    {"a0dc72230878a4cfc03cb1da52ad8e", 0, true, BH1750handler},
    {"cb4d49748f0dc9fc17a49b7b441ff8", 0, true, BH1750handler},
    {"f86e193224fee588ddb5036ea0548d", 0, true, BH1750handler},
    {"e6e81072d2289b4e062b4b95a9fcbe", 0, true, BH1750handler}
};
int TARGET_DEVICE_COUNT = 4;

void BH1750handler(StaticJsonDocument<JSON_BUFFER_SIZE> &data)
{
    data["amount"] = 487.63;
}

DeviceHandler::DeviceHandler() {}

DeviceHandler* DeviceHandler::GetInstance()
{
    Serial.println("[trying GetInstance]");
    if(DeviceHandler::instance == nullptr)
    {
        DeviceHandler::instance = new DeviceHandler;
    }
    Serial.println("[end of GetInstance]");
    return DeviceHandler::instance;
}
void DeviceHandler::SetUpDeviceMap(StaticJsonDocument<JSON_BUFFER_SIZE> &map)
{
    Serial.println("[Handler Start Setting Up Device Map]");
    for(int i = 0;i != TARGET_DEVICE_COUNT;++i)
    {
        TARGET_DEVICE[i].ex_id = map["device_map"][TARGET_DEVICE[i].hid];
    }
    Serial.println("[Handler End Setting Up Device Map]");
}

// the update routine for every tick at serve state
void DeviceHandler::Tick()
{
    Serial.println("[Handler Start Tick]");
    for(int i = 0;i != TARGET_DEVICE_COUNT;++i)
    {
        StaticJsonDocument<JSON_BUFFER_SIZE> dev;
        TARGET_DEVICE[i].Tick(dev);
        dev["token"] = NODE_TOKEN;
        dev["device"] = TARGET_DEVICE[i].ex_id;
        String de_str;
        serializeJson(dev, de_str);
        Serial.println(de_str);
    }
    Serial.println("[Handler End Tick]");
}