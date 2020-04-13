### KELPIE SYNTHESIZER
By Kenneth Marut
www.kennethmarut.com

A custom hardware synthesizer based off of the Teensy 3.2 development hardware. This repository houses all firmware code, built using the Arduino language in PlatformIO.

## Getting Started with PlatformIO

This project uses VSCode with the PlatformIO extension instead of the Arduino IDE. To get set up, follow the instructions below:

- Download and install [VSCode](https://code.visualstudio.com/download) for your operating system
- Open VSCode and add the PlatformIO IDE Extension (platformio.platformio-ide)
- After PlatformIO finishes installing, restart VSCode
- Open PlatformIO by clicking on the "Alien" icon on VSCode's left toolbar
- Click on the "Platforms" icon, then search for the "Teensy" platform and install the latest version
- In the PIO Home window, select `Open Project` and navigate to `/kelpie-pocket-synth/firmware`
- Once the directory has been opened, click on the Alien PlatformIO icon on the left toolbar, and then select `Build` to compile the firmware
- Ensure the project has been successfully compiled, then connect your Kelpie/Teensy 3.2 via USB and select `Upload`
- After recompiling, the Teensy Loader should open and follow the familiar steps to flash the firmware to your device

The device firmware is written in C++ using the Arduino framework. The main entrypoint is `/src/main.cpp`. 
Custom libraries and classes can be found within the `/lib` directory. This is where most of the code lives.