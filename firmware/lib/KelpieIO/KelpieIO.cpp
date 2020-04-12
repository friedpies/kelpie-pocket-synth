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

void KelpieIO::setKnobOnStartup(byte knobIndex)
{
    int knobValue = analogRead(_knobs[knobIndex].pinNum);
    _knobs[knobIndex].setValue = knobValue;
    _knobs[knobIndex].polledValue = knobValue;
}

// Detects if a knob was changed and returns the changed Potentiometer
byte KelpieIO::getIndexOfChangedKnob(void)
{
    for (byte i = 0; i < 16; i++)
    {
        _knobs[i].polledValue = analogRead(_knobs[i].pinNum); // **the dimensions of this struct seem to be reversed**
        if ((_knobs[i].polledValue - _knobs[i].setValue) > 3 || (_knobs[i].polledValue - _knobs[i].setValue) < -3) // if there is a significant change
        {
            _knobs[i].setValue = _knobs[i].polledValue; //update state
            return i;
            break;
        }
    }
    return -1;
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

Potentiometer KelpieIO::getKnob(byte knobIndex) 
{
    return _knobs[knobIndex];
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