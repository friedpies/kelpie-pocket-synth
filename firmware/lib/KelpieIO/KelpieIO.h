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
    byte getIndexOfChangedButton(void); // this function will return a struct with the button that has changed
    Potentiometer getKnob(byte knobIndex);
    Button getButton(byte buttonIndex);
    void blinkMidiLED(bool value);
    void bootupAnimation(void);

private:
    Potentiometer _knobs[16] = {
        {BALANCE_KNOB, KNOB1_PIN, 0, 0},
        {PWM_KNOB, KNOB2_PIN, 0, 0},
        {ATTACK_KNOB, KNOB3_PIN, 0, 0},
        {DECAY_KNOB, KNOB4_PIN, 0, 0},
        {VOL_KNOB, KNOB5_PIN, 0, 0},
        {NOISE_KNOB, KNOB6_PIN, 0, 0},
        {COARSE_KNOB, KNOB7_PIN, 0, 0},
        {SUSTAIN_KNOB, KNOB8_PIN, 0, 0},
        {RELEASE_KNOB, KNOB9_PIN, 0, 0},
        {GLIDE_KNOB, KNOB10_PIN, 0, 0},
        {FREQ_KNOB, KNOB11_PIN, 0, 0},
        {Q_KNOB, KNOB12_PIN, 0, 0},
        {DEPTH_KNOB, KNOB13_PIN, 0, 0},
        {RATE_KNOB, KNOB14_PIN, 0, 0},
        {FILTER_KNOB, KNOB15_PIN, 0, 0},
        {AMP_KNOB, KNOB16_PIN, 0, 0}
    };

    Button _buttons[4] = {
        {OSC_1_BUTTON, SWLED1, Bounce(SW1, 10), false},
        {OSC_2_BUTTON, SWLED2, Bounce(SW2, 10), false},
        {POLY_MONO_BUTTON, SWLED3, Bounce(SW3, 10), false},
        {SHIFT_BUTTON, SWLED4, Bounce(SW4, 10), false},
    };
};

#endif