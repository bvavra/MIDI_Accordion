/*******************************************************************************
 MIDI Accordion
 https://github.com/bvavra/MIDI_Accordion
 Copyright � 2016-2017 Brendan Vavra
 based on projects by Dimon Yegorenkov 2011 and Jason Bugeja 2014
 *******************************************************************************
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
   
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/

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
  // but we're setting our baud rate higher so that the Serial<->MIDI software 
  // can properly decode and read outgoing MIDI data on the computer.
  static const long BaudRate = 115200;
};

//#define DEBUG//uncomment this line to print serial messages, comment to send MIDI data
//#define BLUETOOTH//uncomment this line to send MIDI data via bluetooth instead of USB
//#define BMP//uncomment this line to use the BMP180 to add dynamics via bellows
//#define JOYSTICK//uncomment this line to use a joystick as a pitch-bend controller

#ifdef BLUETOOTH
  MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial1, MIDI, MySettings);
#else
  MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);
#endif

char left_hand_pins[] = { 53, 52, 50 };
// array to store up/down status of left keys
int LeftKeysStatus[] = {  
  B0000000,
  B0000000,
  B0000000
};
//Note: Based on how the opto-interruptors are laid out,
//You will likely have to remap their pitch numbers (36-59)
//36-47 are the bass notes, 48-59 are the chord notes
const char left_notes_midi_numbers[][8] = {
  {38,39,40,41,50,51,52,53},//53
  {46,47,36,37,58,59,48,49},//52
  {42,43,44,45,54,55,56,57} //50
};

char right_hand_pins[] = { 23, 25, 27, 26, 24, 22 };
// array to store up/down status of right keys
int RightKeysStatus[] = {  
  B0000000,
  B0000000,
  B0000000,
  B0000000,
  B0000000,
  B0000000
};
//Note: Based on how the opto-interruptors are laid out,
//You will likely have to remap their pitch numbers (53-93)
const char right_notes_midi_numbers[][8] = {
  {65,64,62,60,59,57,55,53},//23
  {79,77,76,74,72,71,69,67},//25
  {70,68,66,63,61,58,56,54},//27
  {93,91,89,88,86,84,83,81},//26
  {90,87,85,82,80,78,75,73},//24
  {92,0,0,0,0,0,0,0}        //22
};

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
  #else
    MIDI.begin();
    //If we're sending MIDI over Serial1, open Serial for additional debugging
    #ifdef BLUETOOTH
      Serial.begin(9600);
    #endif
  #endif
  //Digital pins start turned off
  for (int i=0; i<sizeof(left_hand_pins);i++){ 
    pinMode(left_hand_pins[i],OUTPUT);
    digitalWrite(left_hand_pins[i], LOW);
  }
  for (int i=0; i<sizeof(right_hand_pins);i++){ 
    pinMode(right_hand_pins[i],OUTPUT);
    digitalWrite(right_hand_pins[i], LOW);
  }

  DDRL = B00000000;  // PortL (42-49) as input (for left hand)
  PORTL = B11111111; // turn on pullup resistors

  DDRC = B00000000;  // PortC (30-37) as input (for right hand)
  PORTC = B11111111; // turn on pullup resistors

  #ifdef BMP
    init_BMP();
  #endif

  #ifdef JOYSTICK
    init_joystick();
  #endif
}

//MIDI Control Change code for expression, which is a percentage of velocity
const int CC_Expression = 11;
int prev_expression = 127;
//The BMP_180 is very sensitive, so readings can vary wildly from sample to sample.
//We're getting around this by computing and sending the average of bmp_sample_rate samples.
//A smaller bmp_sample_rate is more granular, but allows more "noise" to come in.
//A larger bmp_sample_rate is less granular, but has a smoother contour.
//Setting bmp_sample_rate too large may also lose the amount of perceived expression
//and create a noticable delay between squeezing the bellows and hearing the volume change,
//resulting in choppy crescendos and decrescendos.
//Tweak this value as needed.
const int bmp_sample_rate = 5;
int expression_avg[bmp_sample_rate];
int e = 0;

int joystick_prev_val = 0;

void loop()
{
  #ifdef BMP
    //Read pressure from the BMP_180 and convert it to MIDI expression
    int expression = get_expression(prev_expression);
    
    //Ignore it if it didn't change
    if(expression != prev_expression) {
      expression_avg[e] = expression;
      //Only send MIDI CC every bmp_sample_rate times, 
      //but send the average of the last bmp_sample_rate deltas
      if (e == bmp_sample_rate - 1){
        expression = 0;
        for (int i=0; i<bmp_sample_rate; i++){
          expression += expression_avg[i];
        }
        expression = expression/bmp_sample_rate;
        
        #ifdef DEBUG
          Serial.print("Expression Change: ");
          Serial.println(expression);
        #else
          MIDI.sendControlChange(CC_Expression,expression,1);
          //Don't let bass overpower melody
          MIDI.sendControlChange(CC_Expression,constrain(expression-6,0,127),2);
          //Don't let chords overpower melody
          MIDI.sendControlChange(CC_Expression,constrain(expression-12,0,127),3);
        #endif
        prev_expression = expression;
        e = 0;
      }
      else {
        e = e + 1;
      }
    }
  #endif

  #ifdef JOYSTICK
    int pitch_bend_val = scan_joystick();
    if(pitch_bend_val != joystick_prev_val) {
      #ifdef DEBUG
        Serial.print("Pitch Bend Change: ");
        Serial.println(pitch_bend_val);
      #else
        //Comment and uncomment to select which channels you want pitch bend to affect.
        MIDI.sendPitchBend(pitch_bend_val, 1);
        //MIDI.sendPitchBend(pitch_bend_val, 2);
        //MIDI.sendPitchBend(pitch_bend_val, 3);
        joystick_prev_val = pitch_bend_val;
      #endif
    }
  #endif

  //Alternate between scanning the left and right hand pins 
  //to reduce necessary delay between reads
  for (int i=0; i<6;i++){ 
    scan_pin(right_hand_pins[i], i, RightKeysStatus[i], false);
    scan_pin(left_hand_pins[i%3], i%3, LeftKeysStatus[i%3], true);
  }
}

byte reg_values = 0;

//Read the analog port value for the given pin
//If something changed, trigger MIDI signal
void scan_pin(int pin, int index, byte PinStatus, bool left) {
  //TODO - I wonder if we can replace this with direct port write for even better performance?
  digitalWrite(pin, HIGH);
  //A slight delay is needed here or else we'll be reading the previous pin
  delayMicroseconds(300);//was able to cut this in half by alternating between left and right
  if (left) {
    reg_values = ~PINL;
  }
  else {
    reg_values = ~PINC;
  }
  digitalWrite(pin, LOW);

  //check if something changed
  if (reg_values != PinStatus){ 
    //if the byte value is greater, we're turning the note on; else, turning it off.
    if (reg_values > PinStatus){
      //using bit-wise OR to send modified bits only
      check_key(reg_values ^ PinStatus, index, true, left); 
    }
    else {
      check_key(reg_values ^ PinStatus, index, false, left);
    }
  }
}

//Check to see which bits have changed and send the appropriate midi message
//Instead of iterating the array from 0-7, use binary search to find the modified bits faster
void check_key(int reg, int group, boolean on, boolean left){
  // saving 4 iterations, dividing byte by 2
  if (reg & 0xF0) {
    for(int i=0; i<4; i++){
      if ((reg >> 4+i) & 1){
        note_midi(group, i+4, on, left);
      }
    }
  }
  else if (reg & 0x0F) { 
    for(int i=0; i<4; i++){
      if ((reg >> i) & 1){
        note_midi(group, i, on, left);
      }
    }
  }
}

void note_midi(int group, int position, boolean on, boolean left){
  int pitch;
  int channel = 1;
  int midi_vel = 127;

  if (left){
    if (on){
      LeftKeysStatus[group] |= (1 << position);  //setting bit value
    }
    else {
      LeftKeysStatus[group] &= ~(1 << position);  //setting bit value
    }
    pitch = left_notes_midi_numbers[group][position];
    if(pitch < 48) {
      midi_vel = 120;//Don't let bass overpower melody
      channel = 2;
    }
    else {
      midi_vel = 110;//Don't let chords overpower melody
      channel = 3;
    }
  }
  else{
    if(on) {
      RightKeysStatus[group] |= (1 << position);  //setting bit value
    }
    else {
      RightKeysStatus[group] &= ~(1 << position);  //setting bit value
    }
    pitch = right_notes_midi_numbers[group][position];
    channel = 1;
  }

  if (pitch){
    #ifdef DEBUG
      Serial.print("Note ");
      if(on){
        Serial.print("on: ");
      }
      else {
        Serial.print("off: ");
      }
      Serial.println(pitch);
    #else
      if(on) {
        MIDI.sendNoteOn(pitch, midi_vel, channel);
      }
      else {
        MIDI.sendNoteOff(pitch, midi_vel, channel);
      }
    #endif
  }

}
