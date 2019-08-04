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

// all pin defines and assignments
#include <Kelpie.h>

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

int *knobsState;

boolean prevButtonsState[4] = {false, false, false, false}; // initial state on boot
boolean *buttonsState;

void setup()
{
  MIDI.begin();
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(globalState.MASTER_VOL);
  waveform1.begin(globalState.WAVEFORM1);
  waveform1.amplitude(globalState.OSC1_VOL);
  waveform1.frequency(82.41);
  waveform1.pulseWidth(0.15);

  waveform2.begin(globalState.WAVEFORM2);
  waveform2.amplitude(globalState.OSC2_VOL);
  waveform2.frequency(82.41);
  waveform2.pulseWidth(0.15);

  pink1.amplitude(0.0);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);

  // GET KNOBS
  kelpie.pollKnobs(true); // force system to read value of knobs
  knobsState = kelpie.getKnobs();
  for (int i = 0; i < 16; i++) {
    Serial.println(knobsState[i]);
  }
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

void handleKnobChange(int *knobsState) {

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

  if (kelpie.pollKnobs(false))
  {
    knobsState = kelpie.getKnobs();
    handleKnobChange(knobsState);
    for (int i = 0; i < 16; i++)
    {
      Serial.print(knobsState[i]);
      Serial.print(" ");
    }
    Serial.println();
  }

  if (kelpie.pollButtons())
  {
    buttonsState = kelpie.getButtons();
    handleButtonPress(buttonsState);
  }
}
