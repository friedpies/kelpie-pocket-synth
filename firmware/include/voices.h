// All "Voice" Information is stored here
#ifndef Voices_h
#define Voices_h

struct voice
{
  int note;
  float noteFreq;
  int velocity;
  bool noteOnOff;
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