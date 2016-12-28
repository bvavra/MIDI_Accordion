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
struct MySettings : public midi::DefaultSettings
{
   // Set MIDI baud rate. MIDI has a default baud rate of 31250,
   // but we're setting our baud rate higher in order to 
   // properly decode and read outgoing MIDI data on the computer.
   static const long BaudRate = 115200;
};

//#define DEBUG//uncomment this line to print serial messages, comment to send MIDI data
//#define BLUETOOTH//uncomment this line to send MIDI data via bluetooth instead of USB

#ifdef BLUETOOTH
  MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial1, MIDI, MySettings);
#else
  MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);
#endif

int CC_Volume = 11;//Control Change code for volume

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
  {38,39,40,41,50,51,52,53},//10
  {46,47,36,37,58,59,48,49},//11
  {42,43,44,45,54,55,56,57} //12
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
  {65,64,62,60,59,57,55,53},//2
  {79,77,76,74,72,71,69,67},//3
  {70,68,66,63,61,58,56,54},//4
  {93,91,89,88,86,84,83,81},//5
  {90,87,85,82,80,78,75,73},//6
  {92,0,0,0,0,0,0,0}        //7
};

void setup()
{
  #ifdef DEBUG
    Serial.begin(9600);
  #else
    MIDI.begin();
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
  //scan_keys(left_hand_pins, sizeof(left_hand_pins), LeftKeysStatus, true);
  //scan_keys(right_hand_pins, sizeof(right_hand_pins), RightKeysStatus, false);
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
  delayMicroseconds(300);//was able to cut this in half by alternating between left and right
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
