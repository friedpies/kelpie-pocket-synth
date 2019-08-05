
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=94,252
AudioSynthWaveform       waveform1;      //xy=95,185
AudioSynthNoisePink      pink1;          //xy=121,321
AudioMixer4              mixer1;         //xy=277,260
AudioFilterStateVariable filter1;        //xy=451,258
AudioEffectEnvelope      envelope1;      //xy=678,260
AudioOutputI2S           i2s1;           //xy=840,263
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(pink1, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, 0, filter1, 0);
AudioConnection          patchCord5(filter1, 0, envelope1, 0);
AudioConnection          patchCord6(envelope1, 0, i2s1, 0);
AudioConnection          patchCord7(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=400,571
// GUItool: end automatically generated code
