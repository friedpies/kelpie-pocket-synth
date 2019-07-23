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
}

void loop()
{
  // while (MIDI.read()) {
  //   Serial.println("MIDI NOTE RECIEVED");
  // }
  // if (kelpie.pollKnobs().didChange) {
  //   Serial.println("CHANGED");
  // };
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