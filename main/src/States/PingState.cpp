#include "./State.h"

PingState::PingState()
{
    this->StateName = "PingState";
    Serial.println("[create ping state]");
    StaticJsonDocument<100> pingString;
    pingString["msg"] = "are you dead?";
    serializeJson(pingString, this->pingString);
}

void PingState::OnUpdate(StateHanlder &sh)
{
    Serial.println("[i am ping state]");
    if(sh.Info == "{\"msg\":\"i am alive\"}")
    {
        Serial.println("[successful connected to server]");
        sh.Translate(new RegisterState);
        sh.Info = "";
        return;
    }
    Serial.println(this->pingString);
}