// MAIN CODE FOR KELPIE SYNTHESIZER
// WRITTEN BY KENNETH MARUT (WWW.KENNETHMARUT.COM)
// THIS PROJECT CAN BE FOLLOWED HERE: https://hackaday.io/project/166460-kelpie-synth-module-for-keyboard-controllers

#include <Arduino.h>
#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <audioConnections.h>
#include <voices.h>
#include <globalSynthState.h>
#include <keyMappings.h>
#include <contants.h>
#include <KelpieIO.h>
#include <KelpieHelpers.h>

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

boolean prevButtonsState[4] = {false, false, false, false}; // initial state on boot
boolean *buttonsState;
pot changedKnob;

polyVoice VOICE_1 = {0, 0.0, 0, false, V1_A, V1_B, V1_N, V1_MIX, V1_AMP, V1_ENV, V1_FILT_ENV, V1_FILT};
polyVoice VOICE_2 = {0, 0.0, 0, false, V2_A, V2_B, V2_N, V2_MIX, V2_AMP, V2_ENV, V2_FILT_ENV, V2_FILT};
polyVoice VOICE_3 = {0, 0.0, 0, false, V3_A, V3_B, V3_N, V3_MIX, V3_AMP, V3_ENV, V3_FILT_ENV, V3_FILT};
polyVoice VOICE_4 = {0, 0.0, 0, false, V4_A, V4_B, V4_N, V4_MIX, V4_AMP, V4_ENV, V4_FILT_ENV, V4_FILT};
polyVoice VOICE_5 = {0, 0.0, 0, false, V5_A, V5_B, V5_N, V5_MIX, V5_AMP, V5_ENV, V5_FILT_ENV, V5_FILT};
polyVoice VOICE_6 = {0, 0.0, 0, false, V6_A, V6_B, V6_N, V6_MIX, V6_AMP, V6_ENV, V6_FILT_ENV, V6_FILT};
polyVoice VOICE_7 = {0, 0.0, 0, false, V7_A, V7_B, V7_N, V7_MIX, V7_AMP, V7_ENV, V7_FILT_ENV, V7_FILT};
polyVoice VOICE_8 = {0, 0.0, 0, false, V8_A, V8_B, V8_N, V8_MIX, V8_AMP, V8_ENV, V8_FILT_ENV, V8_FILT};
polyVoice VOICE_9 = {0, 0.0, 0, false, V9_A, V9_B, V9_N, V9_MIX, V9_AMP, V9_ENV, V9_FILT_ENV, V9_FILT};
polyVoice VOICE_10 = {0, 0.0, 0, false, V10_A, V10_B, V10_N, V10_MIX, V10_AMP, V10_ENV, V10_FILT_ENV, V10_FILT};
polyVoice VOICE_11 = {0, 0.0, 0, false, V11_A, V11_B, V11_N, V11_MIX, V11_AMP, V11_ENV, V11_FILT_ENV, V11_FILT};
polyVoice VOICE_12 = {0, 0.0, 0, false, V12_A, V12_B, V12_N, V12_MIX, V12_AMP, V12_ENV, V12_FILT_ENV, V12_FILT};

const byte numPolyVoices = 8; // 12 voices have been causing issues, so running 6 for now
polyVoice polyVoices[numPolyVoices] = {
    VOICE_1,
    VOICE_2,
    VOICE_3,
    VOICE_4,
    VOICE_5,
    VOICE_6,
    VOICE_7,
    VOICE_8
    // VOICE_9,
    // VOICE_10,
    // VOICE_11,
    // VOICE_12
};

const byte MONOBUFFERSIZE = 8;
byte monoBuffer[MONOBUFFERSIZE];

synthState globalState = {
    WAVEFORM_SAWTOOTH, // WAVEFORM1
    WAVEFORM_SAWTOOTH, // WAVEFORM2
    false,             // isPoly
    false,             // shift
    1.0,               // OSC1_VOL
    1.0,               // OSC2_VOL
    1.0,               // NOISE_VOL
    0.0,               // OSC_CONSTANT
    0.5,               // PWM
    1.0,               // DETUNE
    1.0,               // PITCH_BEND
    0.0,               // LFO_FREQ
    0.0,               // LFO_MIXER_AMP
    0.0,               // AMP_ATTACK
    0.0,               // AMP_DECAY
    1.0,               // AMP_SUSTAIN
    500,               // AMP_RELEASE
    0.0,               // FILTER_ATTACK
    0.0,               // FILTER_DECAY
    1.0,               // FILTER_SUSTAIN
    500,               // FILTER_RELEASE
    10000,             // FILTER_FREQ
    1.1,               // FILTER_Q
    1.0,               // FILTER_OCTAVE
    0.5                // MASTER_VOL
};

