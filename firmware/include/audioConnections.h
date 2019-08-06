// GUItool: begin automatically generated code
AudioSynthNoisePink      V2_N;          //xy=97,373
AudioSynthWaveform       V2_B;      //xy=98,325
AudioSynthWaveform       V2_A;      //xy=100,277
AudioSynthNoisePink      V1_N;          //xy=101,208
AudioSynthWaveform       V1_B;      //xy=105,169
AudioSynthWaveform       V1_A;      //xy=109,129
AudioMixer4              V1_MIX;         //xy=271,172
AudioMixer4              V2_MIX;         //xy=273,314
AudioMixer4              V12_MIX;         //xy=456,257
AudioFilterStateVariable filter1;        //xy=631,254
AudioEffectEnvelope      envelope1;      //xy=789,246
AudioOutputI2S           i2s1;           //xy=996,239
AudioConnection          patchCord1(V2_N, 0, V2_MIX, 2);
AudioConnection          patchCord2(V2_B, 0, V2_MIX, 1);
AudioConnection          patchCord3(V2_A, 0, V2_MIX, 0);
AudioConnection          patchCord4(V1_N, 0, V1_MIX, 2);
AudioConnection          patchCord5(V1_B, 0, V1_MIX, 1);
AudioConnection          patchCord6(V1_A, 0, V1_MIX, 0);
AudioConnection          patchCord7(V1_MIX, 0, V12_MIX, 0);
AudioConnection          patchCord8(V2_MIX, 0, V12_MIX, 1);
AudioConnection          patchCord9(V12_MIX, 0, filter1, 0);
AudioConnection          patchCord10(filter1, 0, envelope1, 0);
AudioConnection          patchCord11(envelope1, 0, i2s1, 0);
AudioConnection          patchCord12(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=799,656
// GUItool: end automatically generated code