// VARIOUS STRUCTS TO DEFINE PARAMETERS FOR HARDWARE INPUT TYPES

#ifndef hardware_input_h
#define hardware_input_h

#include <Bounce.h>
// struct to store individual pot names into a vector
struct pot
{
  boolean didChange;
  byte name;
  int value;
};

struct potentiometers
{
  byte name[16];  // variable name of knob
  int value[16]; // current polled value
  int state[16]; // actual state value
};

struct buttons
{
  Bounce buttonName[4];
  byte ledName[4];
  boolean state[4];
};
#endif