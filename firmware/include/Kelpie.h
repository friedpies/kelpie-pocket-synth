// ENCAPSULATES ALL CODE RELATED TO HARDWARE INTERFACE

#ifndef Kelpie_h
#define Kelpie_h

#include <Arduino.h>
#include <Bounce.h>
#include <pinDefines.h>
#include <HardwareInputs.h>

class Kelpie
{
public:
    Kelpie(bool enableSerial);
    pot pollKnobs(bool forceRead); // this function will return a vector with pots that have changed
    boolean pollButtons(void);

    int *getKnobs(void);
    boolean *getButtons(void);

private:
    Bounce _switch1 = Bounce(SW1, 10); // 10 ms debounce
    Bounce _switch2 = Bounce(SW2, 10); // 10 ms debounce
    Bounce _switch3 = Bounce(SW3, 10); // 10 ms debounce
    Bounce _switch4 = Bounce(SW4, 10); // 10 ms debounce

    potentiometers _kelpieKnobs = {
        {KNOB1, KNOB2, KNOB3, KNOB4, KNOB5, KNOB6, KNOB7, KNOB8, KNOB9, KNOB10, KNOB11, KNOB12, KNOB13, KNOB14, KNOB15, KNOB16},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    buttons _kelpieButtons = {
        {_switch1, _switch2, _switch3, _switch4},
        {SWLED1, SWLED2, SWLED3, SWLED4},
        {false, false, false, false}};
};

#endif