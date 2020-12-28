#include "./State.h"

WaitingState::WaitingState()
{
    this->StateName = "WaitingState";
}
void WaitingState::OnUpdate(StateHanlder &sh)
{
    if(Serial.available())
    {
        String str = Serial.readString();
        str.remove(str.length()-1);
        Serial.println("[got "+str+"]");
        sh.Info = str;
        sh.Translate(new RunningState);
    }
}
