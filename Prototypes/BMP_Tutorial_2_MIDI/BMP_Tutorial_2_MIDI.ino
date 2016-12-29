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
//pressure variables
char status;
double Calib_Pressure, Pressure;
int Pressure_Delta;

//timing variables
unsigned long initial_us = 0; 
unsigned long final_us = 0;

void setup() {
  MIDI.begin(1);
  //Serial.begin(115200);//for my sanity, we may want to use the Mega to have two serial ports
  Serial.begin(9600);

  init_BMP();
}

int curr_velocity = 127;
int velocity = 127;
boolean velocity_active = false;

void loop() {
  //Serial.println("=========================");

  initial_us = micros();
  
  int midi_velocity = velocity_dmitry();
  //int midi_velocity = velocity_jason();

  Serial.print("Velocity: ");
  Serial.println(midi_velocity, DEC);
  
  //view the full list of CC messages here: 
  // http://nickfever.com/music/midi-cc-list
  //CC7 is Volume, but AccordionMega uses CC11, which is
  // "Expression: a percentage of volume (CC7)"
  //Ex. MIDI.sendControlChange(CC#,velocity,channel);
  
  //MIDI.sendControlChange(CC#,midi_velocity,1);
  //MIDI.sendControlChange(CC#,midi_velocity,2);
  //MIDI.sendControlChange(CC#,midi_velocity,3);

  final_us = micros();
  //Serial.print("Time to read pressure: ");
  //Serial.println(final_us-initial_us);//avg 12 ms per read
  
  delay(1000);
}

//This is done in every loop of the AccordionMega code before reading sensors
int velocity_dmitry(){
  int pressure_low_limit = 10;
  Pressure = readPressure();
  Pressure_Delta = constrain(abs(Pressure - Calib_Pressure), pressure_low_limit, 127);  
  
  // setting up minimal pressure to start a sound
  if (Pressure_Delta <= pressure_low_limit){
    // we have to get to send message controller to zero once it got to zero
    // maybe setting curr_velocity to 1 will solve the button press -> move problem
    curr_velocity = 1;
    velocity = 0;
  }
  else { 
    velocity = int((log(float(Pressure_Delta)/100.0)+4.8)/0.03814);
    velocity_active = true;
  }

  if ((velocity_active) && (curr_velocity != velocity)) {
    curr_velocity = velocity;
    velocity_active = false;
  }
  return curr_velocity;
}

//This is done in every loop of the AccordionMega_USB_Keyb code before reading sensors
int velocity_jason() {
  Pressure = readPressure();
  //calculate velocity from delta
  if (Pressure <= Calib_Pressure){ 
    Pressure_Delta = int(float((pow((Calib_Pressure - Pressure),1.4)+280)/45));   
  }
  else if (Pressure > Calib_Pressure){
    Pressure_Delta = int(float((pow((Pressure - Calib_Pressure),1.4)+280)/40));           
  } 
  if (Pressure_Delta > 127){
    Pressure_Delta = 127;
  } 

  // setting up minimal pressure to start a sound
  // setting controller to zero once it got to zero
  if (Pressure_Delta < 7){ 
    curr_velocity = 0; 
  }
  else if (Pressure_Delta >= 7) { 
    velocity = Pressure_Delta;
    curr_velocity = velocity;
  }
  return curr_velocity;
}
