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


void setup()
{
  MIDI.begin();
}

void loop()
{
  // while (MIDI.read()) {
  //   Serial.println("MIDI NOTE RECIEVED");
  // }
  kelpie.pollKnobs();
  kelpie.pollButtons();
}