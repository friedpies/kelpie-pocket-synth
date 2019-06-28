#include <Arduino.h>
#include <Kelpie.h>

Kelpie::Kelpie(bool enableSerial)
{
    if (enableSerial)
    {
        Serial.begin(9600);
    }

    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(SW3, INPUT_PULLUP);
    pinMode(SW4, INPUT_PULLUP);

    pinMode(SWLED1, OUTPUT);
    pinMode(SWLED2, OUTPUT);
    pinMode(SWLED3, OUTPUT);
    pinMode(SWLED4, OUTPUT);
}

void Kelpie::activateLights(void)
{
    digitalWrite(SWLED1, HIGH);
    digitalWrite(SWLED2, HIGH);
    digitalWrite(SWLED3, HIGH);
    digitalWrite(SWLED4, HIGH);
}

void Kelpie::deactivateLights(void)
{
    digitalWrite(SWLED1, LOW);
    digitalWrite(SWLED2, LOW);
    digitalWrite(SWLED3, LOW);
    digitalWrite(SWLED4, LOW);
}
