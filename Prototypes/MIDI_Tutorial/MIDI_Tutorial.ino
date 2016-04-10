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

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin(1);
  // Set MIDI baud rate. MIDI has a single baud rate of 31250,
  // but we're setting the serial baud rate higher to help reduce latency.
  Serial.begin(115200);
}

void loop() {
  int velocity = 127; //Max Velocity (range is 0-127)
  int channel = 1; //MIDI Channel 1 (out of 16)
  // Play notes from F3 (53) to A6 (93):
  for (int note = 53; note <= 93; note ++) {
    // Send a NoteOn message, wait a second, turn the note off
    MIDI.sendNoteOn(note, velocity, channel);  
    delay(1000);
    MIDI.sendNoteOff(note, velocity, channel);
  }
}
