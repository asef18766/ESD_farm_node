#include "./State.h"

DeviceHandler* ServeState::config;
ServeState::ServeState()
{
    this->StateName = "RunningState";
    this->config = DeviceHandler::GetInstance();
    Serial.println("create server state");

}

void ServeState::OnUpdate(StateHanlder &sh)
{
    Serial.println("[at serve state update]");
    config->Tick();
    Serial.println("[end of serve state update]");
}