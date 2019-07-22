// Classes for Kelpie Synth
// Author: Kenneth Marut
// v0.0.1

#ifndef Kelpie_h
#define Kelpie_h

#include <Arduino.h>
#include <pinDefines.h>

typedef struct {
    int name;
    int value;
} knob;

class Kelpie
{
public:
    Kelpie(bool enableSerial);
    void activateLights(void);
    void deactivateLights(void);
    void readPots(void);

private:
    knob _kelpieKnobs[16] = {
        {KNOB1, 0},
        {KNOB2, 0},
        {KNOB3, 0},
        {KNOB4, 0},
        {KNOB5, 0},
        {KNOB6, 0},
        {KNOB7, 0},
        {KNOB8, 0},
        {KNOB9, 0},
        {KNOB10, 0},
        {KNOB11, 0},
        {KNOB12, 0},
        {KNOB13, 0},
        {KNOB14, 0},
        {KNOB15, 0},
        {KNOB16, 0},
        };
};

#endif