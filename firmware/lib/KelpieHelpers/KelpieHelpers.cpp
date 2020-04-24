#include "KelpieHelpers.h"

void activateVoice(byte index, byte noteIn, float frequency, float gain)
{
  voiceManager.polyVoices[index].triggerKeydown(noteIn, gain, frequency);
}

void deactivateVoice(byte index)
{
  voiceManager.polyVoices[index].ampEnv.noteOff();
  voiceManager.polyVoices[index].filterEnv.noteOff();
  voiceManager.polyVoices[index].note = -1;
}

void playNoteMono(byte playMode, byte note, float noteGain)
{
  voiceManager.globalState.PREV_NOTE = voiceManager.globalState.CURRENT_NOTE;
  voiceManager.globalState.CURRENT_NOTE = note;
  if (voiceManager.globalState.CURRENT_NOTE == voiceManager.globalState.PREV_NOTE)
  {
    voiceManager.globalState.PREV_NOTE = 0; // this is a quick fix
    voiceManager.globalState.CURRENT_NOTE = 0;
  }
  float baseNoteFreq = noteFreqs[note];
  AudioNoInterrupts();
  switch (playMode)
  {
  case PLAY_NOTE: // PLAYNOTE
    for (byte i = 0; i < numPolyVoices; i++)
    {
      activateVoice(i, note, baseNoteFreq, noteGain);
    }
    break;
  case UPDATE_NOTE: // UPDATE NOTE
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].note = note;
      voiceManager.polyVoices[i].noteFreq = baseNoteFreq;
      voiceManager.polyVoices[i].waveformA.frequency(baseNoteFreq); // *voiceManager.globalState.PITCH_BEND);
      voiceManager.polyVoices[i].waveformB.frequency(baseNoteFreq * voiceManager.globalState.PITCH_BEND * voiceManager.globalState.DETUNE);
    }
    break;
  case STOP_NOTE: // STOP NOTE
    for (byte i = 0; i < numPolyVoices; i++)
    {
      deactivateVoice(i);
    }
    break;
  }
  AudioInterrupts();
};

void bufferShift(byte indexToRemove, byte currentSizeOfBuffer)
{
  for (byte i = indexToRemove + 1; i < currentSizeOfBuffer; i++)
  {
    monoBuffer[i - 1] = monoBuffer[i];
  }
  monoBuffer[currentSizeOfBuffer - 1] = 0;
}

void keyBuffMono(byte note, float noteGain, boolean playNote)
{
  static byte currentNote = 0; // this might make more sense to start with -1 to keep indexing legible
  if (playNote)
  {
    if (currentNote == MONOBUFFERSIZE) // if we exceed buffer size, newest note goes on end, remove first note and SHIFT all notes down 1
    {
      bufferShift(0, currentNote);
      currentNote = MONOBUFFERSIZE - 1;
    }
    monoBuffer[currentNote] = note;
    playNoteMono(PLAY_NOTE, note, noteGain);
    currentNote++;
  }
  else // key is released
  {
    byte foundNoteIndex = MONOBUFFERSIZE; // default to index larger than buffer size
    for (byte i = 0; i <= (currentNote); i++)
    {

      if (note == monoBuffer[i])
      {
        foundNoteIndex = i;
        monoBuffer[i] = 0;
        // note has to be stopped
        bufferShift(foundNoteIndex, currentNote);
        currentNote--;
        if (currentNote == 0)
        {
          playNoteMono(STOP_NOTE, note, noteGain);
        }
        else
        {
          playNoteMono(UPDATE_NOTE, monoBuffer[currentNote - 1], noteGain); // this is causing issues with the RELEASE phase of the AMP ENV
        }
      }
    }
  }
}

void keyBuffPoly(byte note, float noteGain, boolean playNote)
{
  if (playNote) // on keypress
  {
    float baseNoteFreq = noteFreqs[note];
    for (byte i = 0; i < numPolyVoices; i++)
    {
      if (voiceManager.polyVoices[i].ampEnv.isActive() == false)
      {
        activateVoice(i, note, baseNoteFreq, noteGain);
        break;
      }
    }
  }
  else // key released
  {
    for (byte i = 0; i < numPolyVoices; i++)
    {
      if (voiceManager.polyVoices[i].note == note)
      {
        deactivateVoice(i);
      }
    }
  }
}

