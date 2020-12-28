#include "./State.h"
#include "../Devices/device.h"

extern const String NODE_TOKEN;
extern const String DEVICE_CONFIG;

RegisterState::RegisterState()
{
    this->StateName = "RegisterState";
    Serial.println("[register state created]");
    Serial.println(DEVICE_CONFIG);
}
void RegisterState::OnUpdate(StateHanlder &sh)
{
    Serial.println("[this is Register state]");
    if(sh.Info != "")
    {
        StaticJsonDocument<JSON_BUFFER_SIZE> doc;
        DeserializationError error = deserializeJson(doc, sh.Info);
        if(error)
        {
            Serial.println("[error: can not deserialize target]");
            Serial.println(error.f_str());
            return;
        }
        DeviceHandler::GetInstance()->SetUpDeviceMap(doc);
        sh.Info = "init done";
        return;
    }
    Serial.println(DEVICE_CONFIG);
    sh.Info = "";
}