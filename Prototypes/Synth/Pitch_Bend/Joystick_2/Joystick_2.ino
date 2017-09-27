/*
  Joystick Reader
  Author: Brendan Vavra

  This sketch shows how to use a joystick potentiometer to send MIDI control changes.
  If this circuit is connected to a MIDI synth, moving the joystick will create pitch bend.

  The circuit is as follows:
  - Joystick Pot Left to GND
  - Joystick Pot Right to 5V
  - Joystick Pot Middle to Analog
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

int potPin = 2;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor
int oldVal = 0;
int startVal = 0;
int mappedVal = 0;

int bendDirection = 1; //1 for bend up, -1 for bend down

void setup() {
  MIDI.begin();
  startVal = analogRead(potPin);
}

void loop() {
  // Play notes from F3 (53) to A6 (93):
  for (int note = 53; note <= 93; note ++) {
    // Send a NoteOn message, wait a second, turn the note off
    MIDI.sendNoteOn(note, velocity, channel);
    for(int i = 0; i < 1000; i++) {
      val = analogRead(potPin);    // read the value from the sensor

      //Arduino MIDI Libray takes pitchBend values from -8192 to 8191 
      //and converts them from 0 to 16383.
      //Since we're building a whammy bar (which can only move in one direction), 
      //we only care about mapping half of the values (from 0 up to 8191),
      //and we can invert the mapping to bend the pitch down (0 down to -8192).
      //How this value affects actual pitch bend depends on the playback software.
      //Most synths adjust the pitch by up to 2 semitones, 
      //but some may bend a full octave or more.
      mappedVal = map(val, startVal, 1023, 0, 8191 * bendDirection);
      //Ignore values that are too close to the starting value to prevent unwanted churn.
      if(mappedVal >= -50 && mappedVal <= 50){ 
        mappedVal = 0;
      } 
      if(mappedVal != oldVal) {
        MIDI.sendPitchBend(mappedVal, channel);
        oldVal = mappedVal;
      }
      delay(1);
    }
    MIDI.sendNoteOff(note, velocity, channel);
  }
  
}
