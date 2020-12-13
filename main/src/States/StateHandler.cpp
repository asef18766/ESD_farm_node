#include "./State.h"

StateHanlder::StateHanlder()
{
    this->CurrentState = nullptr;
}
void StateHanlder::Translate(IState *new_state)
{
    if(this->CurrentState != nullptr)
    {
        Serial.println("[delete "+this->CurrentState->StateName+" state]");
        delete this->CurrentState;
    }
    else
    {
        Serial.println("[detected nullptr]");
    }
    
    this->CurrentState = new_state;
}