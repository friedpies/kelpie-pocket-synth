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

SynthState globalState;

SynthVoice VOICE_1 = {0, 0.0, 0, false, voiceManager.audioManager.V1_A, voiceManager.audioManager.V1_B, voiceManager.audioManager.V1_N, voiceManager.audioManager.V1_MIX, voiceManager.audioManager.V1_AMP, voiceManager.audioManager.V1_ENV, voiceManager.audioManager.V1_FILT_ENV, voiceManager.audioManager.V1_FILT, globalState};
SynthVoice VOICE_2 = {0, 0.0, 0, false, voiceManager.audioManager.V2_A, voiceManager.audioManager.V2_B, voiceManager.audioManager.V2_N, voiceManager.audioManager.V2_MIX, voiceManager.audioManager.V2_AMP, voiceManager.audioManager.V2_ENV, voiceManager.audioManager.V2_FILT_ENV, voiceManager.audioManager.V2_FILT, globalState};
SynthVoice VOICE_3 = {0, 0.0, 0, false, voiceManager.audioManager.V3_A, voiceManager.audioManager.V3_B, voiceManager.audioManager.V3_N, voiceManager.audioManager.V3_MIX, voiceManager.audioManager.V3_AMP, voiceManager.audioManager.V3_ENV, voiceManager.audioManager.V3_FILT_ENV, voiceManager.audioManager.V3_FILT, globalState};
SynthVoice VOICE_4 = {0, 0.0, 0, false, voiceManager.audioManager.V4_A, voiceManager.audioManager.V4_B, voiceManager.audioManager.V4_N, voiceManager.audioManager.V4_MIX, voiceManager.audioManager.V4_AMP, voiceManager.audioManager.V4_ENV, voiceManager.audioManager.V4_FILT_ENV, voiceManager.audioManager.V4_FILT, globalState};
SynthVoice VOICE_5 = {0, 0.0, 0, false, voiceManager.audioManager.V5_A, voiceManager.audioManager.V5_B, voiceManager.audioManager.V5_N, voiceManager.audioManager.V5_MIX, voiceManager.audioManager.V5_AMP, voiceManager.audioManager.V5_ENV, voiceManager.audioManager.V5_FILT_ENV, voiceManager.audioManager.V5_FILT, globalState};
SynthVoice VOICE_6 = {0, 0.0, 0, false, voiceManager.audioManager.V6_A, voiceManager.audioManager.V6_B, voiceManager.audioManager.V6_N, voiceManager.audioManager.V6_MIX, voiceManager.audioManager.V6_AMP, voiceManager.audioManager.V6_ENV, voiceManager.audioManager.V6_FILT_ENV, voiceManager.audioManager.V6_FILT, globalState};
SynthVoice VOICE_7 = {0, 0.0, 0, false, voiceManager.audioManager.V7_A, voiceManager.audioManager.V7_B, voiceManager.audioManager.V7_N, voiceManager.audioManager.V7_MIX, voiceManager.audioManager.V7_AMP, voiceManager.audioManager.V7_ENV, voiceManager.audioManager.V7_FILT_ENV, voiceManager.audioManager.V7_FILT, globalState};
SynthVoice VOICE_8 = {0, 0.0, 0, false, voiceManager.audioManager.V8_A, voiceManager.audioManager.V8_B, voiceManager.audioManager.V8_N, voiceManager.audioManager.V8_MIX, voiceManager.audioManager.V8_AMP, voiceManager.audioManager.V8_ENV, voiceManager.audioManager.V8_FILT_ENV, voiceManager.audioManager.V8_FILT, globalState};

