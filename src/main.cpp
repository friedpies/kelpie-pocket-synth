#include <Arduino.h>
// #include <Audio.h>

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <pinDefines.h>

void setup()
{
  Serial.begin(9600);
  pinMode(SWLED1, OUTPUT);
  pinMode(SWLED2, OUTPUT);
  pinMode(SWLED3, OUTPUT);
  pinMode(SWLED4, OUTPUT);

  digitalWrite(SWLED1, LOW);
  digitalWrite(SWLED2, LOW);
  digitalWrite(SWLED3, LOW);
  digitalWrite(SWLED4, LOW);
  digitalWrite(MIDILED, LOW);
}

void loop()
{
  digitalWrite(SWLED1, HIGH);
  delay(150);
  digitalWrite(SWLED1, LOW);
  delay(150);

  digitalWrite(SWLED2, HIGH);
  delay(150);
  digitalWrite(SWLED2, LOW);
  delay(150);

  digitalWrite(SWLED3, HIGH);
  delay(150);
  digitalWrite(SWLED3, LOW);
  delay(150);

  digitalWrite(SWLED4, HIGH);
  delay(150);
  digitalWrite(SWLED4, LOW);
  delay(150);

}