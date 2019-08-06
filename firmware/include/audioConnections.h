// GUItool: begin automatically generated code
AudioSynthWaveform V9_A;          //xy=100.01040649414062,1268.454921722412
AudioSynthWaveform V9_B;          //xy=105.01042938232422,1305.4549283981323
AudioSynthNoisePink V9_N;         //xy=106.01042175292969,1346.1217594146729
AudioSynthWaveform V10_A;         //xy=108.01040649414062,1421.0104904174805
AudioSynthWaveform V10_B;         //xy=109.01040649414062,1459.0106010437012
AudioSynthNoisePink V10_N;        //xy=109.01040649414062,1504.121576309204
AudioSynthNoisePink V12_N;        //xy=108.0103988647461,1786.121618270874
AudioSynthWaveform V11_A;         //xy=109.01040649414062,1564.0104990005493
AudioSynthWaveform V11_B;         //xy=109.01040649414062,1599.2327499389648
AudioSynthNoisePink V8_N;         //xy=111,1196
AudioSynthWaveform V6_B;          //xy=113,872
AudioSynthWaveform V12_B;         //xy=110.0103988647461,1744.1216163635254
AudioSynthWaveform V6_A;          //xy=114,831
AudioSynthNoisePink V11_N;        //xy=111.01040267944336,1639.1215572357178
AudioSynthNoisePink V7_N;         //xy=114,1056
AudioSynthWaveform V8_B;          //xy=114,1153
AudioSynthNoisePink V6_N;         //xy=115,914
AudioSynthWaveform V7_A;          //xy=115,975
AudioSynthWaveform V12_A;         //xy=113.0103988647461,1705.2326984405518
AudioSynthWaveform V7_B;          //xy=116,1017
AudioSynthWaveform V8_A;          //xy=116,1111
AudioSynthWaveform V5_B;          //xy=119,730
AudioSynthWaveform V3_A;          //xy=121,402
AudioSynthWaveform V5_A;          //xy=121,690
AudioSynthNoisePink V2_N;         //xy=123,355
AudioSynthWaveform V3_B;          //xy=123,452
AudioSynthNoisePink V3_N;         //xy=123,496
AudioSynthWaveform V2_B;          //xy=124,307
AudioSynthNoisePink V1_N;         //xy=125,211
AudioSynthWaveform V4_A;          //xy=124,545
AudioSynthWaveform V4_B;          //xy=124,587
AudioSynthWaveform V2_A;          //xy=126,259
AudioSynthNoisePink V5_N;         //xy=124,774
AudioSynthWaveform V1_B;          //xy=129,172
AudioSynthNoisePink V4_N;         //xy=130,626
AudioSynthWaveform V1_A;          //xy=133,132
AudioMixer4 V8_MIX;               //xy=280,1153
AudioMixer4 V10_MIX;              //xy=281.01040267944336,1457.6772117614746
AudioMixer4 V5_MIX;               //xy=285,722
AudioMixer4 V7_MIX;               //xy=284,1010
AudioMixer4 V3_MIX;               //xy=287,420
AudioMixer4 V9_MIX;               //xy=284.0103988647461,1297.677095413208
AudioMixer4 V6_MIX;               //xy=286,859
AudioMixer4 V4_MIX;               //xy=290,559
AudioMixer4 V11_MIX;              //xy=287.0104064941406,1593.6771926879883
AudioMixer4 V1_MIX;               //xy=295,175
AudioMixer4 V2_MIX;               //xy=299,296
AudioMixer4 V12_MIX;              //xy=302.010404586792,1736.677225112915
AudioEffectEnvelope V3_ENV;       //xy=445,420
AudioEffectEnvelope V1_ENV;       //xy=449,182
AudioEffectEnvelope V2_ENV;       //xy=449,291
AudioEffectEnvelope V6_ENV;       //xy=452,862
AudioEffectEnvelope V4_ENV;       //xy=455,552
AudioEffectEnvelope V5_ENV;       //xy=455,715
AudioEffectEnvelope V7_ENV;       //xy=454,1013
AudioEffectEnvelope V9_ENV;       //xy=454.01040267944336,1291.6771230697632
AudioEffectEnvelope V8_ENV;       //xy=461,1150
AudioEffectEnvelope V10_ENV;      //xy=472.0104217529297,1459.6771326065063
AudioEffectEnvelope V11_ENV;      //xy=477.0104179382324,1581.67724609375
AudioEffectEnvelope V12_ENV;      //xy=479.0104789733887,1727.6771965026855
AudioMixer4 V14_MIX;              //xy=682.0000534057617,621.0000324249268
AudioMixer4 V912_MIX;             //xy=688.0105667114258,808.677167892456
AudioMixer4 V58_MIX;              //xy=691.0001068115234,714.0001068115234
AudioMixer4 ALL_VOICE_MIX;        //xy=942.0105743408203,707.8993339538574
AudioFilterStateVariable filter1; //xy=1162.0001335144043,710.0000228881836
AudioOutputI2S i2s1;              //xy=1348.999942779541,691.0000400543213
AudioConnection patchCord1(V9_A, 0, V9_MIX, 0);
AudioConnection patchCord2(V9_B, 0, V9_MIX, 1);
AudioConnection patchCord3(V9_N, 0, V9_MIX, 2);
AudioConnection patchCord4(V10_A, 0, V10_MIX, 0);
AudioConnection patchCord5(V10_B, 0, V10_MIX, 1);
AudioConnection patchCord6(V10_N, 0, V10_MIX, 2);
AudioConnection patchCord7(V12_N, 0, V12_MIX, 2);
AudioConnection patchCord8(V11_A, 0, V11_MIX, 0);
AudioConnection patchCord9(V11_B, 0, V11_MIX, 1);
AudioConnection patchCord10(V8_N, 0, V8_MIX, 2);
AudioConnection patchCord11(V6_B, 0, V6_MIX, 1);
AudioConnection patchCord12(V12_B, 0, V12_MIX, 1);
AudioConnection patchCord13(V6_A, 0, V6_MIX, 0);
AudioConnection patchCord14(V11_N, 0, V11_MIX, 2);
AudioConnection patchCord15(V7_N, 0, V7_MIX, 2);
AudioConnection patchCord16(V8_B, 0, V8_MIX, 1);
AudioConnection patchCord17(V6_N, 0, V6_MIX, 2);
AudioConnection patchCord18(V7_A, 0, V7_MIX, 0);
AudioConnection patchCord19(V12_A, 0, V12_MIX, 0);
AudioConnection patchCord20(V7_B, 0, V7_MIX, 1);
AudioConnection patchCord21(V8_A, 0, V8_MIX, 0);
AudioConnection patchCord22(V5_B, 0, V5_MIX, 1);
AudioConnection patchCord23(V3_A, 0, V3_MIX, 0);
AudioConnection patchCord24(V5_A, 0, V5_MIX, 0);
AudioConnection patchCord25(V2_N, 0, V2_MIX, 2);
AudioConnection patchCord26(V3_B, 0, V3_MIX, 1);
AudioConnection patchCord27(V3_N, 0, V3_MIX, 2);
AudioConnection patchCord28(V2_B, 0, V2_MIX, 1);
AudioConnection patchCord29(V1_N, 0, V1_MIX, 2);
AudioConnection patchCord30(V4_A, 0, V4_MIX, 0);
AudioConnection patchCord31(V4_B, 0, V4_MIX, 1);
AudioConnection patchCord32(V2_A, 0, V2_MIX, 0);
AudioConnection patchCord33(V5_N, 0, V5_MIX, 2);
AudioConnection patchCord34(V1_B, 0, V1_MIX, 1);
AudioConnection patchCord35(V4_N, 0, V4_MIX, 2);
AudioConnection patchCord36(V1_A, 0, V1_MIX, 0);
AudioConnection patchCord37(V8_MIX, V8_ENV);
AudioConnection patchCord38(V10_MIX, V10_ENV);
AudioConnection patchCord39(V5_MIX, V5_ENV);
AudioConnection patchCord40(V7_MIX, V7_ENV);
AudioConnection patchCord41(V3_MIX, V3_ENV);
AudioConnection patchCord42(V9_MIX, V9_ENV);
AudioConnection patchCord43(V6_MIX, V6_ENV);
AudioConnection patchCord44(V4_MIX, V4_ENV);
AudioConnection patchCord45(V11_MIX, V11_ENV);
AudioConnection patchCord46(V1_MIX, V1_ENV);
AudioConnection patchCord47(V2_MIX, V2_ENV);
AudioConnection patchCord48(V12_MIX, V12_ENV);
AudioConnection patchCord49(V3_ENV, 0, V14_MIX, 2);
AudioConnection patchCord50(V1_ENV, 0, V14_MIX, 0);
AudioConnection patchCord51(V2_ENV, 0, V14_MIX, 1);
AudioConnection patchCord52(V6_ENV, 0, V58_MIX, 1);
AudioConnection patchCord53(V4_ENV, 0, V14_MIX, 3);
AudioConnection patchCord54(V5_ENV, 0, V58_MIX, 0);
AudioConnection patchCord55(V7_ENV, 0, V58_MIX, 2);
AudioConnection patchCord56(V9_ENV, 0, V912_MIX, 0);
AudioConnection patchCord57(V8_ENV, 0, V58_MIX, 3);
AudioConnection patchCord58(V10_ENV, 0, V912_MIX, 1);
AudioConnection patchCord59(V11_ENV, 0, V912_MIX, 2);
AudioConnection patchCord60(V12_ENV, 0, V912_MIX, 3);
AudioConnection patchCord61(V14_MIX, 0, ALL_VOICE_MIX, 0);
AudioConnection patchCord62(V912_MIX, 0, ALL_VOICE_MIX, 2);
AudioConnection patchCord63(V58_MIX, 0, ALL_VOICE_MIX, 1);
AudioConnection patchCord64(ALL_VOICE_MIX, 0, filter1, 0);
AudioConnection patchCord65(filter1, 0, i2s1, 0);
AudioConnection patchCord66(filter1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1; //xy=988.0001068115234,353.99998474121094
// GUItool: end automatically generated code
