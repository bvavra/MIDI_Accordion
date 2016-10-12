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

The [MIDI Tutorial on the Arduino website](https://www.arduino.cc/en/Tutorial/Midi) provides a brief overview of how MIDI data is structured, along with [some links](http://www.tigoe.net/pcomp/code/communication/midi/) to [more extensive information](http://hinton-instruments.co.uk/reference/midi/protocol/index.htm).  For the sake of this project I'll give you the [tl;dr:](https://en.wikipedia.org/wiki/Wikipedia:Too_long;_didn%27t_read)

- There are two kinds of MIDI bytes: Data and Commands
- All MIDI data bytes (notes, volume, etc.) range between 0 and 127.
    - For notes, 60 is middle C on the piano, and each number below or above is the difference of one semitone (e.g. 60 is C4, 61 is C#/Db4, 62 is D4, etc.).
    - For velocity, 0 is silence and 127 is the max volume.
- Command bytes range from 127 to 511 and are used to do things with the corresponding data bytes, like turning a note on or off, or setting the note velocity (i.e. volume).  The Arduino MIDI Library makes it easy to execute common MIDI commands because they're wrapped in functions such as sendNoteOn() and sendNoteOff().
- MIDI data is assigned to and sent on a designated channel.  MIDI supports up to 16 channels, each of which can be used to represent different instruments.  Channel 10 is reserved for drums.

Again, there's a lot more to it than this, but I'll dive into details in future sections when necessary.

**Steps**

1. Install the [Arduino MIDI Library](http://playground.arduino.cc/Main/MIDILibrary) to your Arduino IDE.
    - See [Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries) for details.
2. Download and open the [MIDI Tutorial](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/MIDI_Tutorial) for this project.
    - Note: when viewing the Serial output window, be sure to set the [baud rate](https://www.arduino.cc/en/Serial/Begin) to the same baud rate set by the program (115200 bits/second).
    
Before running the program, let's take a look and see what the code is doing.

In order for us to use the Arduino MIDI library, we have to include it at the top:

    #include <MIDI.h>
    #include <midi_Defs.h>
    #include <midi_Message.h>
    #include <midi_Namespace.h>
    #include <midi_Settings.h>
    
Now we're going to [override the MIDI default baud rate](http://arduinomidilib.fortyseveneffects.com/a00013.html), changing it from 31250 to 115200.  We need to do this in order to properly decode and read outgoing MIDI data in Serial output windows on the computer:

    struct MySettings : public midi::DefaultSettings
    {
      static const long BaudRate = 115200;
    };
    MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);

Next we set up some global variables.  In this tutorial velocity and channel do not change, so I made them into constants (i.e. variables that are set once and can never be changed):

    const int velocity = 127; //Max Velocity (range is 0-127)
    const int channel = 1; //MIDI Channel 1 (out of 16)
    
The [setup](https://www.arduino.cc/en/Reference/Setup) function looks like this:

    void setup() {
      MIDI.begin();
    }
    
This is starting up the MIDI library to listen for MIDI In messages on the default Serial port.  Note that we're using this instead of Serial.begin() - in order for MIDI messages to be processed properly, they cannot contain non-MIDI data, so we can't use features like Serial.print() on the same serial port as MIDI data.

Now for the program we want to execute:

    void loop() {
      // Play notes from F3 (53) to A6 (93):
      for (int note = 53; note <= 93; note ++) {
        // Send a NoteOn message, wait a second, turn the note off
        MIDI.sendNoteOn(note, velocity, channel);  
        delay(1000);
        MIDI.sendNoteOff(note, velocity, channel);
      }
    }
    
All the program is doing is playing one note at a time for 1 second each from F3 to A6, which is the full range of the accordion right hand.

Now let's run the program:

**Troubleshooting**

//todo

**Credit**

//TODO thank the makers of arduino midi library
