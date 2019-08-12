#ifndef Kelpie_Helpers_h
#define Kelpie_Helpers_h

#include <Arduino.h>
#include <keyMappings.h>
#include <Audio.h>
#include <voices.h>
#include <Input.h>
#include <globalSynthState.h>
#include <contants.h>

extern const int polyBuffSize;
extern voice polyBuff[];
extern synthState globalState;
extern boolean prevButtonsState[];
extern AudioAmplifier amp1;
extern AudioSynthWaveformSine LFO;
void keyBuffMono(int note, boolean isNoteOn);
void keyBuffPoly(int note, boolean playNote);
void handleButtonPress(boolean *buttonState);
void handleKnobChange(pot knob);
#endif