const byte numPolyVoices = 8; //
SynthVoice polyVoices[numPolyVoices] = {
    VOICE_1,
    VOICE_2,
    VOICE_3,
    VOICE_4,
    VOICE_5,
    VOICE_6,
    VOICE_7,
    VOICE_8};

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

      if (globalState.IS_POLY == true) // depending on mode send to buffer
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
      if (globalState.IS_POLY == true) // depending on mode send to buffer
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
    globalState.PITCH_BEND = pow(2, pitchBend / 12);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      float currentFreq = polyVoices[i].noteFreq;
      polyVoices[i].waveformA.frequency(currentFreq * globalState.PITCH_BEND);
      polyVoices[i].waveformB.frequency(currentFreq * globalState.PITCH_BEND * globalState.DETUNE);
    }
    break;

  case midi::ControlChange:
    byte ccNum = note; // redefining for clarity
    byte value = velocity;
    float normalizedKnobVal = (value * DIV127);
    switch (ccNum)
    {
    case 1: // MODULATION WHEEL
      globalState.LFO_FREQ = normalizedKnobVal * LFO_FREQ_MAX;
      voiceManager.audioManager.LFO.frequency(globalState.LFO_FREQ);
      break;
    case 5: // GLIDE
      break;
    case 7: // MASTER VOLUME
      globalState.MASTER_VOL = normalizedKnobVal * MAX_MASTER_GAIN;
      voiceManager.audioManager.MASTER_GAIN.gain(globalState.MASTER_VOL * globalState.POLY_GAIN_MULTIPLIER);
      break;
    case 8: // OSC BALANCE
      globalState.OSC1_VOL = normalizedKnobVal;
      globalState.OSC2_VOL = 1 - (normalizedKnobVal);
      globalState.OSC_CONSTANT = calculateOscConstant(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL);
      setWaveformLevels(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL, globalState.OSC_CONSTANT);
      break;
    case 102: // OSCILLATOR PWM
      globalState.PWM = 0.1 + 0.4 * (1 - normalizedKnobVal);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].waveformA.pulseWidth(globalState.PWM);
        polyVoices[i].waveformB.pulseWidth(globalState.PWM);
      }
      break;
    case 103: // NOISE VOLUME
      globalState.NOISE_VOL = normalizedKnobVal;
      globalState.OSC_CONSTANT = calculateOscConstant(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL);
      setWaveformLevels(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL, globalState.OSC_CONSTANT);
      break;
    case 104: // OSC DETUNE
      globalState.DETUNE = calculateDetuneValue(normalizedKnobVal);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].waveformB.frequency(polyVoices[i].noteFreq * globalState.DETUNE * globalState.PITCH_BEND);
      }
      break;
    case 105: // FILTER FREQUENCY
      globalState.FILTER_FREQ = FILTER_CUTOFF_MAX * pow(normalizedKnobVal, 3);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filter.frequency(globalState.FILTER_FREQ);
      }
      break;
    case 106: // FILTER RESONANCE
      globalState.FILTER_Q = (FILTER_Q_MAX * normalizedKnobVal) + 1.1;
      globalState.PREFILTER_GAIN = 1 / globalState.FILTER_Q;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filter.resonance(globalState.FILTER_Q);
      }
      break;
    case 107: // FILTER DEPTH
      globalState.FILTER_OCTAVE = FILTER_OCTAVE_DEPTH * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filter.octaveControl(globalState.FILTER_OCTAVE);
      }
      break;
    case 108: // LFO RATE
      globalState.LFO_FREQ = LFO_FREQ_MAX * pow(normalizedKnobVal, 5);
      voiceManager.audioManager.LFO.frequency(globalState.LFO_FREQ);
      break;
    case 109: // LFO DESTINATION FILTER
      globalState.LFO_FILTER_GAIN = (normalizedKnobVal);
      voiceManager.audioManager.LFO_MIXER_FILTER.gain(1, globalState.LFO_FILTER_GAIN);
      break;
    case 110: // LFO DESTINATION AMP
      globalState.LFO_AMP_GAIN = (normalizedKnobVal);
      voiceManager.audioManager.LFO_MIXER_AMP.gain(1, globalState.LFO_AMP_GAIN);
      break;
    case 111: // AMP ATTACK
      globalState.AMP_ATTACK = AMP_ATTACK_MAX * (normalizedKnobVal);
      if (globalState.AMP_ATTACK < 15) //
      {
        globalState.AMP_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.attack(globalState.AMP_ATTACK);
      }
      break;
    case 112: // AMP DECAY
      globalState.AMP_DECAY = AMP_DECAY_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.decay(globalState.AMP_DECAY);
      }
      break;
    case 113: // AMP SUSTAIN
      globalState.AMP_SUSTAIN = normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.sustain(globalState.AMP_SUSTAIN);
      }
      break;
    case 114: // AMP RELEASE
      globalState.AMP_RELEASE = AMP_RELEASE_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.release(globalState.AMP_RELEASE);
      }
      break;
    case 115: // FILTER ATTACK
      globalState.FILTER_ATTACK = FILTER_ATTACK_MAX * normalizedKnobVal;
      if (globalState.FILTER_ATTACK < 15) //
      {
        globalState.FILTER_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.attack(globalState.FILTER_ATTACK);
      }
      break;
    case 116: // FILTER DECAY
      globalState.FILTER_DECAY = FILTER_DECAY_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.decay(globalState.FILTER_DECAY);
      }
      break;
    case 117: // FILTER SUSTAIN
      globalState.FILTER_SUSTAIN = normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.sustain(globalState.FILTER_SUSTAIN);
      }
      break;
    case 118: // FILTER RELEASE
      globalState.FILTER_RELEASE = FILTER_RELEASE_MAX * normalizedKnobVal;
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.release(globalState.FILTER_RELEASE);
      }
      break;
    }
    break;
  }
}

