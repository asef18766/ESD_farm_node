#include "src/States/State.h"

StateHanlder GLOBAL_STATE_HANDLER;
int SLEEP_TIME = 1000;

// the setup function runs once when you press reset or power the board
void setup()
{
    pinMode(5, OUTPUT);
    Serial.begin(9600);
    while (!Serial);
    
    Serial.println("[Instance Created]");
    GLOBAL_STATE_HANDLER.CurrentState = new RunningState;
}

void loop()
{
    digitalWrite(5, HIGH);
    delay(SLEEP_TIME/2);
    digitalWrite(5, LOW);
    GLOBAL_STATE_HANDLER.CurrentState->OnUpdate(GLOBAL_STATE_HANDLER);
    delay(SLEEP_TIME/2);
}