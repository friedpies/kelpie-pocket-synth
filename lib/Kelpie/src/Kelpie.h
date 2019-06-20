// Classes for Kelpie Synth
// Author: Kenneth Marut
// v0.0.1

#ifndef Kelpie_h
#define Kelpie_h

#include <Arduino.h>

#define KNOB1 20
#define KNOB2 21
#define KNOB3 31
#define KNOB4 26
#define KNOB5 A11
#define KNOB6 29
#define KNOB7 27
#define KNOB8 28
#define KNOB9 15
#define KNOB10 30
#define KNOB11 17
#define KNOB12 16
#define KNOB13 A14
#define KNOB14 A10
#define KNOB15 A12
#define KNOB16 A13

#define SW1 4
#define SW2 3
#define SW3 5
#define SW4 2

#define SWLED1 24
#define SWLED2 25
#define SWLED3 32
#define SWLED4 33

#define MIDILED 8 // Not working?

class Kelpie
{
public:
    Kelpie(bool enableSerial);
    void activateLights(void);
    void deactivateLights(void);

private:
};

#endif