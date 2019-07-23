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

boolean Kelpie::pollKnobs(void)
{
    boolean didChange = false;
    for (int i = 0; i < 16; i++) {
        _kelpieKnobs[i].value = analogRead(_kelpieKnobs[i].name);
        if ((_kelpieKnobs[i].value - _kelpieKnobs[i].state) > 6 || (_kelpieKnobs[i].value - _kelpieKnobs[i].state) < -6) {
            _kelpieKnobs[i].state = _kelpieKnobs[i].value;
            didChange = true;
            //  Serial.println(didChange);
        }
        Serial.print(_kelpieKnobs[i].state);
        Serial.print(" ");
    }
    Serial.println();
    return didChange;
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
