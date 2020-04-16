#include "SynthVoice.h"

void SynthVoice::triggerKeydown(byte noteIn, float gain, float frequencyIn)
{
  note = noteIn;
  noteFreq = frequencyIn;
  waveformA.frequency(frequencyIn * synthState.PITCH_BEND);
  waveformA.phase(0);
  waveformB.frequency(frequencyIn * synthState.PITCH_BEND * synthState.DETUNE);
  waveformB.phase(0);
  waveformAmplifier.gain(gain * synthState.PREFILTER_GAIN);
  ampEnv.noteOn();
  filterEnv.noteOn();
}