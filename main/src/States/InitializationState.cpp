#include "./State.h"

StateHanlder *INIT_HISTORY = nullptr;

InitializationState::InitializationState()
{
    this->StateName = "InitializationState";
    if (INIT_HISTORY != nullptr)
    {
        Serial.println("[InitializationState reload!!]");
        this->mStateHandler = INIT_HISTORY;
    }
    else
    {
        Serial.println("[InitializationState init!!]");
        this->mStateHandler = new StateHanlder;
        this->mStateHandler->CurrentState = new PingState;
    }
}

InitializationState::~InitializationState()
{
    Serial.println("[InitializationState destroy!!]");
    INIT_HISTORY = this->mStateHandler;
}

void InitializationState::OnUpdate(StateHanlder &sh)
{
    Serial.println("[InitializationState OnUpdate]");
    (this->mStateHandler)->Info = sh.Info;
    (this->mStateHandler)->CurrentState->OnUpdate(*this->mStateHandler);
    
    if(this->mStateHandler->Info == "init done")
    {
        Serial.println("[Create Serve Service]");
        sh.Translate(new ServeState);
        return;
    }
    sh.Info = "";
}