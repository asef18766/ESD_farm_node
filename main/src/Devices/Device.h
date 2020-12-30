#pragma once
#include <ArduinoJson.h>
#include "../config.h"
#define COMMON_DEV_LIMIT 30
#define MAX_CONFIG_CHAR_SIZE 1<<15

typedef void (*FuncPtr)();
typedef bool (*CMPPtr)(float a, float b);
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
    OP_GT = 0,
    OP_LT = 1,
    OP_EQ = 2
};

struct OutDevAction
{
    char *hid;
    FuncPtr trueAction;
    FuncPtr falseAction;
};

struct CtrlUnit
{
    int idevSerial;
    CMP_OP operand;
    float val;
    int solCnt;
    FuncPtr solActions[COMMON_DEV_LIMIT];
};

class DeviceHandler
{
    public:
    static DeviceHandler* GetInstance();
    void SetUpDeviceMap(StaticJsonDocument<JSON_BUFFER_SIZE> &map);
    // called for each update routine for both input & output device
    void Tick();
    // call when receive notification of new config available
    void CkCfgUpdate(String &str);

    private:
    static DeviceHandler* instance;

    // setup watches for all devices
    DeviceHandler();
};

void ParseTextCfg(const String &str);
void ListConfig();