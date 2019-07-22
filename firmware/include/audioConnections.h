// // GUItool: begin automatically generated code
AudioSynthNoiseWhite     NOISE;         //xy=113,247
AudioSynthWaveform       OSC2;      //xy=120,172
AudioSynthWaveform       OSC1;      //xy=121,116
AudioMixer4              MIXER;         //xy=281,185
AudioFilterStateVariable FILT;        //xy=451,205
AudioEffectEnvelope      FILT_ENV;      //xy=452,159
AudioAmplifier           AMP;           //xy=612,208
AudioEffectEnvelope      AMP_ENV;      //xy=615,167
AudioOutputI2S           i2s1;           //xy=804,193
AudioConnection          patchCord1(NOISE, 0, MIXER, 2);
AudioConnection          patchCord2(OSC2, 0, MIXER, 1);
AudioConnection          patchCord3(OSC1, 0, MIXER, 0);
AudioConnection          patchCord4(MIXER, FILT_ENV);
AudioConnection          patchCord5(FILT, 0, AMP_ENV, 0);
AudioConnection          patchCord6(FILT_ENV, 0, FILT, 1);
AudioConnection          patchCord7(AMP, 0, i2s1, 0);
AudioConnection          patchCord8(AMP, 0, i2s1, 1);
AudioConnection          patchCord9(AMP_ENV, AMP);
AudioControlSGTL5000     sgtl5000_1;     //xy=457,408
// // GUItool: end automatically generated code
