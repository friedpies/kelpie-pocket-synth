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
    void setKnobOnStartup(byte knobIndex);
    byte getIndexOfChangedKnob(void); // this function will return a struct with Potentiometer that has changed
    boolean pollButtons(void);
    boolean *getButtons(void);
    Potentiometer getKnob(byte knobIndex);
    void blinkMidiLED(bool value);
    void bootupAnimation(void);

private:
    Bounce _switches[4] = {Bounce(SW1,10), Bounce(SW2, 10), Bounce(SW3, 10), Bounce(SW4, 10)};

    Potentiometer _knobs[16] = {
        {BALANCE_KNOB, KNOB1_PIN, false, 0, 0},
        {PWM_KNOB, KNOB2_PIN, false, 0, 0},
        {ATTACK_KNOB, KNOB3_PIN, false, 0, 0},
        {DECAY_KNOB, KNOB4_PIN, false, 0, 0},
        {VOL_KNOB, KNOB5_PIN, false, 0, 0},
        {NOISE_KNOB, KNOB6_PIN, false, 0, 0},
        {COARSE_KNOB, KNOB7_PIN, false, 0, 0},
        {SUSTAIN_KNOB, KNOB8_PIN, false, 0, 0},
        {RELEASE_KNOB, KNOB9_PIN, false, 0, 0},
        {GLIDE_KNOB, KNOB10_PIN, false, 0, 0},
        {FREQ_KNOB, KNOB11_PIN, false, 0, 0},
        {Q_KNOB, KNOB12_PIN, false, 0, 0},
        {DEPTH_KNOB, KNOB13_PIN, false, 0, 0},
        {RATE_KNOB, KNOB14_PIN, false, 0, 0},
        {FILTER_KNOB, KNOB15_PIN, false, 0, 0},
        {AMP_KNOB, KNOB16_PIN, false, 0, 0}
    };

    Buttons _buttons = {
        // {_switch1, _switch2, _switch3, _switch4},
        {_switches[0], _switches[1], _switches[2], _switches[3]},
        {SWLED1, SWLED2, SWLED3, SWLED4},
        {false, false, false, false}};
};

#endif