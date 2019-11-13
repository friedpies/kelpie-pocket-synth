// DEFINES A SINGLE 'VOICE'. THERE ARE 12 VOICES TOTAL, THEY ARE INITIALIZED IN THE MAIN.CPP FILE
#ifndef Voices_h
#define Voices_h

#include <Audio.h>
struct polyVoice
{
  byte note;
  float noteFreq;
  byte velocity;
  bool isActive;
  AudioSynthWaveform &waveformA;
  AudioSynthWaveform &waveformB;
  AudioSynthNoiseWhite &noise;
  AudioMixer4 &waveformMixer;
  AudioAmplifier &waveformAmplifier;
  AudioEffectEnvelope &ampEnv;
  AudioEffectEnvelope &filterEnv;
  AudioFilterStateVariable &filter;
};


#endif