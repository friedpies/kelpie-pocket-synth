// Classes for Kelpie Synth
// Author: Kenneth Marut
// v0.0.1

#ifndef Kelpie_h
#define Kelpie_h

#include <Arduino.h>
#include <Bounce.h>
#include <pinDefines.h>

typedef struct {
    int name; // variable name of knob
    int value; // current polled value
    int state; // actual state value
} potentiometer;

typedef struct {
    Bounce buttonName;
    int ledName;
    boolean state;
} button;

class Kelpie
{
public:
    Kelpie(bool enableSerial);
    void activateLights(void);
    void deactivateLights(void);
    boolean pollKnobs(void);
    void pollButtons(void);
    Bounce switch1 = Bounce(SW1, 10);  // 10 ms debounce
    Bounce switch2 = Bounce(SW2, 10);  // 10 ms debounce
    Bounce switch3 = Bounce(SW3, 10);  // 10 ms debounce
    Bounce switch4 = Bounce(SW4, 10);  // 10 ms debounce

private:
    potentiometer _kelpieKnobs[16] = {
        {KNOB1, 0, 0},
        {KNOB2, 0, 0},
        {KNOB3, 0, 0},
        {KNOB4, 0, 0},
        {KNOB5, 0, 0},
        {KNOB6, 0, 0},
        {KNOB7, 0, 0},
        {KNOB8, 0, 0},
        {KNOB9, 0, 0},
        {KNOB10, 0, 0},
        {KNOB11, 0, 0},
        {KNOB12, 0, 0},
        {KNOB13, 0, 0},
        {KNOB14, 0, 0},
        {KNOB15, 0, 0},
        {KNOB16, 0, 0}
        };

    button _kelpieButtons[4] = {
        {switch1, SWLED1, false},
        {switch2, SWLED2, false},
        {switch3, SWLED3, false},
        {switch4, SWLED4, false},
    };
};

#endif