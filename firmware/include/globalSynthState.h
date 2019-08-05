struct synthState
{
  int WAVEFORM1;
  int WAVEFORM2;
  float OSC1_VOL;
  float OSC2_VOL;
  float MASTER_VOL;
};

synthState globalState = {
    WAVEFORM_SAWTOOTH,// WAVEFORM1
    WAVEFORM_SAWTOOTH,  // WAVEFORM2
    0.0,             // OSC1_VOL
    0.0,             // OSC2_VOL
    0.5               // MASTER_VOL
    }; 