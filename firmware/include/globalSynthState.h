struct synthState
{
  int WAVEFORM1;
  int WAVEFORM2;
  float OSC1_VOL;
  float OSC2_VOL;
  float AMP_ATTACK;
  float AMP_DECAY;
  float AMP_SUSTAIN;
  float AMP_RELEASE;
  int FILTER_FREQ;
  float FILTER_Q;
  float MASTER_VOL;
};

synthState globalState = {
    WAVEFORM_SAWTOOTH,// WAVEFORM1
    WAVEFORM_SAWTOOTH,  // WAVEFORM2
    0.0,             // OSC1_VOL
    0.0,             // OSC2_VOL
    0.0,             // AMP_ATTACK
    0.0,            // AMP_DECAY
    1.0,            // AMP_SUSTAIN
    500,            //  AMP_RELEASE
    10000, // FILTER_FREQ
    0.7,  // FILTER_Q
    0.5               // MASTER_VOL
    }; 