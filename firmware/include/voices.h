struct voice
{
  int note;
  int velocity;
  bool noteOnOff;
  AudioSynthWaveform &waveformA;
  AudioSynthWaveform &waveformB;
  AudioEffectEnvelope &ampEnv;
};

voice VOICE_1 = {0, 0, false, V1_A, V1_B, V1_ENV};
voice VOICE_2 = {0, 0, false, V2_A, V2_B, V2_ENV};