#include "VoiceManager.h"

VoiceManager::VoiceManager() : audioManager(),
                               globalState(),
                               polyVoices{
                                   SynthVoice(audioManager.V1_A, audioManager.V1_B, audioManager.V1_N, audioManager.V1_MIX, audioManager.V1_AMP, audioManager.V1_ENV, audioManager.V1_FILT_ENV, audioManager.V1_FILT, globalState),
                                   SynthVoice(audioManager.V2_A, audioManager.V2_B, audioManager.V2_N, audioManager.V2_MIX, audioManager.V2_AMP, audioManager.V2_ENV, audioManager.V2_FILT_ENV, audioManager.V2_FILT, globalState),
                                   SynthVoice(audioManager.V3_A, audioManager.V3_B, audioManager.V3_N, audioManager.V3_MIX, audioManager.V3_AMP, audioManager.V3_ENV, audioManager.V3_FILT_ENV, audioManager.V3_FILT, globalState),
                                   SynthVoice(audioManager.V4_A, audioManager.V4_B, audioManager.V4_N, audioManager.V4_MIX, audioManager.V4_AMP, audioManager.V4_ENV, audioManager.V4_FILT_ENV, audioManager.V4_FILT, globalState),
                                   SynthVoice(audioManager.V5_A, audioManager.V5_B, audioManager.V5_N, audioManager.V5_MIX, audioManager.V5_AMP, audioManager.V5_ENV, audioManager.V5_FILT_ENV, audioManager.V5_FILT, globalState),
                                   SynthVoice(audioManager.V6_A, audioManager.V6_B, audioManager.V6_N, audioManager.V6_MIX, audioManager.V6_AMP, audioManager.V6_ENV, audioManager.V6_FILT_ENV, audioManager.V6_FILT, globalState),
                                   SynthVoice(audioManager.V7_A, audioManager.V7_B, audioManager.V7_N, audioManager.V7_MIX, audioManager.V7_AMP, audioManager.V7_ENV, audioManager.V7_FILT_ENV, audioManager.V7_FILT, globalState),
                                   SynthVoice(audioManager.V8_A, audioManager.V8_B, audioManager.V8_N, audioManager.V8_MIX, audioManager.V8_AMP, audioManager.V8_ENV, audioManager.V8_FILT_ENV, audioManager.V8_FILT, globalState)}
{
  audioManager.init();
}