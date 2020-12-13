#include "./State.h"

StateHanlder *RUN_HISTORY = nullptr;

RunningState::RunningState()
{
    this->StateName = "RunningState";
    if(RUN_HISTORY != nullptr)
    {
        Serial.println("[RunningState Using Old History]");
        this->mStateHandler = RUN_HISTORY;
    }
    else
    {
        Serial.println("[RunningState Initialization]");
        this->mStateHandler = new StateHanlder;
        mStateHandler->CurrentState = new InitializationState;
    }

}
RunningState::~RunningState()
{
    Serial.println("[deconstruct RunningState]");
    RUN_HISTORY = this->mStateHandler;
}
void RunningState::OnUpdate(StateHanlder &sh)
{
    Serial.println("[RunningState Update]");
    
    (this->mStateHandler)->Info = sh.Info;
    (this->mStateHandler)->CurrentState->OnUpdate(*this->mStateHandler);

    // change to waiting state awating for input
    sh.Translate(new WaitingState);
}