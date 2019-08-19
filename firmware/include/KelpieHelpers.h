// HELPER FUNCTIONS USED ACROSS VARIOUS CLASSES AND IN MAIN CODE

#ifndef Kelpie_Helpers_h
#define Kelpie_Helpers_h

#include <Arduino.h>
#include <keyMappings.h>
#include <Audio.h>
#include <voices.h>
#include <HardwareInputs.h>
#include <globalSynthState.h>
#include <contants.h>

extern const int numPolyVoices;
extern const int numMonoVoices;
extern voice polyVoices[];
extern voice monoVoices[];
extern synthState globalState;
extern boolean prevButtonsState[];
extern AudioAmplifier amp1;
extern AudioSynthWaveformSine LFO;
extern AudioMixer4 LFO_MIXER_AMP;
void playNoteMono(byte note);
void keyBuffMono(int note, int velocity, boolean isNoteOn);
void keyBuffPoly(int note, int velocty, boolean playNote);
void handleButtonPress(boolean *buttonState);
void handleKnobChange(pot knob);
float calculateOscConstant(float osc1Vol, float osc2Vol, float noiseVol);
void setWaveformLevels(float osc1Vol, float osc2Vol, float noiseVol, float oscConstant);
float calculateDetuneValue(int knobReading);
#endif