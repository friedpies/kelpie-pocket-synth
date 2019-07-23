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

boolean Kelpie::pollKnobs(void)
{
    boolean didChange = false;
    for (int i = 0; i < 16; i++) {
        _kelpieKnobs.value[i] = analogRead(_kelpieKnobs.name[i]);
        if ((_kelpieKnobs.value[i] - _kelpieKnobs.state[i]) > 6 || (_kelpieKnobs.value[i] - _kelpieKnobs.state[i]) < -6) {
            _kelpieKnobs.state[i] = _kelpieKnobs.value[i];
            didChange = true;
            //  Serial.println(_kelpieKnobs);
        }
        // Serial.print(_kelpieKnobs.state[i]);
        // Serial.print(" ");
    }
    // Serial.println();
    return didChange;
}

potentiometer Kelpie::getKnobs(void)
{
    return _kelpieKnobs;
}

void Kelpie::pollButtons(void) {
 for (int i = 0; i < 4; i++) {
        if(_kelpieButtons[i].buttonName.update()) {
            if (_kelpieButtons[i].buttonName.fallingEdge()) {
                _kelpieButtons[i].state = !_kelpieButtons[i].state;
                digitalWrite(_kelpieButtons[i].ledName, _kelpieButtons[i].state);
                // Serial.print(i);
            }
        }
    }
}
