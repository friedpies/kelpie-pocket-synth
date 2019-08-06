struct voice
{
  int note;
  int velocity;
  bool noteOnOff;
  AudioSynthWaveform &waveformA;
  AudioSynthWaveform &waveformB;
  AudioSynthNoisePink &noise;
  AudioMixer4 &waveformMixer;
  AudioEffectEnvelope &ampEnv;
};

voice VOICE_1 = {0, 0, false, V1_A, V1_B, V1_N, V1_MIX, V1_ENV};
voice VOICE_2 = {0, 0, false, V2_A, V2_B, V2_N, V2_MIX, V2_ENV};