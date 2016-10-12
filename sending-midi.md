---
layout: page
title: Sending MIDI
subtitle: How to MIDI with Arduino
---

//This will be the tutorial for creating and sending midi data.  Include some info about the MIDI protocol, some info about Arduino, and detailed isntructions for using the tutorials (with link to the tutorial folder in the GitHub repo).


**Goal:** Have the Arduino send MIDI data to the computer.

**The Problem:** We need to make sure whatever data we send follows the MIDI protocol in order for the data to be interpreted properly.  We will use the [Arduino MIDI library](http://playground.arduino.cc/Main/MIDILibrary) to make it simple for us.

**You will need:**

- Arduino (Uno, Mega, etc)
- [MIDI Accordion's MIDI Tutorial](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/MIDI_Tutorial)
- [Arduino MIDI Library](http://playground.arduino.cc/Main/MIDILibrary)

## Solution

The [MIDI Tutorial on the Arduino website](https://www.arduino.cc/en/Tutorial/Midi) provides a brief overview of how MIDI data is structured, along with [some links](http://www.tigoe.net/pcomp/code/communication/midi/) to [more extensive information](http://hinton-instruments.co.uk/reference/midi/protocol/index.htm).  For the sake of this project I'll give you the [tl;dr](https://en.wikipedia.org/wiki/Wikipedia:Too_long;_didn%27t_read) for this project:

- There are two kinds of MIDI bytes: Data and Commands
- All MIDI data bytes (notes, volume, etc.) range between 0 and 127.
 - For notes, 60 is middle C on the piano, and each number below or above is the difference of one semitone.
 - For velocity, 0 is silence and 127 is the max volume.
- Command bytes range from 127 to 511 and are used to do things with the corresponding data bytes, like turning a note on or off, or setting the note velocity (i.e. volume).  The Arduino MIDI Library makes it easy to execute common MIDI commands because they're wrapped in functions such as sendNoteOn() and sendNoteOff().
- MIDI data is assigned to and sent on a designated channel.  MIDI supports up to 16 channels, each of which can be used to represent different instruments.  Channel 10 is reserved for drums.

Again, there's a lot more to it than this, but I'll dive into details in future sections when necessary.

**Steps**

1. Install the [Arduino MIDI Library](http://playground.arduino.cc/Main/MIDILibrary) to your Arduino IDE.
2. Download and open the [MIDI Tutorial](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/MIDI_Tutorial) for this project, and run it.  
 - Note: when viewing the Serial output window, be sure to set the [baud rate](https://www.arduino.cc/en/Serial/Begin) to the same baud rate set by the program (115200 bits/second).

**Troubleshooting**

//todo

**Credit**

//TODO thank the makers of arduino midi library
