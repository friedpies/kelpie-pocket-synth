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
#include <Kelpie.h>
#include <KelpieHelpers.h>

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

boolean prevButtonsState[4] = {false, false, false, false}; // initial state on boot
boolean *buttonsState;
pot changedKnob;

voice VOICE_1 = {0, 0.0, 0, false, V1_A, V1_B, V1_N, V1_MIX, V1_ENV, V1_FILT_ENV, V1_FILT};
voice VOICE_2 = {0, 0.0, 0, false, V2_A, V2_B, V2_N, V2_MIX, V2_ENV, V2_FILT_ENV, V2_FILT};
voice VOICE_3 = {0, 0.0, 0, false, V3_A, V3_B, V3_N, V3_MIX, V3_ENV, V3_FILT_ENV, V3_FILT};
voice VOICE_4 = {0, 0.0, 0, false, V4_A, V4_B, V4_N, V4_MIX, V4_ENV, V4_FILT_ENV, V4_FILT};
voice VOICE_5 = {0, 0.0, 0, false, V5_A, V5_B, V5_N, V5_MIX, V5_ENV, V5_FILT_ENV, V5_FILT};
voice VOICE_6 = {0, 0.0, 0, false, V6_A, V6_B, V6_N, V6_MIX, V6_ENV, V6_FILT_ENV, V6_FILT};
voice VOICE_7 = {0, 0.0, 0, false, V7_A, V7_B, V7_N, V7_MIX, V7_ENV, V7_FILT_ENV, V7_FILT};
voice VOICE_8 = {0, 0.0, 0, false, V8_A, V8_B, V8_N, V8_MIX, V8_ENV, V8_FILT_ENV, V8_FILT};
voice VOICE_9 = {0, 0.0, 0, false, V9_A, V9_B, V9_N, V9_MIX, V9_ENV, V9_FILT_ENV, V9_FILT};
voice VOICE_10 = {0, 0.0, 0, false, V10_A, V10_B, V10_N, V10_MIX, V10_ENV, V10_FILT_ENV, V10_FILT};
voice VOICE_11 = {0, 0.0, 0, false, V11_A, V11_B, V11_N, V11_MIX, V11_ENV, V11_FILT_ENV, V11_FILT};
voice VOICE_12 = {0, 0.0, 0, false, V12_A, V12_B, V12_N, V12_MIX, V12_ENV, V12_FILT_ENV, V12_FILT};

const int polyBuffSize = 12;
voice polyBuff[polyBuffSize] = {
    VOICE_1,
    VOICE_2,
    VOICE_3,
    VOICE_4,
    VOICE_5,
    VOICE_6,
    VOICE_7,
    VOICE_8,
    VOICE_9,
    VOICE_10,
    VOICE_11,
    VOICE_12};

synthState globalState = {
    WAVEFORM_SAWTOOTH, // WAVEFORM1
    WAVEFORM_SAWTOOTH, // WAVEFORM2
    true,              // isPoly
    false,             // shift
    1.0,               // OSC1_VOL
    0.33,              // OSC2_VOL
    0.5,               // PWM
    0.0,               // DETUNE_FINE
    0.0,               // DETUNE_COARSE
    0.0,               // AMP_ATTACK
    0.0,               // AMP_DECAY
    1.0,               // AMP_SUSTAIN
    500,               // AMP_RELEASE
    0.0,               // FILTER_ATTACK
    0.0,               // FILTER_DECAY
    1.0,               // FILTER_SUSTAIN
    500,               // FILTER_RELEASE
    10000,             // FILTER_FREQ
    0.7,               // FILTER_Q
    0.5                // MASTER_VOL
};

void setup()
{
  MIDI.begin();
  AudioMemory(80);
  sgtl5000_1.enable();
  sgtl5000_1.volume(globalState.MASTER_VOL);

  for (int i = 0; i < polyBuffSize; i++)
  {
    polyBuff[i].waveformA.begin(globalState.WAVEFORM1);
    polyBuff[i].waveformA.amplitude(0.5);
    polyBuff[i].waveformA.frequency(82.41);
    polyBuff[i].waveformA.pulseWidth(0.15);

    polyBuff[i].waveformB.begin(globalState.WAVEFORM2);
    polyBuff[i].waveformB.amplitude(0.5);
    polyBuff[i].waveformB.frequency(82.41);
    polyBuff[i].waveformB.pulseWidth(0.15);

    polyBuff[i].noise.amplitude(0.0);

    polyBuff[i].waveformMixer.gain(0, globalState.OSC1_VOL);
    polyBuff[i].waveformMixer.gain(1, globalState.OSC2_VOL);
    polyBuff[i].waveformMixer.gain(2, 1.0);

    polyBuff[i].ampEnv.attack(globalState.AMP_ATTACK);
    polyBuff[i].ampEnv.decay(globalState.AMP_DECAY);
    polyBuff[i].ampEnv.sustain(globalState.AMP_SUSTAIN);
    polyBuff[i].ampEnv.release(globalState.AMP_RELEASE);

    polyBuff[i].filter.frequency(globalState.FILTER_FREQ);
    polyBuff[i].filter.resonance(globalState.FILTER_Q);
    polyBuff[i].filter.octaveControl(2.0);
  }

  LFO.amplitude(1.0);
  LFO.frequency(2);
  LFO.phase(90);

  // V12_MIX
  V14_MIX.gain(0, 0.3);
  V14_MIX.gain(1, 0.3);
  V14_MIX.gain(2, 0.3);

  V58_MIX.gain(0, 0.3);
  V58_MIX.gain(1, 0.3);
  V58_MIX.gain(2, 0.3);

  V912_MIX.gain(0, 0.3);
  V912_MIX.gain(1, 0.3);
  V912_MIX.gain(2, 0.3);

  ALL_VOICE_MIX.gain(0, 0.5);
  ALL_VOICE_MIX.gain(1, 0.5);
}

void handleMidiEvent(int channelByte, int controlByte, int valueByte)
{
  int type = MIDI.getType();
  int note;
  switch (type)
  {
  case midi::NoteOn:
    note = MIDI.getData1();
    // velocity = MIDI.getData2();
    if (note > 23 && note < 108)
    {
      if (globalState.isPoly == true) // depending on mode send to buffer
      {
        keyBuffPoly(note, true);
      }
      else
      {
        keyBuffMono(note, true);
      }
    }
    break;

  case midi::NoteOff:
    note = MIDI.getData1();
    // envelope1.noteOff();
    if (note > 23 && note < 108)
    {
      if (globalState.isPoly == true) // depending on mode send to buffer
      {
        keyBuffPoly(note, false);
      }
      else
      {
        keyBuffMono(note, false);
      }
    }
    break;

  case midi::PitchBend:
    break;

  case midi::ControlChange:
    break;
  }
}

void loop()
{
  if (MIDI.read())
  {
    int channel = MIDI.getChannel();
    int controlType = MIDI.getData1();
    int value = MIDI.getData2();
    handleMidiEvent(channel, controlType, value);
  }

  changedKnob = kelpie.pollKnobs(false);
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