void setup()
{
  MIDI.begin();
  voiceManager.audioManager.init();
  voiceManager.audioManager.sgtl5000_1.volume(globalState.MASTER_VOL);

  AudioNoInterrupts();
  for (byte i = 0; i < numPolyVoices; i++)
  {
    polyVoices[i].waveformA.begin(globalState.WAVEFORM1);
    polyVoices[i].waveformA.amplitude(0.33);
    polyVoices[i].waveformA.frequency(82.41);
    polyVoices[i].waveformA.pulseWidth(0.15);

    polyVoices[i].waveformB.begin(globalState.WAVEFORM2);
    polyVoices[i].waveformB.amplitude(0.33);
    polyVoices[i].waveformB.frequency(82.41);
    polyVoices[i].waveformB.pulseWidth(0.15);

    polyVoices[i].noise.amplitude(0.33);

    polyVoices[i].waveformMixer.gain(0, 1.0);
    polyVoices[i].waveformMixer.gain(1, 1.0);
    polyVoices[i].waveformMixer.gain(2, 1.0);

    polyVoices[i].waveformAmplifier.gain(0.0);

    polyVoices[i].ampEnv.attack(globalState.AMP_ATTACK);
    polyVoices[i].ampEnv.decay(globalState.AMP_DECAY);
    polyVoices[i].ampEnv.sustain(globalState.AMP_SUSTAIN);
    polyVoices[i].ampEnv.release(globalState.AMP_RELEASE);

    polyVoices[i].filter.frequency(globalState.FILTER_FREQ);
    polyVoices[i].filter.resonance(globalState.FILTER_Q);
    polyVoices[i].filter.octaveControl(2.0);
  }
  AudioInterrupts();

  voiceManager.audioManager.DC_OFFSET.amplitude(1.0);
  voiceManager.audioManager.LFO.amplitude(1.0);
  voiceManager.audioManager.LFO.frequency(2.0);
  voiceManager.audioManager.LFO.phase(90);

  voiceManager.audioManager.LFO_MIXER_FILTER.gain(0, 1); // THIS IS THE AMP THAT ADJUSTS HOW MUCH OF THE LFO IS FED INTO THE FILTER
  voiceManager.audioManager.LFO_MIXER_FILTER.gain(1, 0);

  for (byte i = 0; i < 4; i++)
  {
    voiceManager.audioManager.V14_MIX.gain(i, 0.25);
    voiceManager.audioManager.V58_MIX.gain(i, 0.25);
  }

  voiceManager.audioManager.ALL_VOICE_MIX.gain(0, 0.5);
  voiceManager.audioManager.ALL_VOICE_MIX.gain(1, 0.5);

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
