---
layout: ordered_page
title: Bluetooth
subtitle: Sending MIDI wirelessly
prevUrl: /power
prevTitle: Power
nextUrl: /volume
nextTitle: Dynamic Volume
---

//This will be the tutorial for communicating the MIDI data via bluetooth.  This, coupled with using a battery pack, will make the accordion "wireless".

### Goal: Have the Arduino send MIDI data to the PC wirelessly using Bluetooth.

### The Problem: Now that we've established a MIDI connection over the USB wire, let's take it one step further and send the data over bluetooth instead so that the accordion can be played wirelessly.

Note: This step is optional to build a working MIDI accordion and only necessary if you want to be able to play the accordion wirelessly.  Also, this tutorial assumes you've established your MIDI connection using a Serial-to-MIDI converter (see Sending MIDI guide) and does not apply if you're connecting with a MIDI cable.

You will need:

- Arduino (Uno, Mega, etc)
- Bluetooth HC-05 transceiver
- Bluetooth USB dongle
- 1x1k Ω resistor
- 1x2k Ω resistor
    - You can also use 10k and 20k if you don’t have 1k/2k

### Solution

Honestly, this guy does a much better job of explaining how to do this than I could, so I recommend checking out his tutorials on hooking up bluetooth to Arduino: 
http://www.instructables.com/id/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/?ALLSTEPS

<still, maybe give a brief tl;dr on what I did here in case it deviates, or just for clarity/tl;dr>

When I first booted Tera Term the Serial COM ports were not available - it took a few minutes after pairing the BT devices for them to show up.


Additionally, we'll need to configure the transceiver using AT commands so that it uses a baud rate of 115200 bytes/second:
http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/?ALLSTEPS

<also consider saving the above links as PDFs to have>

This link does a really great job of breaking down each component of getting the HC-05 into AT mode, including which pins need voltage dividers and how to avoid connecting to the KEY/EN pin by using the button on the board:
http://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/ 

It may make the most sense for me to just do it using the original set up.

Note: I couldn't get the KEY pin working through the arduino, so I just used the reset button and held it whenever I wanted to enter a command.

<also add any special tidbits that helped me when I get around to doing this>

Once all of this is done, all you need to do is update your Serial-to-MIDI converter to use the new bluetooth Serial Port instead of the arduino port and you should be good to go.

<image of complete connection should go here>

Note: You can't use TeraTerm while trying to establish a connection to the Serial-to-MIDI converter (because it's occupying the port you need).
