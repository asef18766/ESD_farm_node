#include "./device.h"

DeviceHandler *DeviceHandler::instance = nullptr; 
extern int TARGET_DEVICE_COUNT;
extern Device TARGET_DEVICE[];

extern void ParseTextCfg(const String &str);

DeviceHandler::DeviceHandler() {}
DeviceHandler* DeviceHandler::GetInstance()
{
    Serial.println(F("[trying GetInstance]"));
    if(DeviceHandler::instance == nullptr)
    {
        DeviceHandler::instance = new DeviceHandler;
    }
    Serial.println(F("[end of GetInstance]"));
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
