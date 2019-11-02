#include <KelpieHelpers.h>

void activateVoices(byte index, byte note, float frequency, float gain)
{
  polyVoices[index].note = note;
  polyVoices[index].noteFreq = frequency;
  polyVoices[index].waveformA.frequency(frequency * globalState.PITCH_BEND);
  polyVoices[index].waveformA.phase(0);
  polyVoices[index].waveformB.frequency(frequency * globalState.PITCH_BEND * globalState.DETUNE);
  polyVoices[index].waveformB.phase(0);
  polyVoices[index].waveformAmplifier.gain(gain);
  polyVoices[index].ampEnv.noteOn();
  polyVoices[index].filterEnv.noteOn();
}

void deactivateVoices(byte index, boolean stopOscillator)
{
  polyVoices[index].ampEnv.noteOff();
  polyVoices[index].filterEnv.noteOff();
  polyVoices[index].note = 0;
}

void playNoteMono(byte playMode, byte note, byte velocity)
{
  float baseNoteFreq = noteFreqs[note];
  float noteGain = float(velocity) * DIV127;
  Serial.println(noteGain);
  AudioNoInterrupts();
  switch (playMode) // WILL SWITCH TO ENUMS LATER
  {
  case 0: // PLAYNOTE
    for (byte i = 0; i < numPolyVoices; i++)
    {
      activateVoices(i, note, baseNoteFreq, noteGain);
    }
    break;
  case 1: // UPDATE NOTE
    for (byte i = 0; i < numPolyVoices; i++)
    {
      polyVoices[i].note = note;
      polyVoices[i].noteFreq = baseNoteFreq;
      polyVoices[i].waveformA.frequency(baseNoteFreq * globalState.PITCH_BEND);
      polyVoices[i].waveformB.frequency(baseNoteFreq * globalState.PITCH_BEND * globalState.DETUNE);
    }
    break;
  case 2: // STOP NOTE
    for (byte i = 0; i < numPolyVoices; i++)
    {
      deactivateVoices(i, true);
    }
    break;
  }
  AudioInterrupts();
};

void bufferShift(byte indexToRemove, byte currentIndexPlaying)
{
  for (byte i = indexToRemove + 1; i < currentIndexPlaying; i++)
  {
    monoBuffer[i - 1] = monoBuffer[i];
  }
}

void keyBuffMono(byte note, byte velocity, boolean playNote)
{
  static byte currentNote = 0;
  if (playNote)
  {
    if (currentNote == MONOBUFFERSIZE) // if we exceed buffer size, newest note goes on end, remove first note and shift all notes down 1
    {
      bufferShift(0, currentNote);
      currentNote = MONOBUFFERSIZE - 1;
    }
    monoBuffer[currentNote] = note;
    playNoteMono(0, note, velocity);
    currentNote++;
  }

  else // key is released
  {
    byte foundNoteIndex = MONOBUFFERSIZE; // default to index larger than buffer size
    for (byte i = 0; i < (currentNote + 1); i++)
    {
      if (note == monoBuffer[i])
      {
        foundNoteIndex = i;
        // note has to be stopped
        bufferShift(foundNoteIndex, currentNote);
        currentNote--;
        // playNoteMono(1, monoBuffer[currentNote - 1], velocity);
        break;
      }
    }
    if (currentNote == 0)
    {
      playNoteMono(2, note, velocity);
    }
  }
}

void keyBuffPoly(byte note, byte velocity, boolean playNote)
{
  if (playNote) // on keypress
  {
    float noteGain = float(velocity) * DIV127;
    float baseNoteFreq = noteFreqs[note];
    for (byte i = 0; i < numPolyVoices; i++)
    {
      if (polyVoices[i].ampEnv.isActive() == false)
      {
        activateVoices(i, note, baseNoteFreq, noteGain);
        break;
      }
    }
  }
  else // key released
  {
    for (byte i = 0; i < numPolyVoices; i++)
    {
      if (polyVoices[i].note == note)
      {
        deactivateVoices(i, false);
      }
    }
  }
}

