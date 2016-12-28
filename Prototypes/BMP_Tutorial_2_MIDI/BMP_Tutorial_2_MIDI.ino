/*
  Barometric Pressure Sensor
  Author: Brendan Vavra

  This sketch shows how to convert BMP180 pressure readings to MIDI velocity.
  Based off the AccordionMega code and SparkFun's BMP library examples

  This sketch will play a MIDI note on and off.  While the note is on,
  blowing on the BMP should change the volume of the note.
*/
#include <SFE_BMP180.h>
#include <Wire.h>
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

MIDI_CREATE_DEFAULT_INSTANCE();

SFE_BMP180 pressure;

char status;
double Temp, Calib_Pressure, Pressure;
int Pressure_Delta;

void setup() {
  MIDI.begin(1);
  //Serial.begin(115200);//for my sanity, we may want to use the Mega to have two serial ports
  Serial.begin(9600);

  init_BMP();
}

//AccordionMega's variables:
//byte midi_volume_ctrl = 0xB0;//176
int pressure_low_limit=10;
int curr_velocity = 127;
int velocity = 127;
boolean velocity_active = false;

//Command  Meaning # parameters  param 1 param 2
//0x80  Note-off  2 key velocity
//0x90  Note-on 2 key veolcity
//0xA0  Aftertouch  2 key touch
//0xB0  Continuous controller 2 controller #  controller value
//0xC0  Patch change  2 instrument #  
//0xD0  Channel Pressure  1 pressure
//0xE0  Pitch bend  2 lsb (7 bits)  msb (7 bits)
//0xF0  (non-musical commands)      

void loop() {
  //TODO: 
    
  // - take the abs value of the difference between init and current pressure
  // - constrain the difference to 0-127
  // - print new value if changed
  // 
  // Also keep reading AccordionMega's code to make sure
  // there isn't anything else we need to do.
  // See if/how he handles changing velocity of sustained notes.
  Pressure = readPressure();
  Pressure_Delta = abs(Pressure - Calib_Pressure);
  Pressure_Delta = constrain(Pressure_Delta, pressure_low_limit, 127);
  //view the full list of CC messages here: 
  // http://nickfever.com/music/midi-cc-list
  //CC7 is Volume, but AccordionMega uses CC11, which is
  // "Expression: a percentage of volume (CC7)"
  //MIDI.sendControlChange(CC#,velocity,channel);
  
  //This is done in every loop of AccordionMega's code before reading sensors
//  pressure = bmp085_read_up();    
//  delta_pressure = abs(pressure - calibration_pressure);
//  delta_pressure = constrain(delta_pressure, pressure_low_limit, 127);
//  BV - CC 7: change volume to delta_pressure/pressure_step
//  noteOn(0xB0,0x07,delta_pressure/pressure_step);
  Serial.print("Expression Change: ");
  Serial.print(Pressure_Delta/31);
  Serial.print(", ");
  Serial.println(Pressure_Delta);
  //MIDI.sendControlChange(11,delta_pressure/pressure_step,1);
  //  setting up minimal pressure to start a sound
  if (Pressure_Delta == pressure_low_limit){
    // we have to get to send message controller to zero once it got to zero
    if (curr_velocity>1){
      //BV - CC 11: set expression to 0
      //noteOn(midi_volume_ctrl,0x0B,0);
      Serial.println("Zero crossed");
      // maybe setting curr_velocity to 1 will solve the button press -> move problem
      curr_velocity = 1;
    }
  }
  else { 
    velocity_active = true;
  }

  Serial.println(Pressure_Delta);
  Serial.println(pressure_low_limit);
  Serial.println(Pressure_Delta > pressure_low_limit);
  if(Pressure_Delta > pressure_low_limit){
    Serial.print("Calculating velocity: ");
    velocity = int((log(float(Pressure_Delta)/100.0)+4.8)/0.03814);
  }
  else {
    
    velocity = 0;
  }
  Serial.print("Velocity: ");
  Serial.println(velocity, DEC);
  if ((velocity_active) && (curr_velocity != velocity)) {
    //BV - CC 11: set expression to new velocity
    //noteOn(midi_volume_ctrl,0x0B,velocity);
    curr_velocity = velocity;
    velocity_active = false;
    Serial.print("Velocity Change: ");
    Serial.println(curr_velocity, DEC);
  }
  delay(1000);
}


