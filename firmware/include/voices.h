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
  AudioSynthNoisePink &noise;
  AudioMixer4 &waveformMixer;
  AudioEffectEnvelope &ampEnv;
  AudioEffectEnvelope &filterEnv;
  AudioFilterStateVariable &filter;
};

#endif