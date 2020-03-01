// ENCAPSULATES ALL CODE RELATED TO HARDWARE INTERFACE

#ifndef Kelpie_io_h
#define Kelpie_io_h

#include <Arduino.h>
#include <Bounce.h>
#include "pinDefines.h"
#include "HardwareInputs.h"

class KelpieIO
{
public:
    KelpieIO(bool enableSerial);
    Potentiometer getKnobValOnStartup(byte knobIndex);
    Potentiometer pollKnobs(void); // this function will return a struct with Potentiometer that has changed
    boolean pollButtons(void);
    boolean *getButtons(void);
    void blinkMidiLED(bool value);
    void bootupAnimation(void);

private:
    Bounce _switches[4] = {Bounce(SW1,10), Bounce(SW2, 10), Bounce(SW3, 10), Bounce(SW4, 10)};

    Knobs _knobs = {
        {KNOB1_PIN, KNOB2_PIN, KNOB3_PIN, KNOB4_PIN, KNOB5_PIN, KNOB6_PIN, KNOB7_PIN, KNOB8_PIN, KNOB9_PIN, KNOB10_PIN, KNOB11_PIN, KNOB12_PIN, KNOB13_PIN, KNOB14_PIN, KNOB15_PIN, KNOB16_PIN},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Buttons _buttons = {
        // {_switch1, _switch2, _switch3, _switch4},
        {_switches[0], _switches[1], _switches[2], _switches[3]},
        {SWLED1, SWLED2, SWLED3, SWLED4},
        {false, false, false, false}};
};

#endif