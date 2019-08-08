#ifndef globalSynthState_h
#define globalSynthState_h

struct synthState
{
  int WAVEFORM1;
  int WAVEFORM2;
  bool isPoly;
  bool shift;
  float OSC1_VOL;
  float OSC2_VOL;
  float DETUNE;
  float AMP_ATTACK;
  float AMP_DECAY;
  float AMP_SUSTAIN;
  float AMP_RELEASE;
  float FILTER_ATTACK;
  float FILTER_DECAY;
  float FILTER_SUSTAIN;
  float FILTER_RELEASE;
  int FILTER_FREQ;
  float FILTER_Q;
  float MASTER_VOL;
};

#endif