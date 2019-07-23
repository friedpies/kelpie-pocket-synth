// Classes for Kelpie Synth
// Author: Kenneth Marut
// v0.0.1

#ifndef Kelpie_h
#define Kelpie_h

#include <Arduino.h>
#include <Bounce.h>
#include <pinDefines.h>

struct potentiometer {
    int name[16]; // variable name of knob
    int value[16]; // current polled value
    int state[16]; // actual state value
};


struct button {
    Bounce buttonName;
    int ledName;
    boolean state;
};

class Kelpie
{
public:
    Kelpie(bool enableSerial);
    boolean pollKnobs(void);
    void pollButtons(void);

    potentiometer getKnobs(void);

private:
    Bounce _switch1 = Bounce(SW1, 10);  // 10 ms debounce
    Bounce _switch2 = Bounce(SW2, 10);  // 10 ms debounce
    Bounce _switch3 = Bounce(SW3, 10);  // 10 ms debounce
    Bounce _switch4 = Bounce(SW4, 10);  // 10 ms debounce

    potentiometer _kelpieKnobs = {
        {KNOB1, KNOB2, KNOB3, KNOB4, KNOB5, KNOB6, KNOB7, KNOB8, KNOB9, KNOB10, KNOB11, KNOB12, KNOB13, KNOB14, KNOB15, KNOB16},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
        // {KNOB1, 0, 0},
        // {KNOB2, 0, 0},
        // {KNOB3, 0, 0},
        // {KNOB4, 0, 0},
        // {KNOB5, 0, 0},
        // {KNOB6, 0, 0},
        // {KNOB7, 0, 0},
        // {KNOB8, 0, 0},
        // {KNOB9, 0, 0},
        // {KNOB10, 0, 0},
        // {KNOB11, 0, 0},
        // {KNOB12, 0, 0},
        // {KNOB13, 0, 0},
        // {KNOB14, 0, 0},
        // {KNOB15, 0, 0},
        // {KNOB16, 0, 0}
        // };

    button _kelpieButtons[4] = {
        {_switch1, SWLED1, false},
        {_switch2, SWLED2, false},
        {_switch3, SWLED3, false},
        {_switch4, SWLED4, false},
    };
};

#endif