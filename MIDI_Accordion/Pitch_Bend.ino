int joy_pin = 0;
int joy_start_val = 0;
int joy_prev_val = 0;
int joy_bendDir = -1; //Set to 1 to bend pitch up, -1 to bend pitch down
int joy_limit = 8191; //Adjust to set the pitch bend range (max: 8191)
int joy_rest_threshold = 80; //Adjust based on the joystick's sensitivity

void init_joystick() {
  //Need to get the joystick's starting position.
  joy_start_val = analogRead(joy_pin);
}

//Reads the joystick analog value and converts it to a MIDI pitchBend value
int scan_joystick() {
  //Arduino MIDI Libray takes pitchBend values from -8192 to 8191 and converts them from 0 to 16383.
  //When the joystick is being used as a whammy bar (which can only move in one direction), 
  //we only care about mapping half of the values (from 0 up to 8191),
  //and we can invert the mapping to bend the pitch down instead of up (0 down to -8192).
  //How this value affects actual pitch bend depends on the playback software.
  //Most synths adjust the pitch by up to 2 semitones, but some may bend a full octave or more.
  //Adjust joy_limit as needed to set desired pitch bend range for your playback software.
  int joy_raw_val = analogRead(joy_pin);
  int joy_val = map(joy_raw_val, joy_start_val, 1023, 0, joy_limit * joy_bendDir);
  //Ignore values that are too close to the starting value to prevent unwanted churn.
  //You may need to increase joy_rest_threshold based on how sensitive the joystick is at rest.
  if(joy_val >= joy_rest_threshold * -1 && joy_val <= joy_rest_threshold) {
    joy_val = 0;
  } 
  return joy_val;
}

