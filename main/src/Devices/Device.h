#pragma once
#include <ArduinoJson.h>
#include "../config.h"
#define COMMON_DEV_LIMIT 1000
struct Device
{
    char *hid;
    // the communication id set by server
    int ex_id;
    // whether is input device
    bool input; 

    void (*Tick)(StaticJsonDocument<JSON_BUFFER_SIZE> &data);
};

enum CMP_OP
{
    OP_GT,
    OP_LT,
    OP_EQ
};

struct OutDevAction
{
    char *hid;
    void (*true_action)();
    void (*false_action)();
}

struct CtrlUnit
{
    int idevSerial;
    CMP_OP operand;
    float val;
    void (*solActions)()[COMMON_DEV_LIMIT];
}

class DeviceHandler
{
    public:
    static DeviceHandler* GetInstance();
    void SetUpDeviceMap(StaticJsonDocument<JSON_BUFFER_SIZE> &map);
    // called for each update routine for both input & output device
    void Tick();

    private:
    static DeviceHandler* instance;

    // setup watches for all devices
    DeviceHandler();
};
