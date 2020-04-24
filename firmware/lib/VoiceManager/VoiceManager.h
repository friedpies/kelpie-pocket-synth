#ifndef Voice_Manager_h
#define Voice_Manager_h

#include <KelpieAudioManager.h>
#include <SynthState.h>
class VoiceManager
{
public:
  VoiceManager();
  SynthState synthState;
  KelpieAudioManager audioManager;
};

#endif