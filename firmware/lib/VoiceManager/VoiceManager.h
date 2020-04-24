#ifndef Voice_Manager_h
#define Voice_Manager_h

#include <KelpieAudioManager.h>
#include <SynthState.h>
#include <SynthVoice.h>
class VoiceManager
{
public:
  VoiceManager();
  KelpieAudioManager audioManager;
  SynthState globalState;
  SynthVoice polyVoices[8];
};

#endif