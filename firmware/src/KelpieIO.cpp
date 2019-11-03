#include <KelpieIO.h>

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

    pinMode(MIDILED, OUTPUT);
}

pot Kelpie::getKnobValOnStartup(byte knobIndex)
{
    pot potToRead;
    _kelpieKnobs.value[knobIndex] = analogRead(_kelpieKnobs.name[knobIndex]);
    potToRead.didChange = true;
    potToRead.name = knobIndex;
    potToRead.value = _kelpieKnobs.value[knobIndex];
    _kelpieKnobs.state[knobIndex] = _kelpieKnobs.value[knobIndex];
    return potToRead;
}

// this function detects if a knob was changed and returns the pot Struct of the changed knob
pot Kelpie::pollKnobs(void)
{
    pot changedPot;
    changedPot.didChange = false;
    for (byte i = 0; i < 16; i++)
    {
        _kelpieKnobs.value[i] = analogRead(_kelpieKnobs.name[i]); // THIS LINE IS BAD

        if ((_kelpieKnobs.value[i] - _kelpieKnobs.state[i]) > 3 || (_kelpieKnobs.value[i] - _kelpieKnobs.state[i]) < -3) // if there is a significant change
        {
            changedPot.didChange = true;
            changedPot.name = i;
            changedPot.value = _kelpieKnobs.value[i];
            _kelpieKnobs.state[i] = _kelpieKnobs.value[i]; //update state
            break;
        }
    }
    return changedPot;
}

boolean Kelpie::pollButtons(void)
{
    boolean didChange = false;
    for (byte i = 0; i < 4; i++)
    {
        if (_kelpieButtons.buttonName[i].update())
        {
            if (_kelpieButtons.buttonName[i].fallingEdge())
            {
                _kelpieButtons.state[i] = !_kelpieButtons.state[i];
                digitalWrite(_kelpieButtons.ledName[i], _kelpieButtons.state[i]);
                didChange = true;
            }
        }
    }
    return didChange;
}

boolean *Kelpie::getButtons(void)
{
    return _kelpieButtons.state;
}

void Kelpie::blinkMidiLED(bool value)
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

void Kelpie::bootupAnimation(void)
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
            digitalWrite(_kelpieButtons.ledName[i], HIGH);
            delay(delayTimeMS);
            digitalWrite(_kelpieButtons.ledName[i], LOW);
            delay(delayTimeMS);
        }
    }
}