/*
  Barometric Pressure Sensor
  Author: Brendan Vavra

  This sketch shows how to convert BMP180 pressure readings to MIDI velocity.
  Based off the AccordionMega code and SparkFun's BMP library examples

  This sketch will play a MIDI note on and off.  While the note is on,
  blowing on the BMP should change the volume of the note.
*/

#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

MIDI_CREATE_DEFAULT_INSTANCE();

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
  //velocity_per_second();
  constant_velocity_change();

  //view the full list of CC messages here: 
  // http://nickfever.com/music/midi-cc-list
  //CC7 is Volume, but AccordionMega uses CC11, which is
  // "Expression: a percentage of volume (CC7)"
  //Ex. MIDI.sendControlChange(CC#,velocity,channel);
  
  //MIDI.sendControlChange(CC#,midi_velocity,1);
  //MIDI.sendControlChange(CC#,midi_velocity,2);
  //MIDI.sendControlChange(CC#,midi_velocity,3);
}

int prev_velocity = 127;
//Print velocity data whenever it changes
void constant_velocity_change(){
  
  int midi_velocity = velocity_bv();
  //int midi_velocity = velocity_dmitry();
  //int midi_velocity = velocity_jason();
  
  if(prev_velocity != midi_velocity){
    Serial.print("Velocity: ");
    Serial.println(midi_velocity, DEC);
    prev_velocity = midi_velocity;
  }
}

//Print velocity data every second
//Also includes timing data
void velocity_per_second(){
  initial_us = micros();

  int midi_velocity = velocity_bv();
  //int midi_velocity = velocity_dmitry();
  //int midi_velocity = velocity_jason();

  //Serial.println("=========================");
  Serial.print("Velocity: ");
  Serial.println(midi_velocity, DEC);

  final_us = micros();
  //Serial.print("Time to read pressure: ");
  //Serial.println(final_us-initial_us);//avg 12 ms per read
  
  delay(500);
}

//This is done in every loop of my code before reading sensors.
//Smoke test looks good so far, but I may end up tweaking this from time to time.
int velocity_bv(){
  //minimum amount of pressure change required to form a sound
  int pressure_low_limit = 10;//default=10
  //maximum amount of pressure change to register
  //Any change higher than this is reported as 127 velocity.
  //Increasing this number allows for more expression, but a quieter sounding accordion
  //Decreasing this number lets the accordion get louder with less air, but also less expression.
  int pressure_high_limit = 120;//default=120
  
  Pressure = readPressure();
  Pressure_Delta = Pressure - Calib_Pressure;
  //Serial.print("Pressure_Delta: ");
  //Serial.println(Pressure_Delta, DEC);
  Pressure_Delta = abs(Pressure_Delta);

  // setting up minimal pressure to start a sound
  if (Pressure_Delta <= pressure_low_limit){
    velocity = 0;
  }
  else { 
    //map() works if we want the correlation between pressure and velocity to be linear,
    //which may not be ideal.  I'll have to play a bit and see how this feels.
    //Both Dmitry and Jason use exponential functions, so I may end up switching to that.
    //Also, Jason applies different weights for pushing the bellows in or out,
    //so we may decide to something like that as well.
    velocity = map(Pressure_Delta, pressure_low_limit, pressure_high_limit, 0, 127);
  }

  return velocity;
}

//This is done in every loop of the AccordionMega code before reading sensors.
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
    //we assume the delta has been constrained between 10 and 127,
    //or else this function will not work.
    velocity = int((log(float(Pressure_Delta)/100.0)+4.8)/0.03814);
    velocity_active = true;
  }

  if ((velocity_active) && (curr_velocity != velocity)) {
    curr_velocity = velocity;
    velocity_active = false;
  }
  return curr_velocity;
}

//This is done in every loop of the AccordionMega_USB_Keyb code before reading sensors.
int velocity_jason() {
  Pressure = readPressure();
  //not sure where these numbers come from...
  //the final divisor differs between pulling the bellows out (45) and pushing them in (40)
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
