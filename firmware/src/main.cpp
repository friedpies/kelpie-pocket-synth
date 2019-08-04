#include <Arduino.h>

#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <audioConnections.h>
#include <keyMappings.h>

// all pin defines and assignments
#include <Kelpie.h>

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

potentiometers knobState;

void setup()
{
  MIDI.begin();
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.75);
  waveform1.frequency(82.41);
  waveform1.pulseWidth(0.15);

  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(0.75);
  waveform2.frequency(123);
  waveform2.pulseWidth(0.15);

  pink1.amplitude(0.0);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);
}

void handleMidiEvent(byte channelByte, byte controlByte, byte valueByte)
{
  byte type = MIDI.getType();
  Serial.println(controlByte);
  Serial.println(valueByte);
  Serial.println();
  int note, velocity;
  switch (type)
  {
  case midi::NoteOn:
    note = MIDI.getData1();
    velocity = MIDI.getData2();
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

void loop()
{
  if (MIDI.read())
  {
    byte channel = MIDI.getChannel();
    byte controlType = MIDI.getData1();
    byte value = MIDI.getData2();
    handleMidiEvent(channel, controlType, value);
  }

  if (kelpie.pollKnobs())
  {
    knobState = kelpie.getKnobs();
    for (int i = 0; i < 16; i++)
    {
      // Serial.print(knobState.state[i]);
      // Serial.print(" ");
    }
    // Serial.println();
  }
  if (kelpie.pollButtons())
  {
    Serial.println("A button was pressed");
  }
}
