// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=187.7003173828125,214.62339973449707
AudioSynthWaveform       waveform1;      //xy=188.46954345703125,148.46953964233398
AudioSynthNoisePink      pink1;          //xy=194.62340927124023,277.7003650665283
AudioMixer4              mixer1;         //xy=370.7772407531738,213.85415840148926
AudioOutputI2S           i2s1;           //xy=565.392620380108,214.6233954796424
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(pink1, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=410.77723576472346,376.93108778733466
// GUItool: end automatically generated code
