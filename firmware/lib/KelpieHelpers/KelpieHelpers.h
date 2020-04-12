// HELPER FUNCTIONS USED ACROSS VARIOUS CLASSES AND IN MAIN CODE

#ifndef Kelpie_Helpers_h
#define Kelpie_Helpers_h

#include <Arduino.h>
#include <Audio.h>
#include <HardwareInputs.h>
#include "keyMappings.h"
#include "SynthVoice.h"
#include "SynthState.h"
#include "constants.h"

extern const byte numPolyVoices;
extern SynthVoice polyVoices[];
extern SynthVoice monoVoices[];
extern SynthState globalState;
extern boolean prevButtonsState[];
extern AudioAmplifier MASTER_GAIN;
extern AudioSynthWaveformSine LFO;
extern AudioMixer4 LFO_MIXER_FILTER;
extern AudioMixer4 LFO_MIXER_AMP;
extern const byte MONOBUFFERSIZE;
extern byte monoBuffer[];

enum playModes {
  PLAY_NOTE,
  UPDATE_NOTE,
  STOP_NOTE
};

void activateVoice(byte index, byte note, float frequency, float gain);
void decactivateVoice(byte index, boolean stopOscillator);
void playNoteMono(byte playMode, byte note, float noteGain);
void bufferShift(byte indexToRemove, byte currentIndexPlaying);
void keyBuffMono(byte note, float noteGain, boolean isNoteOn);
void keyBuffPoly(byte note, float noteGain, boolean playNote);
void handleButtonPress(Button button);
void handleKnobChange(Potentiometer knob);
float calculateOscConstant(float osc1Vol, float osc2Vol, float noiseVol);
void setWaveformLevels(float osc1Vol, float osc2Vol, float noiseVol, float oscConstant);
float calculateDetuneValue(int knobReading);

#endif