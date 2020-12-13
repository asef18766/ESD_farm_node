#include "./device.h"

DeviceHandler *DeviceHandler::instance = nullptr; 
void BH1750handler(StaticJsonDocument<JSON_BUFFER_SIZE> &data);

Device TARGET_DEVICE[] = {
    {"deadbeef", 0, true, BH1750handler},
    {"deadbeef2", 0, true, BH1750handler}
};
int TARGET_DEVICE_COUNT = 2;

void BH1750handler(StaticJsonDocument<JSON_BUFFER_SIZE> &data)
{

}

DeviceHandler::DeviceHandler() {}

DeviceHandler* DeviceHandler::GetInstance()
{
    if(DeviceHandler::instance == nullptr)
    {
        DeviceHandler::instance = new DeviceHandler;
    }
    return DeviceHandler::instance;
}
void DeviceHandler::SetUpDeviceMap(StaticJsonDocument<JSON_BUFFER_SIZE> &map)
{
    for(int i = 0;i != TARGET_DEVICE_COUNT;++i)
    {
        TARGET_DEVICE[i].ex_id = map["device_map"][TARGET_DEVICE[i].hid];
    }
}
void DeviceHandler::Tick()
{
    for(int i = 0;i != TARGET_DEVICE_COUNT;++i)
    {
        StaticJsonDocument<JSON_BUFFER_SIZE> dev;
        TARGET_DEVICE[i].Tick(dev);
    }
}