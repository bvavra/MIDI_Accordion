---
layout: ordered_page
title: Pitch Bend
subtitle: Accordion Whammy Bar
prevUrl: /volume
prevTitle: Power
---

If your MIDI accordion has a master palm switch, you can hook it up to a joystick potentiometer and use it to send MIDI pitch bend (or other modulation) data.

### Goal

Add the ability to send pitch bend data by pressing the accordion's master palm switch.

**You will need:**

- Arduino (Uno, Mega, etc)
- Mini Joystick (I used the CTS Series 254 Ultra-miniature joystick: 254TA103C50A)

Note: This project add-on may not be feasible for your accordion if you don't have a palm switch, or if you are unable to mount the joystick next to the inner mechanics of the switch.  However, you can still mount a joystick or other potentiometer on the outside to use for pitchbend if you want.

### Solution

#### 1. Choosing a Joystick

The only real requirements for choosing a joystick is that it's small enough to fit inside the accordion AND can be pushed by one of the inner levers that get triggered when you push the master palm switch.  Most joysticks are actually fairly large and won't fit my accordion; I picked the 254TA103C50A because it was the smallest joystick I could find, though even at time of purchase I wasn't 100% sure if it would work or not.  Note that although the joystick may support 2-axis movement, we only need a single axis for this project.

#### 2. Wiring and Mounting the Joystick

The circuit is straightforward: like any other analog potentiometer, just hook up 5V, GND, and an analog pin to read the value (the project code uses A0).  You can use the Joystick_1 prototype sketch to test that your joystick is set up properly before soldering to and mounting the PCB.

To ensure the joystick would be triggered by the palm switch lever properly, I had to measure and play around with various positions on the PCB, as well as picking the right standoff size, before mounting it.  The biggest factor was making sure the palm switch lever pushed the joystick just the right amount - if I placed the joystick too far up the lever I wouldn't be able to press the palm switch all the way before hitting the max joystick movement, and if it was too far down the joystick wouldn't trigger until part way through pressing the switch.

[![Joystick](/MIDI_Accordion/img/joystick/joy_pot.gif)](/MIDI_Accordion/img/joystick/joy_pot.gif)

#### 3. Updating the code to map joystick input to MIDI pitch bend

The MIDI_Accordion code has already been updated to do this - just uncomment the #define JOYSTICK variable to enable reading from analog pin A0 and mapping the read value to MIDI pitch bend data.

The Arduino MIDI library already has a built-in function that supports pitch bend:

    MIDI.sendPitchBend(value, channel);

Where value is a value between -8192 (max pitch bend down) and 8191 (max pitch bend up).  How this value translates to the amount the pitch will bend depends on the VST that's realizing the sound - normally the min and max values are a full whole step, but it could be as high as an entire octave or more.  

To map the joystick input to this value we use the following map function:

    map(joystickCurrentValue, joystickValueAtRest, joystickMaxValue, 0, 8191 * bendDirection)

Where bendDirection is either 1 (to bend pitch up) or -1 (to bend pitch down).  You can use the Joystick_2 prototype sketch to play around with these mapping configurations before adding it to the final project.

#### 4. Adjusting the Thresholds (and other Configuration options)

Once the joystick is mounted, you may need to adjust the sensitivity of the joystick to ensure that pitch bend signals are not picked up when the switch is at rest.  This is set in Pitch_Bend.ino with the joy_rest_threshold variable.  The default value is 50.  In my testing, a value between 50 and 100 is suitable, but you may find that this value needs to be adjusted over time.

Other configuration variables in Pitch_Bend.ino include:

- joy_limit - The max pitchBend MIDI value to send (default: 8191)
- joy_benDir - Whether to bend pitch up (1) or down (-1)

One final configuration exists in MIDI_Accordion.ino's main loop() function: defining which MIDI channels the pitch bend applies to.  By default, pitch bend is only applied to MIDI Channel 1 (accordion right hand), but you can optionally apply it to any and all 3 MIDI channels (right hand, left hand bass, left hand chords).

### Going Further

Some additional enhancements that could be made to this feature include:

- An on-board switch to toggle between bending pitch up or down without having to upload code changes
- Adding a second joystick that's triggered by a left-hand register switch to bend the pitch of bass and/or chords separately from the right hand


