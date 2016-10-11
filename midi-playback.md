---
layout: page
title: MIDI Playback
subtitle: Turning bytes into notes
---

//This will be the tutorial for taking the midi data from the Arduino and turning it into computer-realized sound.  Include some more info about the MIDI protocol, some info about layout and diagram of how everything's connected, and detailed isntructions for putting everything together (with links to third-party software).

**Goal:** Have the Arduino send MIDI data to the PC and have the PC recognize the data as MIDI and play it back for us using software that supports MIDI Input and Output (e.g. Reason, Logic, etc).

**The Problem:** Arduino communicates with the PC over a Serial port, but we want to communicate using MIDI.  We need a way to convert the serial output into something the PC understands to be a MIDI port.  There are two ways to solve this problem:

# Create a MIDI port on the Arduino (see MIDI tutorial).
# Use Serial to MIDI conversion software to send Serial data coming from the Arduino to a virtual MIDI port.

I tried both solutions but was only able to get #2 to work, so that's the one I'll be elaborating on.

**You will need:**

- Arduino (Uno, Mega, etc)
- For Option 1 Only:
-- MIDI-USB cable
-- MIDI connector PIN
-- 2x220 Ohm resistors
-- Wires

## Solution #1

In theory, for solution #1 all you should need is to follow the [MIDI tutorial on the Arduino website](https://www.arduino.cc/en/Tutorial/Midi)  and you should be done - when you plug in the MIDI cable from the arduino's MIDI connector to the PC the PC should automatically recognize it as a MIDI port and receive MIDI data.  This didn't work for me and I'm not sure why - if I run into latency problems with my current setup I'll revisit this.

<insert music keyboard to pc diagram here>

**Going further:** [This guy demonstrates how to integrate the MIDI<->USB circuit in the cable into the Arduino.](http://shiftmore.blogspot.com/2010/01/quick-and-dirty-arduino-midi-over-usb.html)  In theory, one could build a plug-n-play MIDI device that would work on any computer using this method.  I personally haven't tried because I would prefer to get my accordion [communicating MIDI data wirelessly via bluetooth](bluetooth), which would not be able to send data in MIDI format.  I've looked into wireless MIDI "cables" and they can be pretty expensive. //TODO - insert link here.

## Solution #2

For solving the Serial to MIDI conversion on the PC side, we need two pieces of software: one to convert the serial output from the Arduino to MIDI, and a virtual MIDI port to connect the converted output to your MIDI playback software of choice.

<insert serial to midi conversion diagram here, along with a brief explanation of each component>

**Serial to MIDI conversion software**

Some Options:

- [Hairless MIDI <-> Serial Bridge](http://projectgus.github.io/hairless-midiserial/)
- [Serial - MIDI Converter](http://spikenzielabs.com/SpikenzieLabs/Serial_MIDI.html)

I decided to go with Hairless MIDI because it provides an easy way to debug MIDI messages, and the site has good documentation.

**Virtual MIDI port software**

Some Options:

- [LoopMIDI](http://www.tobias-erichsen.de/software/loopmidi.html)
- [LoopBe1](http://nerds.de/en/loopbe1.html)

I decided to go with LoopMIDI because I liked having the communication display (I felt LoopBeMIDI was too simplistic for me).

**Virtual MIDI Controller Software**

Any virtual MIDI controller will get the job done, so you can pick your favorite.  Logic (Mac) and Reason (Mac, Windows) are two popular options.  I'll be using Reason for my final project; it's overqualified for the job, but it offers a wide variety of high quality sounds with practically limitless configuration ability.

If you don't have a virtual MIDI controller program and don't want to shell out the money for a high-end MIDI sequencer, I recommend using [Virtual MIDI Piano Keyboard](https://sourceforge.net/projects/vmpk/) which is free, compatible with Windows/Mac/Linux, and comes with the FluidSynth MIDI OUT driver, which is vastly superior to Microsoft GS Wavetable Synth in both sound quality and response time.

**Steps**

Once all of the software is installed, perform the following steps to hook everything up:

# Upload your Circuit code to the Arduino (requires the Arduino MIDI Library).
# Start your Virtual MIDI port.
# Open your Serial-to-MIDI program:
 - Select your Arduino port as the Serial port
 - Select the virtual MIDI port you created in Step 2 as MIDI Out
  - At this point, if done correctly, you should see MIDI data going through. <insert image of hairless MIDI here>
# On your MIDI controller program, create a MIDI connection to the virtual MIDI port.  This step greatly depends on your program; here's how to do it in Reason and VMPK: <insert images of reason and vmpk here>

And that's it - if done correctly, any MIDI messages being sent from the Arduino should now be playing back on your computer.

**Troubleshooting**

- I can't upload code changes to the Arduino.
 - You can't update the Arduino code while the COM port is in use by the MIDI<->Serial bridge, so you have to turn it off (including debug messages) when uploading new code to the Arduino.
 - If you try uploading quickly after plugging it in, sometimes it fails to find the COM port.  More often than not unplugging and replugging the USB cable seems to do the trick.

**Credit**

<thank the makers of Hairless MIDI, LoopMIDI, and VMPK here>