void handleMidiEvent(byte channelByte, byte controlByte, byte valueByte)
{
  byte type = MIDI.getType();
  byte note = MIDI.getData1();
  byte velocity = MIDI.getData2();
  int pitch = 0; // initialize to zero, only applies in pitch bend case
  float pitchBend = 0.00;
  switch (type)
  {
  case midi::NoteOn:
    kelpie.blinkMidiLED(true);
    if (note > 23 && note < 108)
    {
      if (globalState.isPoly == true) // depending on mode send to buffer
      {
        keyBuffPoly(note, velocity, true);
      }
      else
      {
        keyBuffMono(note, velocity, true);
      }
    }
    break;

  case midi::NoteOff:
    kelpie.blinkMidiLED(false);
    if (note > 23 && note < 108)
    {
      if (globalState.isPoly == true) // depending on mode send to buffer
      {
        keyBuffPoly(note, velocity, false);
      }
      else
      {
        keyBuffMono(note, velocity, false);
      }
    }
    break;

  case midi::PitchBend:
    pitch = velocity * 256 + note; // this converts 8 bit values into a 16 bit value for precise pitch control
    pitchBend = map(double(pitch), 0, 32767, -2, 2);
    globalState.PITCH_BEND = pow(2, pitchBend / 12);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      float currentFreq = polyVoices[i].noteFreq;
      polyVoices[i].waveformA.frequency(currentFreq * globalState.PITCH_BEND);
      polyVoices[i].waveformB.frequency(currentFreq * globalState.PITCH_BEND * globalState.DETUNE);
    }
    break;

  case midi::ControlChange:
    break;
  }
}

void setup()
{
  MIDI.begin();
  AudioMemory(80);
  sgtl5000_1.enable();
  sgtl5000_1.volume(globalState.MASTER_VOL);

  for (byte i = 0; i < numPolyVoices; i++)
  {
    polyVoices[i].waveformA.begin(globalState.WAVEFORM1);
    polyVoices[i].waveformA.amplitude(0.33);
    polyVoices[i].waveformA.frequency(82.41);
    polyVoices[i].waveformA.pulseWidth(0.15);

    polyVoices[i].waveformB.begin(globalState.WAVEFORM2);
    polyVoices[i].waveformB.amplitude(0.33);
    polyVoices[i].waveformB.frequency(82.41);
    polyVoices[i].waveformB.pulseWidth(0.15);

    polyVoices[i].noise.amplitude(0.33);

    polyVoices[i].waveformMixer.gain(0, 1.0);
    polyVoices[i].waveformMixer.gain(1, 1.0);
    polyVoices[i].waveformMixer.gain(2, 1.0);

    polyVoices[i].waveformAmplifier.gain(1);

    polyVoices[i].ampEnv.attack(globalState.AMP_ATTACK);
    polyVoices[i].ampEnv.decay(globalState.AMP_DECAY);
    polyVoices[i].ampEnv.sustain(globalState.AMP_SUSTAIN);
    polyVoices[i].ampEnv.release(globalState.AMP_RELEASE);

    polyVoices[i].filter.frequency(globalState.FILTER_FREQ);
    polyVoices[i].filter.resonance(globalState.FILTER_Q);
    polyVoices[i].filter.octaveControl(2.0);
  }

  DC_OFFSET.amplitude(1.0);
  LFO.amplitude(1.0);
  LFO.frequency(2.0);
  LFO.phase(90);

  LFO_MIXER_AMP.gain(0, 1); // THIS IS THE AMP THAT ADJUSTS HOW MUCH OF THE LFO IS FED INTO THE FILTER
  LFO_MIXER_AMP.gain(1, 0);

  // V12_MIX
  for (byte i = 0; i < 4; i++)
  {
    V14_MIX.gain(0, 0.25);
    V58_MIX.gain(0, 0.25);
    V912_MIX.gain(0, 0.25);
  }

  ALL_VOICE_MIX.gain(0, 0.5);
  ALL_VOICE_MIX.gain(1, 0.5);

  // READ AND INITIALIZE ALL KNOBS
  for (byte i = 0; i < 16; i++)
  {
    changedKnob = kelpie.getKnobValOnStartup(i);
    handleKnobChange(changedKnob);
  }
}

void loop()

  if (MIDI.read())
  {
    byte channel = MIDI.getChannel();
    byte controlType = MIDI.getData1();
    byte value = MIDI.getData2();
    handleMidiEvent(channel, controlType, value);
  }

  changedKnob = kelpie.pollKnobs();
  if (changedKnob.didChange)
  {
    handleKnobChange(changedKnob);
  }

  if (kelpie.pollButtons())
  {
    buttonsState = kelpie.getButtons();
    handleButtonPress(buttonsState);
  }
}
