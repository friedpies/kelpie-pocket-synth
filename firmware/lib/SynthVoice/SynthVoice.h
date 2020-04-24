// DEFINES A SINGLE 'VOICE'. THERE ARE 12 VOICES TOTAL, THEY ARE INITIALIZED IN THE MAIN.CPP FILE
#ifndef SynthVoice_h
#define SynthVoice_h

#include <Audio.h>
#include <SynthState.h>
class SynthVoice
{
public:
  SynthVoice(
      AudioSynthWaveform &waveA,
      AudioSynthWaveform &waveB,
      AudioSynthNoiseWhite &noi,
      AudioMixer4 &waveMixer,
      AudioAmplifier &waveAmplifier,
      AudioEffectEnvelope &ampE,
      AudioEffectEnvelope &filterE,
      AudioFilterStateVariable &filt,
      SynthState &state);

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
  SynthState &synthState;

  void triggerKeydown(byte noteIn, float gain, float frequencyIn);
};

#endif