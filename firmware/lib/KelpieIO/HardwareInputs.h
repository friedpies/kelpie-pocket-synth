// VARIOUS STRUCTS TO DEFINE PARAMETERS FOR HARDWARE INPUT TYPES

#ifndef hardware_input_h
#define hardware_input_h

#include <Bounce.h>
// struct to store individual Potentiometer names into a vector
enum KnobNames
{
  BALANCE_KNOB,
  PWM_KNOB,
  ATTACK_KNOB,
  DECAY_KNOB,
  VOL_KNOB,
  NOISE_KNOB,
  COARSE_KNOB,
  SUSTAIN_KNOB,
  RELEASE_KNOB,
  GLIDE_KNOB,
  FREQ_KNOB,
  Q_KNOB,
  DEPTH_KNOB,
  RATE_KNOB,
  FILTER_KNOB,
  AMP_KNOB
};

struct Potentiometer
{
  KnobNames knobName;
  byte pinNum;
  boolean didChange;
  int polledValue;
  int setValue;
};

struct Buttons
{
  Bounce buttonName[4];
  byte ledName[4];
  boolean state[4];
};
#endif