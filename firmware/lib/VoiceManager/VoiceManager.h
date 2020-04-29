#ifndef Voice_Manager_h
#define Voice_Manager_h

#include <KelpieAudioManager.h>
#include <SynthState.h>
#include <SynthVoice.h>

const byte numVoices = 8;
class VoiceManager
{
public:
  VoiceManager();
  void initVoices();
  void initAudio();

  void setPWM(float);
  void setFilterQ(float);

  KelpieAudioManager audioManager;
  SynthState globalState;
  SynthVoice polyVoices[numVoices];
};

#endif