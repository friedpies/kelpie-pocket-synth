#include <KelpieHelpers.h>

void keyBuffMono(int note, boolean isNoteOn)
{
  if (isNoteOn == true)
  {
  }
  else
  {
  }
}

void keyBuffPoly(int note, boolean playNote)
{
  if (playNote)
  {
    for (int i = 0; i < polyBuffSize; i++)
    {
      if (polyBuff[i].ampEnv.isActive() == false)
      {
        float baseNoteFreq = noteFreqs[note];
        polyBuff[i].noteFreq = baseNoteFreq; // SET VOICE FREQUENCY IN STATE
        polyBuff[i].waveformA.frequency(baseNoteFreq);
        polyBuff[i].waveformB.frequency(baseNoteFreq * globalState.DETUNE_COARSE);
        polyBuff[i].note = note;
        polyBuff[i].ampEnv.noteOn();
        polyBuff[i].filterEnv.noteOn();
        break;
      }
    }
  }
  else
  {
    for (int i = 0; i < polyBuffSize; i++)
    {
      if (polyBuff[i].note == note)
      {
        polyBuff[i].ampEnv.noteOff();
        polyBuff[i].filterEnv.noteOff();
        polyBuff[i].note = 0;
      }
    }
  }
}

void handleButtonPress(boolean *buttonsState)
{
  for (int i = 0; i < 4; i++)
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
        for (int i = 0; i < polyBuffSize; i++)
        {
          polyBuff[i].waveformA.begin(globalState.WAVEFORM1);
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
        for (int i = 0; i < polyBuffSize; i++)
        {
          polyBuff[i].waveformB.begin(globalState.WAVEFORM2);
        }
        break;

      case 2:
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
  case 0: // BALANCE
    globalState.OSC1_VOL = decKnobVal;
    globalState.OSC2_VOL = 1 - decKnobVal;
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].waveformMixer.gain(0, globalState.OSC1_VOL);
      polyBuff[i].waveformMixer.gain(1, globalState.OSC2_VOL);
    }
    break;
  case 1: // PWM
    globalState.PWM = 0.1 + 0.4 * (1 - decKnobVal);
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].waveformA.pulseWidth(globalState.PWM);
      polyBuff[i].waveformB.pulseWidth(globalState.PWM);
    }
    break;
  case 2:                           // ATTACK
    if (globalState.shift == false) // FOR AMP
    {
      globalState.AMP_ATTACK = 5000 * (1 - (float(knobValue) * DIV1023));
      if (globalState.AMP_ATTACK < 15) //
      {
        globalState.AMP_ATTACK = 0;
      }
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].ampEnv.attack(globalState.AMP_ATTACK);
      }
    }
    else // FOR FILTER
    {
      globalState.FILTER_ATTACK = 5000 * (1 - (float(knobValue) * DIV1023));
      if (globalState.FILTER_ATTACK < 15) //
      {
        globalState.FILTER_ATTACK = 0;
      }
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].filterEnv.attack(globalState.FILTER_ATTACK);
      }
    }
    break;
  case 3:                           // DECAY
    if (globalState.shift == false) // FOR AMP
    {
      globalState.AMP_DECAY = 11880 * (1 - (float(knobValue) * DIV1023));
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].ampEnv.decay(globalState.AMP_DECAY);
      }
    }
    else
    { // FOR FILTER
      globalState.FILTER_DECAY = 11880 * (1 - (float(knobValue) * DIV1023));
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].filterEnv.decay(globalState.FILTER_DECAY);
      }
    }
    break;
  case 4: // MASTER_VOL
    globalState.MASTER_VOL = 2 * (1 - decKnobVal);
    amp1.gain(globalState.MASTER_VOL);
    break;
  case 5: // DETUNE_FINE
    globalState.DETUNE_FINE = 1 - decKnobVal;
    break;
  case 6: // DETUNE_COARSE
    globalState.DETUNE_COARSE = pow(2, 2 * ((1 - decKnobVal) - 0.5));
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].waveformB.frequency(polyBuff[i].noteFreq * globalState.DETUNE_COARSE);
    }
    break;
  case 7: // AMP_SUSTAIN
    if (globalState.shift == false)
    {
      globalState.AMP_SUSTAIN = 1 - (float(knobValue) * DIV1023);
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].ampEnv.sustain(globalState.AMP_SUSTAIN);
      }
    }
    else
    {
      globalState.FILTER_SUSTAIN = 1 - (float(knobValue) * DIV1023);
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].filterEnv.sustain(globalState.FILTER_SUSTAIN);
      }
    }
    break;
  case 8: // AMP_RELEASE
    if (globalState.shift == false)
    {
      globalState.AMP_RELEASE = 11880 * (1 - (float(knobValue) * DIV1023));
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].ampEnv.release(globalState.AMP_RELEASE);
      }
    }
    else
    {
      globalState.FILTER_RELEASE = 11880 * (1 - (float(knobValue) * DIV1023));
      for (int i = 0; i < polyBuffSize; i++)
      {
        polyBuff[i].filterEnv.release(globalState.FILTER_RELEASE);
      }
    }
    break;
  case 9:
    break;
  case 10: // FILTER_FREQ
    globalState.FILTER_FREQ = 7000 * (1 - decKnobVal);
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].filter.frequency(globalState.FILTER_FREQ);
    }
    break;
  case 11: // FILTER_Q
    globalState.FILTER_Q = 4.3 * (1 - (float(knobValue) * DIV1023)) + 1.1;
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].filter.resonance(globalState.FILTER_Q);
    }
    break;
  case 12: // FILTER_DEPTH
    globalState.FILTER_OCTAVE = 7 * (1 - decKnobVal);
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].filter.octaveControl(globalState.FILTER_OCTAVE);
    }
    break;
  case 13:
    globalState.LFO_FREQ = 30 * (1 - decKnobVal);
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