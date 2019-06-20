#include <Arduino.h>
// #include <Audio.h>

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <pinDefines.h>
#include <globalVariables.h>

void setup()
{
  Serial.begin(9600);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
}

void loop()
{
  Serial.print(digitalRead(SW1));
  Serial.print(" ");
  Serial.print(digitalRead(SW2));
  Serial.print(" ");
  Serial.print(digitalRead(SW3));
  Serial.print(" ");
  Serial.print(digitalRead(SW4));
  Serial.println(" ");
  // digitalWrite(SWLED1, HIGH);
  // delay(150);
  // digitalWrite(SWLED1, LOW);
  // delay(150);

  // digitalWrite(SWLED2, HIGH);
  // delay(150);
  // digitalWrite(SWLED2, LOW);
  // delay(150);

  // digitalWrite(SWLED3, HIGH);
  // delay(150);
  // digitalWrite(SWLED3, LOW);
  // delay(150);

  // digitalWrite(SWLED4, HIGH);
  // delay(150);
  // digitalWrite(SWLED4, LOW);
  // delay(150);
  // digitalWrite(MIDILED, HIGH);
  // delay(500);
  // digitalWrite(MIDILED, LOW);
  // delay(500);
}