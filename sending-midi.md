---
layout: page
title: Sending MIDI
subtitle: How to MIDI with Arduino
---

Before we even start thinking about making an accordion, let's get the Arduino set up to start making some music.  We'll be using the [MIDI Protocol](https://en.wikipedia.org/wiki/MIDI) to do this by sending data from the Arduino to the computer, where the MIDI data will be interpreted and realized as sound.  Let's solve the data transfer problem first, then we'll tackle turning that data into music in the next tuorial.

### Goal

Have the Arduino send MIDI data to the computer.

### The Problem 

We need to make sure whatever data we send follows the MIDI protocol in order for the data to be interpreted properly.  We will use the [Arduino MIDI library](http://playground.arduino.cc/Main/MIDILibrary) to make it simple for us.

**You will need:**
- Arduino (Uno, Mega, etc)
    - If you're reading this and ready to try this tutorial, I'm assuming that you have a vague idea of how to compile, upload, and run Arduino programs.  If not, I recommend picking up an [Arduino Getting Started Kit](https://www.amazon.com/s/ref=nb_sb_ss_c_1_18?url=search-alias%3Daps&field-keywords=arduino+getting+started+kit&sprefix=arduino+getting+st%2Caps%2C202), checking out the [Getting Started Guide](https://www.arduino.cc/en/Guide/HomePage), and building a few prototypes to get a feel for how the Arduino works before before jumping into this tutorial.
- [MIDI Accordion's MIDI Tutorial](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/MIDI_Tutorial)
- [Arduino MIDI Library](http://playground.arduino.cc/Main/MIDILibrary)

### Solution

The [MIDI Tutorial on the Arduino website](https://www.arduino.cc/en/Tutorial/Midi) provides a brief overview of how MIDI data is structured, along with [some links](http://www.tigoe.net/pcomp/code/communication/midi/) to [more extensive information](http://hinton-instruments.co.uk/reference/midi/protocol/index.htm).  For the sake of this project I'll give you the [tl;dr:](https://en.wikipedia.org/wiki/Wikipedia:Too_long;_didn%27t_read)

- There are two kinds of MIDI bytes: Data and Commands
- All MIDI data bytes (notes, velocity, etc.) range between 0 and 127.
    - For notes, 60 is middle C on the piano, and each number below or above is the difference of one semitone (e.g. 60 is C4, 61 is C#/Db4, 62 is D4, etc.).
    - For velocity (e.g. volume), 0 is silence and 127 is the max volume.
- Command bytes are used to do things with the corresponding data bytes, like turning a note on or off, or setting the note velocity.  The Arduino MIDI Library makes it easy to execute common MIDI commands because they're wrapped in functions such as sendNoteOn() and sendNoteOff(), so we won't go into any byte-specific details here (yet).
- MIDI data is assigned to and sent on a designated channel. MIDI supports up to 16 channels, each of which can be used to represent different instruments. Channel 10 is reserved for drums.

Again, there's a lot more to it than this, and I'll dive into details in future sections when necessary, but this is all you need to knnow for this tutorial.

### Steps


1. Install the [Arduino MIDI Library](http://playground.arduino.cc/Main/MIDILibrary) to your Arduino IDE.
    - See [Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries) for details on how to do this.
2. Download and open the [MIDI Tutorial](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/MIDI_Tutorial) for this project.
    
Before running the program, let's take a look and see what the code is doing.

In order for us to use the Arduino MIDI library, we have to include it at the top:

    #include <MIDI.h>
    #include <midi_Defs.h>
    #include <midi_Message.h>
    #include <midi_Namespace.h>
    #include <midi_Settings.h>
    
Now we're going to [override the MIDI default baud rate](http://arduinomidilib.fortyseveneffects.com/a00013.html), changing it from 31250 to 115200.  We need to do this in order to properly decode and read outgoing MIDI data on the computer:

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

    // Play notes from F3 (53) to A6 (93):
    void loop() {
      // For each note from 53 to 93, perform the following code for that note,
	  // incrementing note by 1 each time.
      for (int note = 53; note <= 93; note ++) {
        MIDI.sendNoteOn(note, velocity, channel);  // Turn the note on.
        delay(1000);                               // Wait 1000 milliseconds.
        MIDI.sendNoteOff(note, velocity, channel); // Turn the note off.
      }
    }
    
All the program is doing is playing one note at a time for 1 second each from F3 to A6, which is the [full range of the accordion right hand](https://en.wikipedia.org/wiki/Piano_accordion).  If you're not familiar with Arduino code and don't quite understand how this syntax works, [check out the reference for For loops](https://www.arduino.cc/en/Reference/For).

Now let's upload and run the program.  If you open the output window, you'll probably see something like this:

![midi_output_9600](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/gh-pages/img/midi_output_9600.JPG)

Not very informative - let's change the baud rate of the output window to match our MIDI baud rate of 115200:

![midi_output_115200](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/gh-pages/img/midi_output_115200.JPG)

Still not great, but you can kind of see things like numbers going up and such, so it sort of looks like it's doing what we expect (if you see something remotely like this, you're good).  To make sure, though, we really need to hear what the output sounds like, and [that's what the next tutorial is for](../midi-playback)!  Before moving on, though, feel free to modify the code to try playing different notes for different durations to get a better feel for how MIDI note data translates to music.

### Troubleshooting

> When I try to upload and run the program I get an error saying: 
> avrdude: ser_open(): can't open device "\\.\COM#"

- Make sure that the selected Board matches your Arduino board and the select Port matches the Port number created when you installed the Arduino.
- Sometimes, if you unplug the Arduino, make a code change, re-plug it in, and reupload the code, it might not recognize that it's plugged in immediately.  Try unplugging and replugging it in again and then re-upload the code.

> "The program won't compile!"

- This program was written to work with the Arduino Uno and the Arduino Mega.  If you're running this program on a different Arduino (such as the Arduino Due) you may need to alter the MIDI_CREATE_CUSTOM_INSTANCE function call accordingly.  See the [Arduino MIDI Library Documentation](http://arduinomidilib.fortyseveneffects.com/a00020.html#a95faae7d93fc1a603f99cc7ad92d72bf) for details.

### Credit

- Thank you to [FortySevenEffects](https://github.com/FortySevenEffects), maker of the [Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library), for building an awesome, comprehensive library for easily using MIDI with the Arduino.
