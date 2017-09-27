/*
  MIDI note player
  Author: Brendan Vavra

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play
  the notes from F3 (53) to A6 (93) in sequence.

  This tutorial has been modified to use the Arduino MIDI library:
  http://playground.arduino.cc/Main/MIDILibrary
  Original code is in the public domain:
  http://www.arduino.cc/en/Tutorial/Midi

  If using a serial-to-MIDI converter, no circuit components are necessary.
  If sending MIDI over a MIDI cable, the circuit is as follows:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220-ohm resistor
  Attach a MIDI cable to the jack, then to a MIDI synth (or PC), and play music.
*/
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
struct MySettings : public midi::DefaultSettings
{
  //By default, the Arduino MIDI Library tries to be smart by 
  //excluding the CC byte if it doesn't change (to save bandwidth).
  //This is a problem when starting up Serial<->MIDI software
  //after starting up the Arduino because we miss the first CC byte.
  //Setting UseRunningStatus to false removes this "feature."
  //See https://github.com/projectgus/hairless-midiserial/issues/16 for details.
  static const bool UseRunningStatus = false;
  // Set MIDI baud rate. MIDI has a default baud rate of 31250,
  // but we're setting our baud rate higher in order to 
  // properly decode and read outgoing MIDI data on the computer.
  static const long BaudRate = 115200;
};

MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);

const int velocity = 127; //Max Velocity (range is 0-127)
const int channel = 1; //MIDI Channel 1 (out of 16)

void setup() {
  MIDI.begin();
}

void loop() {
  // Play notes from F3 (53) to A6 (93):
  for (int note = 53; note <= 93; note ++) {
    // Send a NoteOn message, wait a second, turn the note off
    MIDI.sendNoteOn(note, velocity, channel);  
    delay(1000);
    MIDI.sendNoteOff(note, velocity, channel);
  }
}
