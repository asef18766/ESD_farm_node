#pragma once
#include <ArduinoJson.h>
#include "../config.h"
struct Device
{
    char *hid;
    int ex_id;
    bool input; // whether is input device

    void (*Tick)(StaticJsonDocument<JSON_BUFFER_SIZE> &data);
};

class DeviceHandler
{
    public:
    static DeviceHandler* GetInstance();
    void SetUpDeviceMap(StaticJsonDocument<JSON_BUFFER_SIZE> &map);
    void Tick();

    private:
    static DeviceHandler* instance;

    // setup watches for all devices
    DeviceHandler();
};
