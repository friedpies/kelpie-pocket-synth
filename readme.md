## KELPIE - a polyphonic pocket synth

![kelpie](https://cdn.hackaday.io/images/3974921568747326146.jpg)
---
### About

The KELPIE is a digital polyphonic synthesizer powered by the SGTL5000 audio DAC and an ARM Cortex M4 microcontroller. For a description of the full project, please visit the [Hackaday Project Page](https://hackaday.io/project/166460-kelpie-synth-module-for-keyboard-controllers)

---
### Repository Details

This repo houses all mechanical, electrical, and software files relating to the project, as well as graphical assets and other additional files.

- Mechanical CAD (mCAD) files can be found and viewed [here](https://a360.co/2Hpqyr5) via Fusion 360's online viewer. They can be downloaded directly in whatever format you need (including STLs for 3D printing). The link provided here directly reflects the most current progress and is kept up-to-date in real time.
- Electronics CAD ([Autodesk Eagle](https://www.autodesk.com/products/eagle/free-download)) files and schematics can be found [here](https://github.com/friedpies/kelpie-pocket-synth/tree/master/hardware/electronics). The parts library and full BOM can be exported from the schematic. This is the most up-to-date BOM.
- Firmware files, written in Arduino/C++ using [PlatformIO](https://platformio.org/) can be found [here](https://github.com/friedpies/kelpie-pocket-synth/tree/master/firmware)


### Audio Design

The synthesizer block diagram is shown below and was designed using the [Teensy Audio Design Tool](https://www.pjrc.com/teensy/gui/index.html)

![BlockDiagram](https://github.com/friedpies/kelpie-pocket-synth/blob/master/graphics/OTHER%20ASSETS/Screen%20Shot%202019-08-23%20at%206.13.28%20PM.png?raw=true)

---

### About the Device / How to Use
![drawing](https://github.com/friedpies/kelpie-pocket-synth/blob/master/graphics/OTHER%20ASSETS/KELPIE_MASTER_DRAWING_TOP.png)

The KELPIE is a subtractive synthesizer that follows the standard 2 oscillator model. For those who have never used a subtractive synth before, there are plenty of resources online, I would recommend [this series of videos](https://www.youtube.com/watch?v=-1iK6drewCE) which do a great job of explaning and demonstrating the basics.

Some unique features of the KELPIE that are different and worth pointing out are:

 #### Oscillators
 - Each oscillator can only generate either a `pulse` waveform or `sawtooth` (both these waveforms are harmonically rich compared to triangle/sine waves, and can easily emulate other waves through filtering)
 - The `Pulse Width Modulation knob` (PWM) can only be heard if one (or both) of the waveforms are switched to a pulse waveform. This knob can be thought of as a "global" PWM
 - The `noise` knob is more of a noise "presence". At `0%`, oscillators 1 & 2 will dominate the output. Whereas at `100%`, the noise will completely dominate the output. At `50%` there will be an equal gain of Oscillators 1 & 2 and Noise.
 - `Coarse` refers to the relative tuning of Oscillator 2 to Oscillator 1. At `0%`, Oscillator 2 is tuned 1 octave below Oscillator 1, at `100%`, Oscillator 2 is tuned 1 octave above. Around `50%`, the knob is less sensitive in order to achieve less dramatic detuning.

#### Envelopes
  - The envelope knobs are responsible for both `amp` and `filter` envelopes. To switch between `amp` and `filter`, active the `shift` button. In future revisions, more features may be attached to the `shift` button.

#### Filter
  - Both filter `freq` and `Q` or (resonance) behave as expected in a traditional subtractive synthesizer. However, `depth` can be explained as the filter's impact or octave range. This effect is manifested in both the `LFO`'s `filter` parameter, as well as the `filter enevelope`'s effect on the overall sound.

#### LFO
  - The KELPIE has a single `LFO` or `low frequency oscillator` which is mapped to both the `filter`'s frequency as well as the overall `master gain`. The `rate` describes the frequency of oscillation, whereas the `filter` and `amp` parameters describe the `LFO`'s effect on those destinations.
  - Currently, the `LFO rate` is also mapped to the `modulation` MIDI CC message, so a player can easily adjust this parameter directly from their MIDI control interface.

#### GLIDE
  - This feature has not yet been implemented, but will allow the user to change the overall portamento rate (sliding between notes in `mono` mode)

#### MIDI CC
  - The KELPIE accepts `MIDI CC` messages from `102 - 119` which allow adjustment of all the parameters on the device. Both the built-in knobs and external MIDI knobs can be used simultaneously.

---

### Acknowledgements

I utilized and referenced a couple of open source libraries + repos for this project, as well as some very useful tools:

- PJRC Audio Library and Audio Design Tool
- [Bounce](https://github.com/thomasfredericks/Bounce2) library by Thomas Fredericks
- [MIDI](https://github.com/FortySevenEffects/arduino_midi_library) library by Francois Best
- thewknd's [Teensy Reference Boards schematics](https://github.com/thewknd/teensy-boards/tree/master/Teensy%203.2%20reference%20board%20clone)
- [Note's and Volts](https://www.notesandvolts.com/2018/05/teensy-synth-part-1.html) tutorial videos on building a Teensy synth
