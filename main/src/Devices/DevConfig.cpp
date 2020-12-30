#include "Device.h"
CtrlUnit DevConfig[COMMON_DEV_LIMIT];
int devConfigCnt = 0;
int devCfgVer = -1;

extern FuncPtr GetCtrlFunc(String sHid, bool swCond);
extern int GetExIdByHid(const String &sHid);

void ParseTextCfg(const String &str)
{
    StaticJsonDocument<MAX_CONFIG_CHAR_SIZE> devcfg;
    deserializeJson(devcfg, str);
    devConfigCnt = 0;
    for(auto j:devcfg[F("cfg")].as<JsonArray>())
    {
        String hid = j[F("dev_hid")];
        int exid = GetExIdByHid(hid);
        if (exid == -1)
        {
            Serial.println(F("[hid to ex id failed]"));
            return;
        }
        DevConfig[devConfigCnt].idevSerial = exid;

        String op = j[F("condition")];
        if (op == F("gt"))
        {
            DevConfig[devConfigCnt].operand = CMP_OP::OP_GT;
        }
        else if (op == F("lt"))
        {
            DevConfig[devConfigCnt].operand = CMP_OP::OP_LT;
        }
        else if (op == F("eq"))
        {
            DevConfig[devConfigCnt].operand = CMP_OP::OP_EQ;
        }
        else
        {
            Serial.print(F("[unexpected operand]"));
            return;
        }

        DevConfig[devConfigCnt].val = j["val"];
        DevConfig[devConfigCnt].solCnt = 0;
        for (auto so:j["sol"].as<JsonArray>())
        {
            String odev_hid = so["dev_hid"];
            bool ctrl = so["operate"];
            auto fptr = GetCtrlFunc(odev_hid, ctrl);
            if ( fptr == nullptr )
            {
                Serial.println(F("[can not translate operate!!]"));
                return;
            }
            DevConfig[devConfigCnt].solActions[DevConfig[devConfigCnt].solCnt++] = fptr;
        }
        devConfigCnt++;
    }
}
void ListConfig()
{
    for (int i = 0;i != devConfigCnt;++i)
    {
        Serial.print("[Hid:");
        Serial.print(DevConfig[i].idevSerial);
        Serial.println("]");

        for(int j = 0;j != DevConfig[i].solCnt;++j)
        {
            Serial.println("[executing sol]");
            DevConfig[i].solActions[j]();
            Serial.println("[end of executing sol]");
        }
    }
}
bool CheckCfgVer(int version)
{
    return version > devCfgVer;
}