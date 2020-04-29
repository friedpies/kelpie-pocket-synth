// MAIN CODE FOR KELPIE SYNTHESIZER
// WRITTEN BY KENNETH MARUT (WWW.KENNETHMARUT.COM)
// THIS PROJECT CAN BE FOLLOWED HERE: https://hackaday.io/project/166460-kelpie-synth-module-for-keyboard-controllers

#include <Arduino.h>
#include <MIDI.h>
#include <KelpieAudioManager.h>
#include <SynthVoice.h>
#include <SynthState.h>
#include <VoiceManager.h>
#include <KelpieHelpers.h>
#include <KelpieIO.h>

#define DEBUG false

elapsedMillis fps;
KelpieIO kelpieIO(true);
VoiceManager voiceManager;
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

byte changedKnobIndex;
byte changedButtonIndex;

const byte MONOBUFFERSIZE = 8; // how many voices we allow to be stored in the MONO buffer
byte monoBuffer[MONOBUFFERSIZE];
const byte numPolyVoices = 8; //

void handleMidiEvent(byte channelByte, byte controlByte, byte valueByte)
{
  byte messageType = MIDI.getType();
  byte note = MIDI.getData1();
  byte velocity = MIDI.getData2();
  int pitch = 0; // initialize to zero, only applies in pitch bend case
  float pitchBend = 0.00;
  switch (messageType)
  {
  case midi::NoteOn:
    kelpieIO.blinkMidiLED(true);
    if (note > 23 && note < 108)
    {
      voiceManager.audioManager.LFO.phase(0); // retrigger LFO on keypress
      float noteGain = pow(float(velocity) * DIV127, VELOCITY_CURVE);

      if (voiceManager.globalState.IS_POLY == true) // depending on mode send to buffer
      {
        keyBuffPoly(note, noteGain, true);
      }
      else
      {
        keyBuffMono(note, noteGain, true);
      }
    }
    break;

  case midi::NoteOff:
    kelpieIO.blinkMidiLED(false);
    if (note > 23 && note < 108)
    {
      if (voiceManager.globalState.IS_POLY == true) // depending on mode send to buffer
      {
        keyBuffPoly(note, velocity, false);
      }
      else
      {
        keyBuffMono(note, velocity, false);
      }
    }
    break;

  case midi::PitchBend:
    pitch = velocity * 256 + note; // this converts 8 bit values into a 16 bit value for precise pitch control
    pitchBend = map(double(pitch), 0, 32767, -2, 2);
    voiceManager.globalState.PITCH_BEND = pow(2, pitchBend / 12);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      float currentFreq = voiceManager.polyVoices[i].noteFreq;
      voiceManager.polyVoices[i].waveformA.frequency(currentFreq * voiceManager.globalState.PITCH_BEND);
      voiceManager.polyVoices[i].waveformB.frequency(currentFreq * voiceManager.globalState.PITCH_BEND * voiceManager.globalState.DETUNE);
    }
    break;

  case midi::ControlChange:
    byte ccNum = note; // redefining for clarity
    byte value = velocity;
    float normalizedKnobVal = (value * DIV127);
    switch (ccNum)
    {
    case 1: // MODULATION WHEEL
      voiceManager.globalState.LFO_FREQ = normalizedKnobVal * LFO_FREQ_MAX;
      voiceManager.audioManager.LFO.frequency(voiceManager.globalState.LFO_FREQ);
      break;
    case 5: // GLIDE
      break;
    case 7: // MASTER VOLUME
      voiceManager.globalState.MASTER_VOL = normalizedKnobVal * MAX_MASTER_GAIN;
      voiceManager.audioManager.MASTER_GAIN.gain(voiceManager.globalState.MASTER_VOL * voiceManager.globalState.POLY_GAIN_MULTIPLIER);
      break;
    case 8: // OSC BALANCE
      voiceManager.globalState.OSC1_VOL = normalizedKnobVal;
      voiceManager.globalState.OSC2_VOL = 1 - (normalizedKnobVal);
      voiceManager.globalState.OSC_CONSTANT = calculateOscConstant(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL);
      setWaveformLevels(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL, voiceManager.globalState.OSC_CONSTANT);
      break;
    case 102: // OSCILLATOR PWM
      voiceManager.setPWM(0.1 + 0.4 * (1 - normalizedKnobVal));
      break;
    case 103: // NOISE VOLUME
      voiceManager.globalState.NOISE_VOL = normalizedKnobVal;
      voiceManager.globalState.OSC_CONSTANT = calculateOscConstant(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL);
      setWaveformLevels(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL, voiceManager.globalState.OSC_CONSTANT);
      break;
    case 104: // OSC DETUNE
      voiceManager.globalState.DETUNE = calculateDetuneValue(normalizedKnobVal);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].waveformB.frequency(voiceManager.polyVoices[i].noteFreq * voiceManager.globalState.DETUNE * voiceManager.globalState.PITCH_BEND);
      }
      break;
    case 105: // FILTER FREQUENCY
      voiceManager.globalState.FILTER_FREQ = FILTER_CUTOFF_MAX * pow(normalizedKnobVal, 3);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filter.frequency(voiceManager.globalState.FILTER_FREQ);
      }
      break;
    case 106: // FILTER RESONANCE
      voiceManager.setFilterQ((FILTER_Q_MAX * normalizedKnobVal) + 1.1);
      break;
    case 107: // FILTER DEPTH
      voiceManager.globalState.FILTER_OCTAVE = FILTER_OCTAVE_DEPTH * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filter.octaveControl(voiceManager.globalState.FILTER_OCTAVE);
      }
      break;
    case 108: // LFO RATE
      voiceManager.globalState.LFO_FREQ = LFO_FREQ_MAX * pow(normalizedKnobVal, 5);
      voiceManager.audioManager.LFO.frequency(voiceManager.globalState.LFO_FREQ);
      break;
    case 109: // LFO DESTINATION FILTER
      voiceManager.globalState.LFO_FILTER_GAIN = (normalizedKnobVal);
      voiceManager.audioManager.LFO_MIXER_FILTER.gain(1, voiceManager.globalState.LFO_FILTER_GAIN);
      break;
    case 110: // LFO DESTINATION AMP
      voiceManager.globalState.LFO_AMP_GAIN = (normalizedKnobVal);
      voiceManager.audioManager.LFO_MIXER_AMP.gain(1, voiceManager.globalState.LFO_AMP_GAIN);
      break;
    case 111: // AMP ATTACK
      voiceManager.globalState.AMP_ATTACK = AMP_ATTACK_MAX * (normalizedKnobVal);
      if (voiceManager.globalState.AMP_ATTACK < 15) //
      {
        voiceManager.globalState.AMP_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.attack(voiceManager.globalState.AMP_ATTACK);
      }
      break;
    case 112: // AMP DECAY
      voiceManager.globalState.AMP_DECAY = AMP_DECAY_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.decay(voiceManager.globalState.AMP_DECAY);
      }
      break;
    case 113: // AMP SUSTAIN
      voiceManager.globalState.AMP_SUSTAIN = normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.sustain(voiceManager.globalState.AMP_SUSTAIN);
      }
      break;
    case 114: // AMP RELEASE
      voiceManager.globalState.AMP_RELEASE = AMP_RELEASE_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.release(voiceManager.globalState.AMP_RELEASE);
      }
      break;
    case 115: // FILTER ATTACK
      voiceManager.globalState.FILTER_ATTACK = FILTER_ATTACK_MAX * normalizedKnobVal;
      if (voiceManager.globalState.FILTER_ATTACK < 15) //
      {
        voiceManager.globalState.FILTER_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.attack(voiceManager.globalState.FILTER_ATTACK);
      }
      break;
    case 116: // FILTER DECAY
      voiceManager.globalState.FILTER_DECAY = FILTER_DECAY_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.decay(voiceManager.globalState.FILTER_DECAY);
      }
      break;
    case 117: // FILTER SUSTAIN
      voiceManager.globalState.FILTER_SUSTAIN = normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.sustain(voiceManager.globalState.FILTER_SUSTAIN);
      }
      break;
    case 118: // FILTER RELEASE
      voiceManager.globalState.FILTER_RELEASE = FILTER_RELEASE_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.release(voiceManager.globalState.FILTER_RELEASE);
      }
      break;
    }
    break;
  }
}

