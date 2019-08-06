#include <Arduino.h>
#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <audioConnections.h>
#include <globalSynthState.h>
#include <keyMappings.h>
#include <contants.h>
#include <Kelpie.h>

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

boolean prevButtonsState[4] = {false, false, false, false}; // initial state on boot
boolean *buttonsState;
pot changedKnob;
const int bufferSize = 8;

void setup()
{
  MIDI.begin();
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(globalState.MASTER_VOL);

//  VOICE 1
  V1_A.begin(globalState.WAVEFORM1);
  V1_A.amplitude(0.75);
  V1_A.frequency(82.41);
  V1_A.pulseWidth(0.15);

  V1_B.begin(globalState.WAVEFORM2);
  V1_B.amplitude(0.75);
  V1_B.frequency(82.41);
  V1_B.pulseWidth(0.15);

  V1_N.amplitude(0.0);

  V1_MIX.gain(0, globalState.OSC1_VOL);
  V1_MIX.gain(1, globalState.OSC2_VOL);
  V1_MIX.gain(2, 1.0);

// VOICE 2
  V2_A.begin(globalState.WAVEFORM1);
  V2_A.amplitude(0.75);
  V2_A.frequency(82.41);
  V2_A.pulseWidth(0.15);

  V2_B.begin(globalState.WAVEFORM2);
  V2_B.amplitude(0.75);
  V2_B.frequency(82.41);
  V2_B.pulseWidth(0.15);

  V2_N.amplitude(0.0);

  V2_MIX.gain(0, globalState.OSC1_VOL);
  V2_MIX.gain(1, globalState.OSC2_VOL);
  V2_MIX.gain(2, 1.0);

// V12_MIX
  V12_MIX.gain(0, 1.0);
  V12_MIX.gain(1, 1.0);
  V12_MIX.gain(2, 1.0);

  filter1.frequency(globalState.FILTER_FREQ);
  filter1.resonance(globalState.FILTER_Q);

  envelope1.attack(globalState.AMP_ATTACK);
  envelope1.decay(globalState.AMP_DECAY);
  envelope1.sustain(globalState.AMP_SUSTAIN);
  envelope1.release(globalState.AMP_RELEASE);
}

void keyBuff(int note, boolean isNoteOn)
{
  static int buff[BUFFER_LENGTH];
  static int buffSize = 0;

  if (isNoteOn == true)
  {
    envelope1.noteOn();
  }
  else
  {
    envelope1.noteOff();
  }
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
      V1_A.frequency(noteFreqs[note]);
      V1_B.frequency(noteFreqs[note]);
      // envelope1.noteOn();
      keyBuff(note, true);
    }
    break;

  case midi::NoteOff:
    note = MIDI.getData1();
    // envelope1.noteOff();
    keyBuff(note, false);
    break;

  case midi::PitchBend:
    break;

  case midi::ControlChange:
    break;
  }
}

void handleButtonPress(boolean *buttonsState)
{
  for (int i = 0; i < 4; i++)
  {
    if (buttonsState[i] != prevButtonsState[i]) // which button changed?
    {
      prevButtonsState[i] = buttonsState[i];
      int pressedButton = i;
      switch (pressedButton)
      {
      case 0:
        if (buttonsState[i] == 1)
        {
          globalState.WAVEFORM1 = WAVEFORM_SQUARE;
          V1_A.begin(globalState.WAVEFORM1);
          // waveform1.begin(WAVEFORM_SQUARE);
        }
        else
        {
          globalState.WAVEFORM2 = WAVEFORM_SAWTOOTH;
          V1_A.begin(globalState.WAVEFORM2);
        }
        break;

      case 1:
        if (buttonsState[i] == 1)
        {
          globalState.WAVEFORM2 = WAVEFORM_SQUARE;
          V1_B.begin(globalState.WAVEFORM2);
        }
        else
        {
          globalState.WAVEFORM2 = WAVEFORM_SAWTOOTH;
          V1_B.begin(globalState.WAVEFORM2);
        }
        break;

      case 2:
        break;

      case 3:
        break;

      default:
        break;
      }
    }
  }
}

void handleKnobChange(pot knob)
{
  int knobName = knob.name;
  int knobValue = knob.value;
  switch (knobName)
  {
  case 0: // VOLUME 1
    globalState.OSC1_VOL = 1 - (float(knobValue) * DIV1023);
    // Serial.println(globalState.OSC1_VOL);
    V1_MIX.gain(0, globalState.OSC1_VOL);
    break;
  case 5: // VOLUME 2
    globalState.OSC2_VOL = 1 - (float(knobValue) * DIV1023);
    // Serial.println(globalState.OSC2_VOL);
    V1_MIX.gain(1, globalState.OSC2_VOL);
    break;
  case 10: // FILTER_FREQ
    globalState.FILTER_FREQ = 10000 * (1 - (float(knobValue) * DIV1023));
    filter1.frequency(globalState.FILTER_FREQ);
    break;

  case 11: // FILTER_Q
    globalState.FILTER_Q = 4.3 * (1 - (float(knobValue) * DIV1023)) + 0.7;
    filter1.resonance(globalState.FILTER_Q);
    Serial.println(globalState.FILTER_Q);
    break;
  case 12: // AMP_ATTACK
    globalState.AMP_ATTACK = 11880 * (1 - (float(knobValue) * DIV1023));
    envelope1.attack(globalState.AMP_ATTACK);
    Serial.println(globalState.AMP_ATTACK);
    break;
  case 13: // AMP_DECAY
    globalState.AMP_DECAY = 11880 * (1 - (float(knobValue) * DIV1023));
    envelope1.decay(globalState.AMP_DECAY);
    Serial.println(globalState.AMP_DECAY);
    break;
  case 14: // AMP_SUSTAIN
    globalState.AMP_SUSTAIN = 1 - (float(knobValue) * DIV1023);
    envelope1.sustain(globalState.AMP_SUSTAIN);
    Serial.println(globalState.AMP_SUSTAIN);
    break;
  case 15: // AMP_RELEASE
    globalState.AMP_RELEASE = 11880 * (1 - (float(knobValue) * DIV1023));
    envelope1.release(globalState.AMP_RELEASE);
    Serial.println(globalState.AMP_RELEASE);
    break;

  default:
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