void handleButtonPress(Button button)
{

  switch (button.buttonName)
  {
  case OSC_1_BUTTON: // button 1 was pressed, toggle between waveforms
    if (button.buttonState == true)
    {
      voiceManager.globalState.WAVEFORM1 = WAVEFORM_PULSE;
    }
    else
    {
      voiceManager.globalState.WAVEFORM1 = WAVEFORM_SAWTOOTH;
    }
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].waveformA.begin(voiceManager.globalState.WAVEFORM1);
    }
    break;

  case OSC_2_BUTTON:
    if (button.buttonState == true)
    {
      voiceManager.globalState.WAVEFORM2 = WAVEFORM_PULSE;
    }
    else
    {
      voiceManager.globalState.WAVEFORM2 = WAVEFORM_SAWTOOTH;
    }
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].waveformB.begin(voiceManager.globalState.WAVEFORM2);
    }
    break;

  case POLY_MONO_BUTTON:
    // wipe out all notes playing just in case
    for (byte i = 0; i < numPolyVoices; i++)
    {
      deactivateVoice(i);
    }
    if (button.buttonState == true)
    {
      voiceManager.globalState.IS_POLY = true;
      voiceManager.globalState.POLY_GAIN_MULTIPLIER = POLY_MULTIPLIER;
    }
    else
    {
      voiceManager.globalState.IS_POLY = false;
      voiceManager.globalState.POLY_GAIN_MULTIPLIER = 1.0;
    }
    voiceManager.audioManager.MASTER_GAIN.gain(voiceManager.globalState.MASTER_VOL * voiceManager.globalState.POLY_GAIN_MULTIPLIER);
    break;

  case SHIFT_BUTTON:

    if (button.buttonState == true)
    {
      voiceManager.globalState.SHIFT = true;
    }
    else
    {
      voiceManager.globalState.SHIFT = false;
    }
    break;

  default:
    break;
  }
}

