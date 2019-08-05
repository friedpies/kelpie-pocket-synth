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

// all pin defines and assignments
#include <Kelpie.h>

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

int prevKnobsState[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int *knobsState;

boolean prevButtonsState[4] = {false, false, false, false}; // initial state on boot
boolean *buttonsState;

std::vector<potQueue> knobQueue;

void setup()
{
  // GET KNOBS
  // kelpie.pollKnobs(true); // force system to read value of knobs
  // knobsState = kelpie.getKnobs();
  // for (int i = 0; i < 16; i++)
  // {
  //   prevKnobsState[i] = knobsState[i];
  // }

  // set global state based off of initial knob values
  // globalState.OSC1_VOL = knobsState[0];
  // globalState.OSC2_VOL = knobsState[5];

  MIDI.begin();
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(globalState.MASTER_VOL);

  waveform1.begin(globalState.WAVEFORM1);
  waveform1.amplitude(.75);
  waveform1.frequency(82.41);
  waveform1.pulseWidth(0.15);

  waveform2.begin(globalState.WAVEFORM2);
  waveform2.amplitude(.75);
  waveform2.frequency(82.41);
  waveform2.pulseWidth(0.15);

  pink1.amplitude(0.0);

  mixer1.gain(0, globalState.OSC1_VOL);
  mixer1.gain(1, globalState.OSC2_VOL);
  mixer1.gain(2, 1.0);
}

void handleMidiEvent(byte channelByte, byte controlByte, byte valueByte)
{
  byte type = MIDI.getType();
  Serial.println(controlByte);
  Serial.println(valueByte);
  Serial.println();
  int note;
  switch (type)
  {
  case midi::NoteOn:
    note = MIDI.getData1();
    // velocity = MIDI.getData2();
    if (note > 23 && note < 108)
    {
      waveform1.frequency(noteFreqs[note]);
      waveform2.frequency(noteFreqs[note]);
    }
    break;

  case midi::NoteOff:
    note = MIDI.getData1();
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
          waveform1.begin(globalState.WAVEFORM1);
          // waveform1.begin(WAVEFORM_SQUARE);
        }
        else
        {
          globalState.WAVEFORM2 = WAVEFORM_SAWTOOTH;
          waveform1.begin(globalState.WAVEFORM2);
        }
        break;

      case 1:
        if (buttonsState[i] == 1)
        {
          globalState.WAVEFORM2 = WAVEFORM_SQUARE;
          waveform2.begin(globalState.WAVEFORM2);
        }
        else
        {
          globalState.WAVEFORM2 = WAVEFORM_SAWTOOTH;
          waveform2.begin(globalState.WAVEFORM2);
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

void handleKnobChange(int *knobsState)
{
  for (int i = 0; i < 16; i++)
  {
    if (knobsState[i] != prevKnobsState[i]) // which knob changed?
    {
      prevKnobsState[i] = knobsState[i];
      int changedKnob = i;
      switch (changedKnob)
      {
      case 0:
        globalState.OSC1_VOL = float(knobsState[0]) * DIV1023;
        Serial.println(globalState.OSC1_VOL);
        mixer1.gain(0, globalState.OSC1_VOL);
        break;
      case 5:
        globalState.OSC2_VOL = float(knobsState[5]) * DIV1023;
        Serial.println(globalState.OSC2_VOL);
        mixer1.gain(0, globalState.OSC2_VOL);
        break;
      default:
        break;
      }
    }
  }
}

void loop()
{
  if (MIDI.read())
  {
    byte channel = MIDI.getChannel();
    byte controlType = MIDI.getData1();
    byte value = MIDI.getData2();
    handleMidiEvent(channel, controlType, value);
  }

  knobQueue = kelpie.pollKnobs(false);
  if (knobQueue.size() > 0)
  {
    Serial.println(knobQueue.size());
  }
  // if (kelpie.pollKnobs(false))
  // {
  //   knobsState = kelpie.getKnobs();
  //   handleKnobChange(knobsState);
  //   for (int i = 0; i < 16; i++)
  //   {
  //     // Serial.print(knobsState[i]);
  //     // Serial.print(" ");
  //   }
  //   // Serial.println();
  // }

  if (kelpie.pollButtons())
  {
    buttonsState = kelpie.getButtons();
    handleButtonPress(buttonsState);
  }
}
