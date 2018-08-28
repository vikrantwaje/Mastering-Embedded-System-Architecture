# Mastering-Embedded-System-Architecture
Project 1

1. A robust bare metal software that was optimized for the ARM M0+ architecture.
2. A debug interface that allowed various modes of operation and provided regular updates on measurements made by the system.
3. Measurement of vortex frequency by use of the zero crossing algorithm which gave an accurate measurement of the frequency.
4. Implementation of flow calculation that took the vortex frequency of the flow and temperature of the liquid and gave an immediate measurement of flow, frequency, and temperature across the debug monitor.

Project 2
Signal analyzer using ARM cortex M4
Sep 2017 – Oct 2017

Project description- Designed a push button interface to glow LED on interrupt
- Generated PWM wave to control the audio speaker
- Implemented Real time characteristics by using mutex and thread based mechanism in mbed platform
-The four threads were as follows:
a) Displaying temperature value on LCD
b) Displaying counter value on LCD
c) Blinking the LED of FRDM kl25z board
d) Controlling the brightness of external LED using PWM principle. Implemented DFT based algorithm to calculate the frequency of incoming sinusoidal signal

Project 3
VoIP Gateway on ARM A8
Nov 2016 – Dec 2016

Project descriptionObjective:
This project was part of the coursework for ECEN 5003: Mastering Embedded Systems Architecture. The project aimed at the development of VoIP PBX gateway on the Sitara AM-3358. The following features were included:

1. Use of G711 open source library for encoding and decoding of audio
2. Evaluation of the following OSes for the application: Win CE 7, Debian 8.6 and Ubuntu

Assessment:
The evaluation of the ARM A8 processor on the Beaglebone Black revealed the following:

1. The processor was capable of easily operating all of the above-mentioned OSes and provided and sufficient computational ability. We arrived at the conclusion that the Ubuntu distribution provided by Asterisk was the best choice of OS for this application. It provided all necessary middleware that is required to run a VoIP PBX efficiency.
2. The G711 codec is an efficient codec for encoding and decoding audio files
