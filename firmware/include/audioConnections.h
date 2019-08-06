// GUItool: begin automatically generated code
AudioSynthNoisePink      V2_N;          //xy=123,341
AudioSynthWaveform       V2_B;      //xy=124,293
AudioSynthWaveform       V2_A;      //xy=126,245
AudioSynthNoisePink      V1_N;          //xy=127,176
AudioSynthWaveform       V1_B;      //xy=131,137
AudioSynthWaveform       V1_A;      //xy=135,97
AudioMixer4              V1_MIX;         //xy=297,140
AudioMixer4              V2_MIX;         //xy=299,282
AudioEffectEnvelope      V1_ENV;      //xy=462,138
AudioEffectEnvelope      V2_ENV;      //xy=466,279
AudioMixer4              V12_MIX;         //xy=680,313
AudioFilterStateVariable filter1;        //xy=855,310
AudioOutputI2S           i2s1;           //xy=1220,295
AudioConnection          patchCord1(V2_N, 0, V2_MIX, 2);
AudioConnection          patchCord2(V2_B, 0, V2_MIX, 1);
AudioConnection          patchCord3(V2_A, 0, V2_MIX, 0);
AudioConnection          patchCord4(V1_N, 0, V1_MIX, 2);
AudioConnection          patchCord5(V1_B, 0, V1_MIX, 1);
AudioConnection          patchCord6(V1_A, 0, V1_MIX, 0);
AudioConnection          patchCord7(V1_MIX, V1_ENV);
AudioConnection          patchCord8(V2_MIX, V2_ENV);
AudioConnection          patchCord9(V1_ENV, 0, V12_MIX, 0);
AudioConnection          patchCord10(V2_ENV, 0, V12_MIX, 1);
AudioConnection          patchCord11(V12_MIX, 0, filter1, 0);
AudioConnection          patchCord12(filter1, 0, i2s1, 0);
AudioConnection          patchCord13(filter1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=799,656
// GUItool: end automatically generated code
