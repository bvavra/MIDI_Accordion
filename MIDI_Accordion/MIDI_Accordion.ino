/* 
* MIDI Accordion
* Author: Brendan Vavra 
* Thanks to Dimon Yegorenkov for the original code of which much of this project is based.
*/
#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int CC_Volume = 7;//Control Change code for volume

//#define DEBUG//uncomment this line to print serial messages, comment to send MIDI data

char left_hand_pins[] = { 10, 11, 12 };
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
  {57,56,55,54,41,40,39,38},
  {49,48,59,58,37,36,47,46},
  {53,52,51,50,45,44,43,42}
};

char right_hand_pins[] = { 2, 3, 4, 5, 6, 7 };
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
  {60,59,58,57,56,55,54,53},
  {68,67,66,65,64,63,62,61},
  {76,75,74,73,72,71,70,69},
  {84,83,82,81,80,79,78,77},
  {92,91,90,89,88,87,86,85},
  {0,0,0,0,0,0,0,93}
};

void setup()
{
  #ifdef DEBUG
    //Set serial baud rate:
    Serial.begin(9600);
  #else
    MIDI.begin(1);
    //Set MIDI baud rate:
    Serial.begin(115200);
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

  DDRF = B00000000;  // PortF as input (for left hand)
  PORTF = B11111111; // turn on pullup resistors

  DDRK = B00000000;  // PortK as input (for right hand)
  PORTK = B11111111; // turn on pullup resistors
}

void loop()
{
  //Alternate between scanning the left and right hand pins 
  //to reduce necessary delay between reads
  for (int i=0; i<6;i++){ 
    scan_pin(right_hand_pins[i], i, RightKeysStatus[i], false);
    scan_pin(left_hand_pins[i%3], i%3, LeftKeysStatus[i%3], true);
  }
  //Original
//  scan_keys(left_hand_pins, sizeof(left_hand_pins), LeftKeysStatus, true);
//  scan_keys(right_hand_pins, sizeof(right_hand_pins), RightKeysStatus, false);
}

//This function is currently unused
void scan_keys(char *pins, int pinLength, int *KeysStatus, bool left) {
  for (int i=0; i<pinLength;i++){ 
    scan_pin(pins[i], i, KeysStatus[i], left);
  }
}

byte reg_values = 0;

//Read the analog port value for the given pin
//If something changed, trigger MIDI signal
void scan_pin(int pin, int index, byte PinStatus, bool left) {
  //TODO - I wonder if we can replace this with direct port write for even better performance?
  digitalWrite(pin, HIGH);
  //A slight delay is needed here or else we'll be reading the previous pin
  delayMicroseconds(250);//was able to cut this in half by alternating between left and right
  if (left) {
    reg_values = ~PINF;
  }
  else {
    reg_values = ~PINK;
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
  //TODO - if enabled, get dynamic velocity from BMP and set here
  //MIDI.sendControlChange(CC_Volume,midi_vel,channel);

  if (left){
    if (on){
      LeftKeysStatus[group] |= (1 << position);  //setting bit value
    }
    else {
      LeftKeysStatus[group] &= ~(1 << position);  //setting bit value
    }
    pitch = left_notes_midi_numbers[group][position];
    if(pitch < 48) {
      channel = 2;
    }
    else {
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

  //TODO - figure out dynamic velocity
  //MIDI.sendControlChange(CC_Volume,midi_vel,channel);

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
