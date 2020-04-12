#include "KelpieIO.h"

KelpieIO::KelpieIO(bool enableSerial)
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

    pinMode(MIDILED, OUTPUT);
}

Potentiometer KelpieIO::getKnobValOnStartup(byte knobIndex)
{
    Potentiometer potToRead;
    _knobs.value[knobIndex] = analogRead(_knobs.name[knobIndex]);
    potToRead.didChange = true; // force potentiometer to be read
    potToRead.name = knobIndex;
    potToRead.polledValue = _knobs.value[knobIndex];
    _knobs.state[knobIndex] = _knobs.value[knobIndex];
    return potToRead;
}

// Detects if a knob was changed and returns the changed Potentiometer
Potentiometer KelpieIO::pollKnobs(void)
{
    Potentiometer changedPot;
    changedPot.didChange = false;
    for (byte i = 0; i < 16; i++)
    {
        _knobs.value[i] = analogRead(_knobs.name[i]); // **the dimensions of this struct seem to be reversed**

        if ((_knobs.value[i] - _knobs.state[i]) > 3 || (_knobs.value[i] - _knobs.state[i]) < -3) // if there is a significant change
        {
            changedPot.didChange = true;
            changedPot.name = i;
            changedPot.polledValue = _knobs.value[i];
            _knobs.state[i] = _knobs.value[i]; //update state
            break;
        }
    }
    return changedPot;
}

boolean KelpieIO::pollButtons(void)
{
    boolean didChange = false;
    for (byte i = 0; i < 4; i++)
    {
        if (_buttons.buttonName[i].update())
        {
            if (_buttons.buttonName[i].fallingEdge())
            {
                _buttons.state[i] = !_buttons.state[i];
                digitalWrite(_buttons.ledName[i], _buttons.state[i]);
                didChange = true;
            }
        }
    }
    return didChange;
}

boolean *KelpieIO::getButtons(void)
{
    return _buttons.state;
}

void KelpieIO::blinkMidiLED(bool value)
{
    if (value)
    {
        digitalWrite(MIDILED, HIGH);
    }
    else
    {
        digitalWrite(MIDILED, LOW);
    }
}

void KelpieIO::bootupAnimation(void)
{
    byte delayTimeMS = 50;
    byte numCycles = 5;
    for (byte counter = 0; counter < numCycles; counter++)
    {
        digitalWrite(MIDILED, HIGH);
        delay(delayTimeMS);
        digitalWrite(MIDILED, LOW);
        for (byte i = 0; i < 4; i++)
        {
            digitalWrite(_buttons.ledName[i], HIGH);
            delay(delayTimeMS);
            digitalWrite(_buttons.ledName[i], LOW);
            delay(delayTimeMS);
        }
    }
}