void handleButtonPress(boolean *buttonsState)
{
  for (byte i = 0; i < 4; i++)
  {
    if (buttonsState[i] != prevButtonsState[i]) // which button changed?
    {
      prevButtonsState[i] = buttonsState[i];
      int pressedButton = i;
      boolean buttonState = boolean(buttonsState[i]);
      switch (pressedButton)
      {
      case 0: // button one was pressed, toggle between waveforms
        if (buttonState == true)
        {
          globalState.WAVEFORM1 = WAVEFORM_PULSE;
        }
        else
        {
          globalState.WAVEFORM1 = WAVEFORM_SAWTOOTH;
        }
        for (byte i = 0; i < numPolyVoices; i++)
        {
          polyVoices[i].waveformA.begin(globalState.WAVEFORM1);
        }
        break;

      case 1:
        if (buttonState == true)
        {
          globalState.WAVEFORM2 = WAVEFORM_PULSE;
        }
        else
        {
          globalState.WAVEFORM2 = WAVEFORM_SAWTOOTH;
        }
        for (byte i = 0; i < numPolyVoices; i++)
        {
          polyVoices[i].waveformB.begin(globalState.WAVEFORM2);
        }
        break;

      case 2:
        if (buttonState == true)
        {
          globalState.isPoly = true;
        }
        else
        {
          globalState.isPoly = false;
        }
        break;

      case 3:
        if (buttonState == true)
        {
          globalState.shift = true;
        }
        else
        {
          globalState.shift = false;
        }
        break;

      default:
        break;
      }
    }
  }
}

void handleKnobChange(pot knob)
{
  int knobName = knob.name;
  int knobValue = knob.value;
  float decKnobVal = float(knobValue) * DIV1023;

  switch (knobName)
  {
  case 0: // BALANCES OSC 1 and 2
    globalState.OSC1_VOL = decKnobVal;
    globalState.OSC2_VOL = 1 - decKnobVal;
    globalState.OSC_CONSTANT = calculateOscConstant(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL);
    setWaveformLevels(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL, globalState.OSC_CONSTANT);
    break;
  case 1: // PWM OF PULSE WAVES (ONLY APPLIES WHEN A PULSE WAVE IS ACTIVATED)
    globalState.PWM = 0.1 + 0.4 * (1 - decKnobVal);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      polyVoices[i].waveformA.pulseWidth(globalState.PWM);
      polyVoices[i].waveformB.pulseWidth(globalState.PWM);
    }
    break;
  case 2:                           // ATTACK
    if (globalState.shift == false) // FOR AMP
    {
      globalState.AMP_ATTACK = AMP_ATTACK_MAX * (1 - (float(knobValue) * DIV1023));
      if (globalState.AMP_ATTACK < 15) //
      {
        globalState.AMP_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.attack(globalState.AMP_ATTACK);
      }
    }
    else // FOR FILTER
    {
      globalState.FILTER_ATTACK = FILTER_ATTACK_MAX * (1 - (float(knobValue) * DIV1023));
      if (globalState.FILTER_ATTACK < 15) //
      {
        globalState.FILTER_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.attack(globalState.FILTER_ATTACK);
      }
    }
    break;
  case 3:                           // DECAY
    if (globalState.shift == false) // FOR AMP
    {
      globalState.AMP_DECAY = AMP_DECAY_MAX * (1 - (float(knobValue) * DIV1023));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.decay(globalState.AMP_DECAY);
      }
    }
    else
    { // FOR FILTER
      globalState.FILTER_DECAY = FILTER_DECAY_MAX * (1 - (float(knobValue) * DIV1023));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.decay(globalState.FILTER_DECAY);
      }
    }
    break;
  case 4: // MASTER_VOL
    globalState.MASTER_VOL = 2 * (1 - decKnobVal);
    amp1.gain(globalState.MASTER_VOL);
    break;
  case 5: // NOISE_PRESENSE
    globalState.NOISE_VOL = 1 - decKnobVal;
    globalState.OSC_CONSTANT = calculateOscConstant(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL);
    setWaveformLevels(globalState.OSC1_VOL, globalState.OSC2_VOL, globalState.NOISE_VOL, globalState.OSC_CONSTANT);
    break;
  case 6: // DETUNE
    globalState.DETUNE = calculateDetuneValue(knobValue);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      polyVoices[i].waveformB.frequency(polyVoices[i].noteFreq * globalState.DETUNE * globalState.PITCH_BEND);
    }
    break;
  case 7: // AMP_SUSTAIN
    if (globalState.shift == false)
    {
      globalState.AMP_SUSTAIN = 1 - (float(knobValue) * DIV1023);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.sustain(globalState.AMP_SUSTAIN);
      }
    }
    else
    {
      globalState.FILTER_SUSTAIN = 1 - (float(knobValue) * DIV1023);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.sustain(globalState.FILTER_SUSTAIN);
      }
    }
    break;
  case 8: // AMP_RELEASE
    if (globalState.shift == false)
    {
      globalState.AMP_RELEASE = AMP_RELEASE_MAX * (1 - (float(knobValue) * DIV1023));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].ampEnv.release(globalState.AMP_RELEASE);
      }
    }
    else
    {
      globalState.FILTER_RELEASE = FILTER_RELEASE_MAX * (1 - (float(knobValue) * DIV1023));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        polyVoices[i].filterEnv.release(globalState.FILTER_RELEASE);
      }
    }
    break;
  case 9:
    break;
  case 10: // FILTER_FREQ

    globalState.FILTER_FREQ = FILTER_CUTOFF_MAX * freqLog[(1023 - knobValue)] * DIV1023;
    for (byte i = 0; i < numPolyVoices; i++)
    {
      polyVoices[i].filter.frequency(globalState.FILTER_FREQ);
    }
    break;
  case 11: // FILTER_Q
    globalState.FILTER_Q = FILTER_Q_MAX * (1 - (float(knobValue) * DIV1023)) + 1.1;
    for (byte i = 0; i < numPolyVoices; i++)
    {
      polyVoices[i].filter.resonance(globalState.FILTER_Q);
    }
    break;
  case 12: // FILTER_DEPTH
    globalState.FILTER_OCTAVE = 7 * (1 - decKnobVal);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      polyVoices[i].filter.octaveControl(globalState.FILTER_OCTAVE);
    }
    break;
  case 13:
    globalState.LFO_FREQ = LFO_FREQ_MAX * (1 - decKnobVal);
    LFO.frequency(globalState.LFO_FREQ);
    break;
  case 14:

  case 15:
    globalState.LFO_MIXER_AMP = (1 - decKnobVal);
    LFO_MIXER_AMP.gain(1, globalState.LFO_MIXER_AMP);
    break;

  default:
    break;
  }
}

