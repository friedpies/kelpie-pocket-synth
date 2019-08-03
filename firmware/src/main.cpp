#include <Arduino.h>


#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <audioConnections.h>

// all pin defines and assignments
#include <Kelpie.h>

Kelpie kelpie(true);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

potentiometer knobState;

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

  pink1.amplitude(1.0);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);
}

void handleMidiEvent(byte channelByte, byte controlByte, byte valueByte) {
  Serial.print(channelByte);
  Serial.print(' ');
  Serial.print(controlByte);
  Serial.print(' ');
  Serial.println(valueByte);
}

void loop()
{
  if (MIDI.read()) {
    byte channel = MIDI.getChannel();
    byte controlType = MIDI.getData1();
    byte value = MIDI.getData2();
    handleMidiEvent(channel, controlType, value);
  }

  if (kelpie.pollKnobs()) {
    knobState = kelpie.getKnobs();
    for (int i = 0; i < 16; i++) {
      Serial.print(knobState.state[i]);
      Serial.print(" ");
      
    }
    Serial.println();
  }
  kelpie.pollButtons();
}

