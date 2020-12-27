#include "./State.h"
#include "../Devices/Device.h"
DeviceHandler* ServeState::config;
ServeState::ServeState()
{
    this->StateName = "RunningState";
    this->config = DeviceHandler::GetInstance();
    Serial.println("create serve state");

}

void ServeState::OnUpdate(StateHanlder &sh)
{
    Serial.println("[at serve state update]");
    
    Serial.print("[server state receive: ");
    Serial.print(sh.Info);
    Serial.println("]");
    if (sh.Info[0] == '*' && sh.Info[1] == '*')
    {
        sh.Info.remove(0,2);
        Serial.println("[start parsing cfg]");
        ParseTextCfg(sh.Info);
        Serial.println("[end parsing cfg]");
        Serial.println(F("[config]"));
        ListConfig();
        Serial.println(F("[end of config]"));
    }
    else
    {
        config->Tick();
    }
    
    Serial.println("[end of serve state update]");
}