// this function is responsible to balancing OSC1, OSC2, and NOISE for each voice. This is necessary because KNOB 1 balances OSC1 and 2, while Knob 6 adds and subtracts noise presense from audio
float calculateOscConstant(float osc1Vol, float osc2Vol, float noiseVol)
{
  float numerator = (1 - noiseVol);
  float denominator = (osc1Vol + osc2Vol + noiseVol);
  float constant = numerator / denominator;
  return constant;
}

void setWaveformLevels(float osc1Vol, float osc2Vol, float noiseVol, float oscConstant)
{
  for (byte i = 0; i < numPolyVoices; i++)
  {
    polyVoices[i].waveformA.amplitude(osc1Vol * oscConstant);
    polyVoices[i].waveformB.amplitude(osc2Vol * oscConstant);
    polyVoices[i].noise.amplitude(noiseVol - (noiseVol * oscConstant));
  }
}

float calculateDetuneValue(int knobReading)
{
  int knobInverse = 1023 - knobReading;
  float mappedKnob = 0.0;

  // piecewise function that separates tuning knob into 3 sections
  // mid section is shallower to achieve finer tuning
  // lower and upper limits will push the tuning 1 octave higher or lower
  if (knobInverse >= 0 && knobInverse <= (362))
  {
    mappedKnob = knobInverse * 1.24; // 1.24 is calculated by dividing 1023/823
  }
  else if (knobInverse > (362) && knobInverse < (662))
  {
    // this line is calculated by interpolating the points between lower and upper sections
    mappedKnob = ((knobInverse - 362) * 0.413) + 449;
  }
  else if (knobInverse >= (662) && knobInverse <= 1023)
  {
    // this is a line with the same slope as the lower bound, but offset in X direction
    mappedKnob = (knobInverse - 200) * 1.24;
  }
  // converts mapped reading to float val between 0 and 1.0
  float decKnobVal = mappedKnob * DIV1023;
  // maps prev value to value between 1/2 and 2, this is is half or 2x the base frequency (octaves)
  return pow(2, 2 * (decKnobVal - 0.5));
}