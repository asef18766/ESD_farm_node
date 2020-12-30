#include "./device.h"

DeviceHandler *DeviceHandler::instance = nullptr; 
const CMPPtr comp_ops[] = {
    [](float a, float b){return a > b;},
    [](float a, float b){return a < b;},
    [](float a, float b){return a == b;}
};

extern int TARGET_DEVICE_COUNT;
extern Device TARGET_DEVICE[];
extern CtrlUnit DevConfig[COMMON_DEV_LIMIT];
extern int devConfigCnt;

extern bool CheckCfgVer(int version);
extern bool CondCheck(int idev, float val, CMPPtr operand);
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
    Serial.println("[Current device mapping]");
    for(int i = 0;i != TARGET_DEVICE_COUNT;++i)
    {
        Serial.print(TARGET_DEVICE[i].hid);
        Serial.print(':');
        Serial.println(TARGET_DEVICE[i].ex_id);
    }
    Serial.println("[End of device mapping]");
}

// the update routine for every tick at serve state
void DeviceHandler::Tick()
{
    Serial.println("[Handler Start Tick]");
    int i = 0;

    // obtain input values
    for(;i != TARGET_DEVICE_COUNT;++i)
    {
        if (!TARGET_DEVICE[i].input)
            break;
        StaticJsonDocument<JSON_BUFFER_SIZE> dev;
        TARGET_DEVICE[i].Tick(dev);
        dev["token"] = NODE_TOKEN;
        dev["device"] = TARGET_DEVICE[i].ex_id;
        String de_str;
        serializeJson(dev, de_str);
        Serial.println(de_str);
    }
    // process condiction
    for ( int u = 0 ; u != devConfigCnt ; ++u )
    {
        if (CondCheck(DevConfig[u].idevSerial, DevConfig[u].val, comp_ops[DevConfig[u].operand]))
        {
            for (int j = 0;j != DevConfig[u].solCnt;++j)
                DevConfig[u].solActions[j]();
            break;
        }
    }
    // obtain output values
    for(;i != TARGET_DEVICE_COUNT;++i)
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
void DeviceHandler::CkCfgUpdate(String &str)
{
    Serial.println(F("[Start Checking Update]"));
    StaticJsonDocument<87> doc;
    deserializeJson(doc, str);
    if (CheckCfgVer(doc["version"]))
    {
        Serial.println(F("[Detected Avaible Update]"));
        Serial.println(str);
    }
    Serial.println(F("[End of Checing Update]"));
}