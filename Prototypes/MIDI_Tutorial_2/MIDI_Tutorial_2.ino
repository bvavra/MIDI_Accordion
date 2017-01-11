/*
  MIDI note player with dynamics
  Author: Brendan Vavra

  This is a temp sketch to see how we can use the Arduino MIDI library to change the volume of a note over time
*/
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int velocity = 127; //Max Velocity (range is 0-127)
int channel = 1; //MIDI Channel 1 (out of 16)
int CC_Volume = 7;//Control Change code for volume

void setup() {
  MIDI.begin(1);
  // Set MIDI baud rate. MIDI has a single baud rate of 31250,
  // but we're setting the serial baud rate higher to help reduce latency.
  Serial.begin(115200);
  MIDI.sendControlChange(CC_Volume,1,channel); 
}

void loop() {
  // Play notes from F3 (53) to A6 (93):
  for (int note = 53; note <= 93; note ++) {
    // Send a NoteOn message, wait a second, turn the note off
    MIDI.sendNoteOn(note, velocity, channel);  
    delay(500);
    for(int i=0; i<128; i++)
    {
      MIDI.sendControlChange(CC_Volume,i,channel); 
      delay(10);
    }
    delay(1000);
    for(int i=127; i>=0; i--)
    {
      MIDI.sendControlChange(CC_Volume,i,channel); 
      delay(10);
    }
    MIDI.sendNoteOff(note, velocity, channel);
    delay(500);
  }
}


  //view the full list of CC messages here: 
  // http://nickfever.com/music/midi-cc-list
  //7 is Volume, but AccordionMega also uses 11, which is
  // "Expression: a percentage of volume (CC7)"
  //MIDI.sendControlChange(7,velocity,channel);
  
  //This is done in every loop of AccordionMega's code before reading sensors
//  pressure = bmp085_read_up();    
//  delta_pressure = abs(pressure - calibration_pressure);
//  delta_pressure = constrain(delta_pressure, pressure_low_limit, 127);
//  BV - CC 7: change volume to delta_pressure/pressure_step
//  noteOn(0xB0,0x07,delta_pressure/pressure_step);    
//  setting up minimal pressure to start a sound
//  if (delta_pressure = pressure_low_limit){
//    // we have to get to send message controller to zero once it got to zero
//    if (curr_velocity>1){
//      BV - CC 11: set expression to 0
//      noteOn(midi_volume_ctrl,0x0B,0);
//      Serial.println("Zero crossed");
//      // maybe setting curr_velocity to 1 will solve the button press -> move problem
//      curr_velocity = 1;
//    }
//  }
//  else { 
//    velocity_active = true;
//  }
//  
//  if(delta_pressure > pressure_low_limit){
//    velocity = int((log(float(delta_pressure)/100.0)+4.8)/0.03814) ;
//  }
//  else {
//    velocity = 0;
//  }
//  //Serial.print("vel ");
//  //Serial.print(velocity, DEC);
//  if ((velocity_active) && (curr_velocity != velocity)) {
//    BV - CC 11: set expression to new velocity
//    noteOn(midi_volume_ctrl,0x0B,velocity);
//    curr_velocity = velocity;
//    velocity_active = false;
//    //Serial.print("Velocity ");
//    //Serial.println(curr_velocity, DEC);
//  }



//0xB0        - CC change command (0xB0 - 0xBF (176-192) depending on the MIDI channel)
//0x07        - Volume command
//the value   - The value of the volume, between 0 and 127

//void MidiVolume(byte channel, byte volume)
//{
//#ifdef DEBUG
//    Serial.println(volume, DEC);
//#else
//    Serial.print(0xB0 | (channel & 0x0F), BYTE);    // Control change command
//    Serial.print(0x07, BYTE);                       // Volume command
//    Serial.print(volume & 0x7F, BYTE);              // Volume 0-127
//#endif
//}

//Serial1.write(176);            // Control change (channel1)
//    Serial1.write(1);               // Volume command
//    Serial1.write(newModVal);  // Volume 0-127
//cc = 7?
//MIDI.sendControlChange(cc,127,1); 
