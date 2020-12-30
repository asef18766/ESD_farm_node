# include "Device.h"
// this section deal with the fuctionality of device work

void BH1750handler(StaticJsonDocument<JSON_BUFFER_SIZE> &data);

// [NOTE] read device shall come first
// [NOTE] write device shall implement an interface to obtain work units
Device TARGET_DEVICE[] = {
    {"a0dc72230878a4cfc03cb1da52ad8e", -1, true, BH1750handler},
    {"cb4d49748f0dc9fc17a49b7b441ff8", -1, true, BH1750handler},
    {"f86e193224fee588ddb5036ea0548d", -1, true, BH1750handler},
    {"e6e81072d2289b4e062b4b95a9fcbe", -1, true, BH1750handler}
};
int TARGET_DEVICE_COUNT = 4;
float history_record[COMMON_DEV_LIMIT];


int GetExIdByHid(const String &sHid)
{
    for(int u = 0 ; u != TARGET_DEVICE_COUNT ; ++u)
    {
        if (sHid == TARGET_DEVICE[u].hid)
        {
            return TARGET_DEVICE[u].ex_id;
        }
    }
    return -1;
}

// this section is only for testing
float randfloat()
{
    static int32_t x = 0xfaceb00c;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    float res;
    memcpy(&res, &x, 4);
    return res;
}
//end of section


void BH1750handler(StaticJsonDocument<JSON_BUFFER_SIZE> &data)
{
    //TODO: implement real handler
    static int idcnt = 0;

    float sampleF = randfloat();
    if (sampleF < 0)
        sampleF = -sampleF;
    
    data["amount"] =  sampleF;
    
    history_record[idcnt] = sampleF;
    idcnt = (idcnt  + 1) % TARGET_DEVICE_COUNT;
}
void OnAct()
{
    Serial.println("[On!!!]");
}
void OffAct()
{
    Serial.println("[Off!!!]");
}
OutDevAction OUT_CTRL[] = {
    {"839bc5bba6a76514868ed84275839c", OnAct, OffAct}
};
int OUT_CTRL_CNT = 1;
FuncPtr GetCtrlFunc(String sHid, bool swCond)
{
    for (int i = 0;i != OUT_CTRL_CNT;++i)
    {
        if (sHid == OUT_CTRL[i].hid)
        {
            return (swCond)? OUT_CTRL[i].trueAction:OUT_CTRL[i].falseAction;
        }
    }
    return nullptr;
}

int getRecordIndex(int idev)
{
    for (int i = 0; i != TARGET_DEVICE_COUNT; ++i)
    {
        if (TARGET_DEVICE[i].ex_id == idev)
        {
            return i;
        }
    }
    Serial.println(F("[error while obatain history index]"));
    return -1;
}

bool CondCheck(int idev, float val, CMPPtr operand)
{
    int idx = getRecordIndex(idev);
    if (idx == -1)
    {
        return false;
    }

    Serial.print(F("[Check for device"));
    Serial.print(idev);
    Serial.print(F(" of val "));
    Serial.print(history_record[idx]);
    Serial.print(F(" compares to "));
    Serial.print(val);
    Serial.println("]");

    return operand(history_record[idx], val);
}