#include <Arduino.h>
// #include <Audio.h>

#include <Audio.h>
#include <MIDI.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <pinDefines.h>
#include <globalVariables.h>
#include <Kelpie.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

Kelpie kelpie(false); // true enables serial

void setup()
{
  MIDI.begin();
}

void loop()
{
  while (MIDI.read()) {
    Serial.println("MIDI NOTE RECIEVED");
  }
  // kelpie.activateLights();
  // delay(500);
  // kelpie.deactivateLights();
  // delay(500);
}