void setup()
{
  MIDI.begin();
  voiceManager.initVoices();
  voiceManager.initAudio();

  // READ AND INITIALIZE ALL KNOBS
  for (byte knobIndex = 0; knobIndex < 16; knobIndex++)
  {
    kelpieIO.setKnobOnStartup(knobIndex);
    handleKnobChange(kelpieIO.getKnob(knobIndex));
  }
  kelpieIO.bootupAnimation();
}

void loop()
{
  if (MIDI.read())
  {
    byte channel = MIDI.getChannel();
    byte controlType = MIDI.getData1();
    byte value = MIDI.getData2();
    handleMidiEvent(channel, controlType, value);
  }

  changedKnobIndex = kelpieIO.getIndexOfChangedKnob();
  if (changedKnobIndex > -1)
  {
    handleKnobChange(kelpieIO.getKnob(changedKnobIndex));
  }

  changedButtonIndex = kelpieIO.getIndexOfChangedButton();
  if (changedButtonIndex > -1)
  {
    handleButtonPress(kelpieIO.getButton(changedButtonIndex));
  }

  if (DEBUG)
  {
    if (fps > 24)
    {
      if (voiceManager.audioManager.PEAK.available())
      {
        fps = 0;
        int monoPeak = voiceManager.audioManager.PEAK.read() * 100.0;
        Serial.print("|");
        for (int cnt = 0; cnt < 100; cnt++)
          if (cnt < monoPeak)
          {
            Serial.print(">");
          }
          else if (cnt >= monoPeak && cnt < 99)
          {
            Serial.print(" ");
          }
          else if (cnt > 99)
          {
            Serial.println("|");
          }
        Serial.print(monoPeak);
        Serial.println();
      }
    }
  }
}
