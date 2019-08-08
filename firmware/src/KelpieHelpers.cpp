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
        float noteFreq = noteFreqs[note];
        polyBuff[i].waveformA.frequency(noteFreq);
        polyBuff[i].waveformB.frequency(noteFreq);
        polyBuff[i].note = note;
        polyBuff[i].noteFreq = noteFreq;
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
          globalState.WAVEFORM1 = WAVEFORM_SQUARE;
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
          globalState.WAVEFORM2 = WAVEFORM_SQUARE;
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
  case 4: // MASTER_VOL
    globalState.MASTER_VOL = 2 * (1 - (float(knobValue) * DIV1023));
    amp1.gain(globalState.MASTER_VOL);
    break;
  case 5: // VOLUME 2
    // globalState.OSC2_VOL = 1 - (float(knobValue) * DIV1023);
    // // Serial.println(globalState.OSC2_VOL);
    // for (int i = 0; i < polyBuffSize; i++)
    // {
    //   polyBuff[i].waveformMixer.gain(1, globalState.OSC2_VOL);
    // }
    break;
  case 6: // DETUNE
    globalState.DETUNE = 1 - (0.05 * (1 - (float(knobValue) * DIV1023)));
    break;
  case 10: // FILTER_FREQ
    globalState.FILTER_FREQ = 10000 * (1 - (float(knobValue) * DIV1023));
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].filter.frequency(globalState.FILTER_FREQ);
    }
    break;

  case 11: // FILTER_Q
    globalState.FILTER_Q = 4.3 * (1 - (float(knobValue) * DIV1023)) + 0.7;
    for (int i = 0; i < polyBuffSize; i++)
    {
      polyBuff[i].filter.resonance(globalState.FILTER_Q);
    }
    break;
  case 12:                          // ATTACK
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
  case 13:                          // DECAY
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
  case 14: // AMP_SUSTAIN
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
  case 15: // AMP_RELEASE
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

  default:
    break;
  }
}