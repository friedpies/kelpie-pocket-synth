#include "SynthVoice.h"

void SynthVoice::triggerKeydown(float gain, float frequency)
{
  waveformA.frequency(frequency * synthState.PITCH_BEND);
  waveformA.phase(0);
  waveformB.frequency(frequency * synthState.PITCH_BEND * synthState.DETUNE);
  waveformB.phase(0);
  waveformAmplifier.gain(gain * synthState.PREFILTER_GAIN);
  ampEnv.noteOn();
  filterEnv.noteOn();
}