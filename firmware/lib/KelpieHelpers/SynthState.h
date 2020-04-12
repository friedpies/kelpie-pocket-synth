// DESCRIBES THE GLOBAL STATE, A DATATYPE TO STORE ALL GLOBAL VARIABLES ACCESSED ACROSS THE PROGRAM

#ifndef globalSynthState_h
#define globalSynthState_h

struct SynthState
{
  byte WAVEFORM1;
  byte WAVEFORM2;
  bool IS_POLY;
  bool SHIFT;
  float OSC1_VOL;
  float OSC2_VOL;
  float NOISE_VOL;
  float OSC_CONSTANT; // this is a multiplication factor that is calculated based on positions of O1 O2 and N, to ensure sum of gains is 1
  float PWM;
  float DETUNE;
  float PITCH_BEND;
  float LFO_FREQ;
  float LFO_FILTER_GAIN;
  float LFO_AMP_GAIN;
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
  float FILTER_OCTAVE;
  float MASTER_VOL;
  float POLY_GAIN_MULTIPLIER;
  float PREFILTER_GAIN; // gain to attenuate waveform amplifier based on filter resonance amount (a high resonance can cause clipping);
  byte PREV_NOTE;
  byte CURRENT_NOTE;
};

#endif