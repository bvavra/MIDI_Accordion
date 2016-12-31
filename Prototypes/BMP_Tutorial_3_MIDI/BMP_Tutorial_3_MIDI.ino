/*
  Barometric Pressure Sensor
  Author: Brendan Vavra

  This sketch shows how to get BMP180 pressure readings asynchronously

  This sketch will play a MIDI note on and off.  While the note is on,
  blowing on the BMP should change the volume of the note.
*/

#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>
struct MySettings : public midi::DefaultSettings
{
  //By default, MIDI Library tries to be smart by excluding the CC byte if it doesn't change.
  //This is a problem when starting up Hairless MIDI after starting up the Arduino.
  //See https://github.com/projectgus/hairless-midiserial/issues/16 for details.
  static const bool UseRunningStatus = false;
  // Set MIDI baud rate. MIDI has a default baud rate of 31250,
  // but we're setting our baud rate higher in order to 
  // properly decode and read outgoing MIDI data on the computer.
  static const long BaudRate = 115200;
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);

void setup() {
  MIDI.begin();
  //Serial.begin(9600);

  init_BMP();
}

int prev_expression = 127;
int CC_Expression = 11;//Control Change code for expression

void loop() {

  int expression = get_expression(prev_expression);
  if(expression != prev_expression) {
    MIDI.sendControlChange(CC_Expression,expression,1);
    //Serial.print("New Expression Value: ");
    //Serial.println(expression, DEC);
    prev_expression = expression;
  }
  
  //TODO - do MIDI note stuff, but in the mean time just pretend we're doing midi note stuff
  delayMicroseconds(3600);//This is the approximate amount of time the final project spends reading sensors
}

