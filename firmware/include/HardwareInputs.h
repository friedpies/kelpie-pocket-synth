// VARIOUS STRUCTS TO DEFINE PARAMETERS FOR HARDWARE INPUT TYPES

#ifndef hardware_input_h
#define hardware_input_h

#include <Bounce.h>
// struct to store individual pot names into a vector
struct pot
{
  boolean didChange;
  int name;
  int value;
};

struct potentiometers
{
  int name[16];  // variable name of knob
  int value[16]; // current polled value
  int state[16]; // actual state value
};

struct buttons
{
  Bounce buttonName[4];
  int ledName[4];
  boolean state[4];
};
#endif