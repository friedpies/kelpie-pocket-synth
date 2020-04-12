// VARIOUS STRUCTS TO DEFINE PARAMETERS FOR HARDWARE INPUT TYPES

#ifndef hardware_input_h
#define hardware_input_h

#include <Bounce.h>
// struct to store individual Potentiometer names into a vector
struct Potentiometer
{
  boolean didChange;
  byte name;
  int polledValue;
};

struct Knobs
{
  byte name[16];  // variable name of knob
  int value[16]; // current polled value
  int state[16]; // actual state value (there is some averaging and filtering that occurs to value before commiting the value to state)
};

struct Buttons
{
  Bounce buttonName[4];
  byte ledName[4];
  boolean state[4];
};
#endif