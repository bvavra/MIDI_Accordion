---
layout: ordered_page
title: Bluetooth
subtitle: Sending MIDI wirelessly
prevUrl: /testing
prevTitle: Testing
nextUrl: /power
nextTitle: Power
---

Now that we've established a MIDI connection over the USB wire, let's take it one step further and send the data over bluetooth instead so that the accordion can be played wirelessly.

### Goal

Have the Arduino send MIDI data to the PC wirelessly using Bluetooth.

### Why Bluetooth?

Why Bluetooth There are many ways to send serial data wirelessly; we're going to use a Bluetooth transceiver 

Note: This step is optional to build a working MIDI accordion and only necessary if you want to be able to play the accordion wirelessly.  Also, this tutorial assumes you've established your MIDI connection using a Serial-to-MIDI converter (see Sending MIDI guide) and does not apply if you're connecting with a MIDI cable.

**You will need:**

- Arduino (Uno, Mega, etc)
- Bluetooth HC-05 transceiver
- Bluetooth USB dongle
- 1x1k Ω resistor
- 1x2k Ω resistor
    - You can also use 10k and 20k if you don’t have 1k/2k

[![HC-05 Breadboard](/MIDI_Accordion/img/hc-05/working_bt_connection.gif)](/MIDI_Accordion/img/hc-05/working_bt_connection.gif)

### Solution

Honestly, [this guy](http://www.instructables.com/member/techbitar/) does a much better job of explaining how to do this than I could, so I recommend checking out [his tutorials on hooking up bluetooth to Arduino](http://www.instructables.com/id/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/?ALLSTEPS).

[//]: # (still, maybe give a brief tl;dr on what I did here in case it deviates, or just for clarity/tl;dr)

Additionally, we'll need to [configure the transceiver using AT commands](http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/?ALLSTEPS) so that it uses a baud rate of 115200 bytes/second.  This [blog post](http://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/) does a really great job of breaking down each component of getting the HC-05 into AT mode, including which pins need voltage dividers and how to avoid connecting to the KEY/EN pin by using the button on the board.

Once all of this is done, all you need to do is update your Serial-to-MIDI converter to use the new bluetooth Serial Port instead of the arduino port and you should be good to go.

[![Working Connection](/MIDI_Accordion/img/hc-05/working.gif)](/MIDI_Accordion/img/hc-05/working.gif)

Up next: [Using an external power supply](../power)

### Troubleshooting Notes

**Using Tera Term**

- When I first booted Tera Term the Serial COM ports were not available - it took a few minutes after pairing the BT devices for them to show up.
- Note: You can't use TeraTerm while trying to establish a connection to the Serial-to-MIDI converter (because it's occupying the port you need).

**Configuring the tranceiver**

- Note: I couldn't get the KEY pin working through the arduino, so I just used the reset button and held it whenever I wanted to enter a command.

### Credit

Thank you to:

- [Hazim Bitar](http://www.techbitar.com/) for making the detailed Instructables for [using Bluetooth with Arduino](http://projectgus.github.io/hairless-midiserial/) and [configuring the Bluetooth transceiver](http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/?)).
- [Martyn Currey](http://www.martyncurrey.com/) for going into great detail on [using the HC-05 in AT mode](http://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/).
