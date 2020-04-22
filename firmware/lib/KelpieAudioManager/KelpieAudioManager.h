#ifndef Kelpie_Audio_Manager_h
#define Kelpie_Audio_Manager_h

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

class KelpieAudioManager
{
public:
  KelpieAudioManager();
  void init();

  // GUItool: begin automatically generated code
  AudioSynthNoiseWhite V8_N;        //xy=572.2395629882812,1611.3333129882812
  AudioSynthWaveform V6_B;          //xy=574.2395629882812,1287.3333129882812
  AudioSynthWaveform V6_A;          //xy=575.2395629882812,1246.3333129882812
  AudioSynthNoiseWhite V7_N;        //xy=575.2395629882812,1471.3333129882812
  AudioSynthWaveform V8_B;          //xy=575.2395629882812,1568.3333129882812
  AudioSynthNoiseWhite V6_N;        //xy=576.2395629882812,1329.3333129882812
  AudioSynthWaveform V7_A;          //xy=576.2395629882812,1390.3333129882812
  AudioSynthWaveform V7_B;          //xy=577.2395629882812,1432.3333129882812
  AudioSynthWaveform V8_A;          //xy=577.2395629882812,1526.3333129882812
  AudioSynthWaveform V5_B;          //xy=580.2395629882812,1145.3333129882812
  AudioSynthWaveform V3_A;          //xy=582.2395629882812,817.3333129882812
  AudioSynthWaveform V5_A;          //xy=582.2395629882812,1105.3333129882812
  AudioSynthNoiseWhite V2_N;        //xy=584.2395629882812,770.3333129882812
  AudioSynthWaveform V3_B;          //xy=584.2395629882812,867.3333129882812
  AudioSynthNoiseWhite V3_N;        //xy=584.2395629882812,911.3333129882812
  AudioSynthWaveform V2_B;          //xy=585.2395629882812,722.3333129882812
  AudioSynthNoiseWhite V1_N;        //xy=586.2395629882812,626.3333129882812
  AudioSynthWaveform V4_A;          //xy=585.2395629882812,960.3333129882812
  AudioSynthWaveform V4_B;          //xy=585.2395629882812,1002.3333129882812
  AudioSynthWaveform V2_A;          //xy=587.2395629882812,674.3333129882812
  AudioSynthNoiseWhite V5_N;        //xy=585.2395629882812,1189.3333129882812
  AudioSynthWaveform V1_B;          //xy=590.2395629882812,587.3333129882812
  AudioSynthNoiseWhite V4_N;        //xy=591.2395629882812,1041.3333129882812
  AudioSynthWaveform V1_A;          //xy=594.2395629882812,547.3333129882812
  AudioSynthWaveformDc DC_OFFSET;   //xy=678.2395629882812,482.33331298828125
  AudioMixer4 V3_MIX;               //xy=739.2395629882812,850.3333129882812
  AudioMixer4 V8_MIX;               //xy=741.2395629882812,1568.3333129882812
  AudioMixer4 V5_MIX;               //xy=746.2395629882812,1137.3333129882812
  AudioMixer4 V7_MIX;               //xy=745.2395629882812,1425.3333129882812
  AudioMixer4 V6_MIX;               //xy=747.2395629882812,1274.3333129882812
  AudioMixer4 V4_MIX;               //xy=751.2395629882812,974.3333129882812
  AudioMixer4 V1_MIX;               //xy=756.2395629882812,590.3333129882812
  AudioMixer4 V2_MIX;               //xy=760.2395629882812,711.3333129882812
  AudioSynthWaveformSine LFO;       //xy=816.2395629882812,418.33331298828125
  AudioEffectEnvelope V7_FILT_ENV;  //xy=890.2395629882812,1395.3333129882812
  AudioEffectEnvelope V6_FILT_ENV;  //xy=896.2395629882812,1253.3333129882812
  AudioEffectEnvelope V8_FILT_ENV;  //xy=896.2395629882812,1546.3333129882812
  AudioAmplifier V8_AMP;            //xy=897.2395629882812,1594.3333129882812
  AudioAmplifier V5_AMP;            //xy=905.2395629882812,1149.3333129882812
  AudioAmplifier V7_AMP;            //xy=904.2395629882812,1432.3333129882812
  AudioEffectEnvelope V3_FILT_ENV;  //xy=909.2395629882812,833.3333129882812
  AudioEffectEnvelope V5_FILT_ENV;  //xy=910.2395629882812,1104.3333129882812
  AudioAmplifier V6_AMP;            //xy=911.2395629882812,1293.3333129882812
  AudioMixer4 LFO_MIXER_FILTER;     //xy=916.2395629882812,506.33331298828125
  AudioAmplifier V2_AMP;            //xy=916.2395629882812,755.3333129882812
  AudioAmplifier V4_AMP;            //xy=916.2395629882812,1006.3333129882812
  AudioEffectEnvelope V4_FILT_ENV;  //xy=917.2395629882812,965.3333129882812
  AudioAmplifier V3_AMP;            //xy=919.2395629882812,880.3333129882812
  AudioAmplifier V1_AMP;            //xy=928.2395629882812,583.3333129882812
  AudioEffectEnvelope V2_FILT_ENV;  //xy=932.2395629882812,697.3333129882812
  AudioEffectEnvelope V1_FILT_ENV;  //xy=935.2395629882812,639.3333129882812
  AudioEffectMultiply MULT_7;       //xy=1064.2395629882812,1405.3333129882812
  AudioEffectMultiply MULT_8;       //xy=1066.2395629882812,1544.3333129882812
  AudioEffectMultiply MULT_3;       //xy=1082.2395629882812,827.3333129882812
  AudioEffectMultiply MULT_6;       //xy=1083.2395629882812,1253.3333129882812
  AudioEffectMultiply MULT_5;       //xy=1089.2395629882812,1121.3333129882812
  AudioEffectMultiply MULT_1;       //xy=1093.2395629882812,578.3333129882812
  AudioEffectMultiply MULT_4;       //xy=1093.2395629882812,954.3333129882812
  AudioEffectMultiply MULT_2;       //xy=1099.2395629882812,696.3333129882812
  AudioFilterStateVariable V7_FILT; //xy=1221.2395629882812,1441.3333129882812
  AudioFilterStateVariable V3_FILT; //xy=1224.2395629882812,867.3333129882812
  AudioFilterStateVariable V2_FILT; //xy=1226.2395629882812,753.3333129882812
  AudioFilterStateVariable V6_FILT; //xy=1225.2395629882812,1292.3333129882812
  AudioFilterStateVariable V8_FILT; //xy=1225.2395629882812,1577.3333129882812
  AudioFilterStateVariable V1_FILT; //xy=1248.2395629882812,641.3333129882812
  AudioFilterStateVariable V4_FILT; //xy=1247.2395629882812,986.3333129882812
  AudioFilterStateVariable V5_FILT; //xy=1249.2395629882812,1140.3333129882812
  AudioEffectEnvelope V1_ENV;       //xy=1411.2395629882812,657.3333129882812
  AudioEffectEnvelope V2_ENV;       //xy=1418.2395629882812,744.3333129882812
  AudioEffectEnvelope V6_ENV;       //xy=1427.2395629882812,1236.3333129882812
  AudioEffectEnvelope V7_ENV;       //xy=1430.2395629882812,1299.3333129882812
  AudioEffectEnvelope V3_ENV;       //xy=1433.2395629882812,868.3333129882812
  AudioEffectEnvelope V5_ENV;       //xy=1441.2395629882812,1149.3333129882812
  AudioEffectEnvelope V4_ENV;       //xy=1445.2395629882812,993.3333129882812
  AudioEffectEnvelope V8_ENV;       //xy=1446.2395629882812,1441.3333129882812
  AudioMixer4 V14_MIX;              //xy=1743.2395629882812,1006.3333129882812
  AudioMixer4 V58_MIX;              //xy=1744.2395629882812,1076.3333129882812
  AudioMixer4 ALL_VOICE_MIX;        //xy=1923.2395629882812,1048.3333129882812
  AudioMixer4 LFO_MIXER_AMP;        //xy=2116.239570617676,886.0000190734863
  AudioEffectMultiply LFO_AMP;      //xy=2120.2395629882812,1037.3333129882812
  AudioAmplifier MASTER_GAIN;       //xy=2230.239875793457,1134.9999160766602
  AudioOutputI2S i2s1;              //xy=2364.2395629882812,1055.3333129882812
  AudioAnalyzePeak PEAK;            //xy=2412.239814758301,1240.5729970932007
  AudioConnection patchCord1;
  AudioConnection patchCord2;
  AudioConnection patchCord3;
  AudioConnection patchCord4;
  AudioConnection patchCord5;
  AudioConnection patchCord6;
  AudioConnection patchCord7;
  AudioConnection patchCord8;
  AudioConnection patchCord9;
  AudioConnection patchCord10;
  AudioConnection patchCord11;
  AudioConnection patchCord12;
  AudioConnection patchCord13;
  AudioConnection patchCord14;
  AudioConnection patchCord15;
  AudioConnection patchCord16;
  AudioConnection patchCord17;
  AudioConnection patchCord18;
  AudioConnection patchCord19;
  AudioConnection patchCord20;
  AudioConnection patchCord21;
  AudioConnection patchCord22;
  AudioConnection patchCord23;
  AudioConnection patchCord24;
  AudioConnection patchCord25;
  AudioConnection patchCord26;
  AudioConnection patchCord27;
  AudioConnection patchCord28;
  AudioConnection patchCord29;
  AudioConnection patchCord30;
  AudioConnection patchCord31;
  AudioConnection patchCord32;
  AudioConnection patchCord33;
  AudioConnection patchCord34;
  AudioConnection patchCord35;
  AudioConnection patchCord36;
  AudioConnection patchCord37;
  AudioConnection patchCord38;
  AudioConnection patchCord39;
  AudioConnection patchCord40;
  AudioConnection patchCord41;
  AudioConnection patchCord42;
  AudioConnection patchCord43;
  AudioConnection patchCord44;
  AudioConnection patchCord45;
  AudioConnection patchCord46;
  AudioConnection patchCord47;
  AudioConnection patchCord48;
  AudioConnection patchCord49;
  AudioConnection patchCord50;
  AudioConnection patchCord51;
  AudioConnection patchCord52;
  AudioConnection patchCord53;
  AudioConnection patchCord54;
  AudioConnection patchCord55;
  AudioConnection patchCord56;
  AudioConnection patchCord57;
  AudioConnection patchCord58;
  AudioConnection patchCord59;
  AudioConnection patchCord60;
  AudioConnection patchCord61;
  AudioConnection patchCord62;
  AudioConnection patchCord63;
  AudioConnection patchCord64;
  AudioConnection patchCord65;
  AudioConnection patchCord66;
  AudioConnection patchCord67;
  AudioConnection patchCord68;
  AudioConnection patchCord69;
  AudioConnection patchCord70;
  AudioConnection patchCord71;
  AudioConnection patchCord72;
  AudioConnection patchCord73;
  AudioConnection patchCord74;
  AudioConnection patchCord75;
  AudioConnection patchCord76;
  AudioConnection patchCord77;
  AudioConnection patchCord78;
  AudioConnection patchCord79;
  AudioConnection patchCord80;
  AudioConnection patchCord81;
  AudioConnection patchCord82;
  AudioConnection patchCord83;
  AudioConnection patchCord84;
  AudioConnection patchCord85;
  AudioConnection patchCord86;
  AudioConnection patchCord87;
  AudioConnection patchCord88;
  AudioConnection patchCord89;
  AudioConnection patchCord90;
  AudioConnection patchCord91;
  AudioConnection patchCord92;
  AudioConnection patchCord93;
  AudioConnection patchCord94;
  AudioConnection patchCord95;
  AudioConnection patchCord96;
  AudioConnection patchCord97;
  AudioConnection patchCord98;
  AudioConnection patchCord99;
  AudioConnection patchCord100;
  AudioControlSGTL5000 sgtl5000_1; //xy=1841.2395629882812,1263.3333129882812
  // GUItool: end automatically generated code
};

#endif