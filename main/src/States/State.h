#pragma once

#include <ArduinoJson.h>
#include "../Devices/Device.h"
class IState;

#pragma region BasicInterface
class StateHanlder
{
    public:
    StateHanlder();
    IState *CurrentState;
    String Info;
    void Translate(IState *new_state);
};

class IState
{
    public:
    virtual void OnUpdate(StateHanlder &sh) = 0;
    String StateName;
    virtual ~IState() {}
};

class IPushDownState : public IState
{
    protected:
    StateHanlder *mStateHandler;
};
#pragma endregion BasicInterface

class RunningState : public IPushDownState
{
    public:
    RunningState();
    ~RunningState() override;
    void OnUpdate(StateHanlder &sh) override;
};

class WaitingState : public IState
{
    public:
    WaitingState();
    void OnUpdate(StateHanlder &sh) override;
};

class InitializationState : public IPushDownState
{
    public:
    InitializationState();
    ~InitializationState() override;

    void OnUpdate(StateHanlder &sh) override;
};

class PingState : public IState
{
    public:
    PingState();
    void OnUpdate(StateHanlder &sh) override;
    private:
    String pingString;
};

class RegisterState : public IState
{
    public:
    RegisterState();
    void OnUpdate(StateHanlder &sh) override;
};

class ServeState : public IState
{
    public:
    ServeState();
    void OnUpdate(StateHanlder &sh) override;
    
    private:
    static DeviceHandler* config;
};
