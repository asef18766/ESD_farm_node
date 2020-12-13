#include "./State.h"

ServeState::ServeState()
{
    this->StateName = "RunningState";
    Serial.println("create server state");
}

void ServeState::OnUpdate(StateHanlder &sh)
{
    Serial.println("at server state");
}