#include "SynthState.h"

SynthState::SynthState() : WAVEFORM1{WAVEFORM_SAWTOOTH},
                           WAVEFORM2{WAVEFORM_SAWTOOTH},
                           IS_POLY{false},
                           SHIFT{false},
                           OSC1_VOL{1.0},
                           OSC2_VOL{1.0},
                           NOISE_VOL{1.0},
                           OSC_CONSTANT{0.0},
                           PWM{0.5},
                           DETUNE{1.0},
                           PITCH_BEND{1.0},
                           LFO_FREQ{0.0},
                           LFO_FILTER_GAIN{0.0},
                           LFO_AMP_GAIN{0.0},
                           AMP_ATTACK{0.0},
                           AMP_DECAY{0.0},
                           AMP_SUSTAIN{1.0},
                           AMP_RELEASE{500},
                           FILTER_ATTACK{0.0},
                           FILTER_DECAY{0.0},
                           FILTER_SUSTAIN{1.0},
                           FILTER_RELEASE{500},
                           FILTER_FREQ{10000},
                           FILTER_Q{1.1},
                           FILTER_OCTAVE{1.0},
                           MASTER_VOL{0.5},
                           POLY_GAIN_MULTIPLIER{1.0},
                           PREFILTER_GAIN{0.9}, // gain to attenuate waveform amplifier based on filter resonance amount (a high resonance can cause clipping);
                           PREV_NOTE{0},
                           CURRENT_NOTE{0}
{
}