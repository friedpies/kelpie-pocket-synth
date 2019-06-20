#include <Arduino.h>
// #include <Audio.h>

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <pinDefines.h>
#include <globalVariables.h>
#include <Kelpie.h>

Kelpie kelpie(false); // true enables serial

void setup()
{
}

void loop()
{
  kelpie.activateLights();
  delay(500);
  kelpie.deactivateLights();
  delay(500);
}