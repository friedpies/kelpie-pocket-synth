#include "SynthVoice.h"

SynthVoice::SynthVoice(
    AudioSynthWaveform &waveA,
    AudioSynthWaveform &waveB,
    AudioSynthNoiseWhite &noi,
    AudioMixer4 &waveMixer,
    AudioAmplifier &waveAmplifier,
    AudioEffectEnvelope &ampE,
    AudioEffectEnvelope &filterE,
    AudioFilterStateVariable &filt,
    SynthState &state) : note{0},
                         noteFreq{0},
                         velocity{0},
                         isActive{false},
                         waveformA{waveA},
                         waveformB{waveB},
                         noise{noi},
                         waveformMixer{waveMixer},
                         waveformAmplifier{waveAmplifier},
                         ampEnv{ampE},
                         filterEnv{filterE},
                         filter{filt},
                         synthState{state} {}

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