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

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

boolean prevButtonsState[4] = {false, false, false, false}; // initial state on boot
boolean *buttonsState;
pot changedKnob;
const int bufferSize = 8;

const int polyBuffSize = 2;
voice polyBuff[polyBuffSize] = {VOICE_1, VOICE_2};

void setup()
{
  MIDI.begin();
  AudioMemory(40);
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
  }

  V1_N.amplitude(0.0);

  V1_MIX.gain(0, globalState.OSC1_VOL);
  V1_MIX.gain(1, globalState.OSC2_VOL);
  V1_MIX.gain(2, 1.0);

  V2_N.amplitude(0.0);

  V2_MIX.gain(0, globalState.OSC1_VOL);
  V2_MIX.gain(1, globalState.OSC2_VOL);
  V2_MIX.gain(2, 1.0);

  // V12_MIX
  V12_MIX.gain(0, 0.3);
  V12_MIX.gain(1, 0.3);
  V12_MIX.gain(2, 0.3);

  filter1.frequency(globalState.FILTER_FREQ);
  filter1.resonance(globalState.FILTER_Q);
}

void keyBuffMono(int note, boolean isNoteOn)
{
  // static int monoBuff[BUFFER_LENGTH];
  // static int buffSize = 0;

  if (isNoteOn == true)
  {
  }
  else
  {
  }
}

void keyBuffPoly(int note, boolean playNote)
{
  if (playNote)
  {
    for (int i = 0; i < polyBuffSize; i++)
    {
      if (polyBuff[i].ampEnv.isActive() == false)
      {
        polyBuff[i].waveformA.frequency(noteFreqs[note]);
        polyBuff[i].waveformB.frequency(noteFreqs[note]);
        polyBuff[i].note = note;
        polyBuff[i].ampEnv.noteOn();
        break;
      }
    }
  }
  else
  {
    Serial.println("I'm a note off");
    for (int i = 0; i < polyBuffSize; i++)
    {
      if (polyBuff[i].note == note)
      {
        polyBuff[i].ampEnv.noteOff();
        polyBuff[i].note = 0;
      }
    }
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
    V2_MIX.gain(0, globalState.OSC1_VOL);
    break;
  case 5: // VOLUME 2
    globalState.OSC2_VOL = 1 - (float(knobValue) * DIV1023);
    // Serial.println(globalState.OSC2_VOL);
    V1_MIX.gain(1, globalState.OSC2_VOL);
    V2_MIX.gain(1, globalState.OSC2_VOL);
    break;
  case 10: // FILTER_FREQ
    globalState.FILTER_FREQ = 10000 * (1 - (float(knobValue) * DIV1023));
    filter1.frequency(globalState.FILTER_FREQ);
    break;

  case 11: // FILTER_Q
    globalState.FILTER_Q = 4.3 * (1 - (float(knobValue) * DIV1023)) + 0.7;
    filter1.resonance(globalState.FILTER_Q);
    // Serial.println(globalState.FILTER_Q);
    break;
  case 12: // AMP_ATTACK
    globalState.AMP_ATTACK = 11880 * (1 - (float(knobValue) * DIV1023));
    // Serial.println(globalState.AMP_ATTACK);
    break;
  case 13: // AMP_DECAY
    globalState.AMP_DECAY = 11880 * (1 - (float(knobValue) * DIV1023));
    // Serial.println(globalState.AMP_DECAY);
    break;
  case 14: // AMP_SUSTAIN
    globalState.AMP_SUSTAIN = 1 - (float(knobValue) * DIV1023);
    // Serial.println(globalState.AMP_SUSTAIN);
    break;
  case 15: // AMP_RELEASE
    globalState.AMP_RELEASE = 11880 * (1 - (float(knobValue) * DIV1023));
    // Serial.println(globalState.AMP_RELEASE);
    break;

  default:
    break;
  }
}

void loop()
{
  Serial.print("VOICE ONE ACTIVE: ");
  Serial.print(V1_ENV.isActive());
  Serial.print("----");
  Serial.print("VOICE 2 ACTIVE: ");
  Serial.println(V2_ENV.isActive());

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
