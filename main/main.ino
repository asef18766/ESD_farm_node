#include "src/States/State.h"
#define DEFAULT_LED 2

StateHanlder GLOBAL_STATE_HANDLER;
int SLEEP_TIME = 1000;

// the setup function runs once when you press reset or power the board
void setup()
{
    pinMode(DEFAULT_LED, OUTPUT);
    Serial.begin(9600);
    while (!Serial);
    
    Serial.println("[Instance Created]");
    GLOBAL_STATE_HANDLER.CurrentState = new RunningState;
}

void loop()
{
    digitalWrite(DEFAULT_LED, HIGH);
    delay(SLEEP_TIME/2);
    digitalWrite(DEFAULT_LED, LOW);
    GLOBAL_STATE_HANDLER.CurrentState->OnUpdate(GLOBAL_STATE_HANDLER);
    delay(SLEEP_TIME/2);
}
