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

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin();
  //Serial.begin(115200);//for my sanity, we may want to use the Mega to have two serial ports
  Serial.begin(9600);

  init_BMP();
}

int prev_expression = 127;
int CC_Expression = 11;//Control Change code for expression

void loop() {

  int expression = get_expression(prev_expression);
  if(expression != prev_expression) {
//    MIDI.sendControlChange(CC_Expression,expression,1);
    Serial.print("New Expression Value: ");
    Serial.println(expression, DEC);
    prev_expression = expression;
  }
  
  //TODO - do MIDI note stuff, but in the mean time just pretend we're doing midi note stuff
  delayMicroseconds(3600);

  //delay(500);
}