void handleKnobChange(Potentiometer knob)
{
  float decKnobVal = float(knob.setValue) * DIV1023;

  switch (knob.knobName)
  {
  case BALANCE_KNOB: // BALANCES OSC 1 and 2
    voiceManager.globalState.OSC1_VOL = decKnobVal;
    voiceManager.globalState.OSC2_VOL = 1 - decKnobVal;
    voiceManager.globalState.OSC_CONSTANT = calculateOscConstant(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL);
    setWaveformLevels(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL, voiceManager.globalState.OSC_CONSTANT);
    break;
  case PWM_KNOB: // PWM OF PULSE WAVES (ONLY APPLIES WHEN A PULSE WAVE IS ACTIVATED)
    voiceManager.globalState.PWM = 0.1 + 0.4 * (1 - decKnobVal);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].waveformA.pulseWidth(voiceManager.globalState.PWM);
      voiceManager.polyVoices[i].waveformB.pulseWidth(voiceManager.globalState.PWM);
    }
    break;
  case ATTACK_KNOB:                              // ATTACK
    if (voiceManager.globalState.SHIFT == false) // FOR AMP
    {
      voiceManager.globalState.AMP_ATTACK = AMP_ATTACK_MAX * (1 - (decKnobVal));
      if (voiceManager.globalState.AMP_ATTACK < 15) //
      {
        voiceManager.globalState.AMP_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.attack(voiceManager.globalState.AMP_ATTACK);
      }
    }
    else // FOR FILTER
    {
      voiceManager.globalState.FILTER_ATTACK = FILTER_ATTACK_MAX * (1 - (decKnobVal));
      if (voiceManager.globalState.FILTER_ATTACK < 15) //
      {
        voiceManager.globalState.FILTER_ATTACK = 0;
      }
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.attack(voiceManager.globalState.FILTER_ATTACK);
      }
    }
    break;
  case DECAY_KNOB:                               // DECAY
    if (voiceManager.globalState.SHIFT == false) // FOR AMP
    {
      voiceManager.globalState.AMP_DECAY = AMP_DECAY_MAX * (1 - (decKnobVal));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.decay(voiceManager.globalState.AMP_DECAY);
      }
    }
    else
    { // FOR FILTER
      voiceManager.globalState.FILTER_DECAY = FILTER_DECAY_MAX * (1 - (decKnobVal));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.decay(voiceManager.globalState.FILTER_DECAY);
      }
    }
    break;
  case VOL_KNOB: // MASTER_VOL
    voiceManager.globalState.MASTER_VOL = MAX_MASTER_GAIN * (1 - decKnobVal);
    voiceManager.audioManager.MASTER_GAIN.gain(voiceManager.globalState.MASTER_VOL * voiceManager.globalState.POLY_GAIN_MULTIPLIER);
    break;
  case NOISE_KNOB: // NOISE_PRESENSE
    voiceManager.globalState.NOISE_VOL = 1 - decKnobVal;
    voiceManager.globalState.OSC_CONSTANT = calculateOscConstant(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL);
    setWaveformLevels(voiceManager.globalState.OSC1_VOL, voiceManager.globalState.OSC2_VOL, voiceManager.globalState.NOISE_VOL, voiceManager.globalState.OSC_CONSTANT);
    break;
  case COARSE_KNOB: // DETUNE
    voiceManager.globalState.DETUNE = calculateDetuneValue(knob.setValue);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].waveformB.frequency(voiceManager.polyVoices[i].noteFreq * voiceManager.globalState.DETUNE * voiceManager.globalState.PITCH_BEND);
    }
    break;
  case SUSTAIN_KNOB: // AMP_SUSTAIN
    if (voiceManager.globalState.SHIFT == false)
    {
      voiceManager.globalState.AMP_SUSTAIN = 1 - (decKnobVal);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.sustain(voiceManager.globalState.AMP_SUSTAIN);
      }
    }
    else
    {
      voiceManager.globalState.FILTER_SUSTAIN = 1 - (decKnobVal);
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.sustain(voiceManager.globalState.FILTER_SUSTAIN);
      }
    }
    break;
  case RELEASE_KNOB: // AMP_RELEASE
    if (voiceManager.globalState.SHIFT == false)
    {
      voiceManager.globalState.AMP_RELEASE = AMP_RELEASE_MAX * (1 - (decKnobVal));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].ampEnv.release(voiceManager.globalState.AMP_RELEASE);
      }
    }
    else
    {
      voiceManager.globalState.FILTER_RELEASE = FILTER_RELEASE_MAX * (1 - (decKnobVal));
      for (byte i = 0; i < numPolyVoices; i++)
      {
        voiceManager.polyVoices[i].filterEnv.release(voiceManager.globalState.FILTER_RELEASE);
      }
    }
    break;
  case GLIDE_KNOB:
    break;
  case FREQ_KNOB: // FILTER_FREQ
    voiceManager.globalState.FILTER_FREQ = FILTER_CUTOFF_MAX * pow((1023 - knob.setValue) * DIV1023, 3);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].filter.frequency(voiceManager.globalState.FILTER_FREQ);
    }
    break;
  case Q_KNOB: // FILTER_Q
    voiceManager.globalState.FILTER_Q = FILTER_Q_MAX * (1 - (float(knob.setValue) * DIV1023)) + 1.1;
    voiceManager.globalState.PREFILTER_GAIN = 1 / voiceManager.globalState.FILTER_Q;
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].filter.resonance(voiceManager.globalState.FILTER_Q);
    }
    break;
  case DEPTH_KNOB: // FILTER_DEPTH
    voiceManager.globalState.FILTER_OCTAVE = FILTER_OCTAVE_DEPTH * (1 - decKnobVal);
    for (byte i = 0; i < numPolyVoices; i++)
    {
      voiceManager.polyVoices[i].filter.octaveControl(voiceManager.globalState.FILTER_OCTAVE);
    }
    break;
  case RATE_KNOB: // LFO RATE
    voiceManager.globalState.LFO_FREQ = LFO_FREQ_MAX * pow((1 - decKnobVal), 5);
    voiceManager.audioManager.LFO.frequency(voiceManager.globalState.LFO_FREQ);
    break;
  case FILTER_KNOB: // LFO SIGNAL TO FILTER
    voiceManager.globalState.LFO_FILTER_GAIN = (1 - decKnobVal);
    voiceManager.audioManager.LFO_MIXER_FILTER.gain(1, voiceManager.globalState.LFO_FILTER_GAIN);
    break;

  case AMP_KNOB: // LFO SIGNAL TO AMP
    voiceManager.globalState.LFO_AMP_GAIN = (1 - decKnobVal);
    voiceManager.audioManager.LFO_MIXER_AMP.gain(1, voiceManager.globalState.LFO_AMP_GAIN);
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
    voiceManager.polyVoices[i].waveformA.amplitude(osc1Vol * oscConstant);
    voiceManager.polyVoices[i].waveformB.amplitude(osc2Vol * oscConstant);
    voiceManager.polyVoices[i].noise.amplitude(noiseVol - (noiseVol * oscConstant));
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