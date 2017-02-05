---
layout: ordered_page
title: Mapping Input
subtitle: Making digital signals from physical motions
prevUrl: /midi-playback
prevTitle: MIDI Playback
nextUrl: /accordion
nextTitle: Accordion Setup
---

[//]: # (This will be the tutorial for learning how to receive analog input from opto-interruptors.  Include some info about how opto-interruptors work, where to get them, some potential pitfalls, and detailed isntructions for using the tutorials (with link to the tutorial folder in the GitHub repo).  Also, I may consider splitting this into multiple pages, because there's a LOT of info here.  Not sure yet what the best way is to organize it all.)

### Goal

Have the Arduino send MIDI data whenever a sensor becomes unblocked.

### The Problem

We need to figure out how to take the action of pressing a physical accordion key and turning it into a digital signal.  We can use opto-interruptors to do this (also known as photo interruptors, optical sensors, or optical interruptors).  Eventually we'll need to do this for all 41 keys in the right hand and all 120 buttons in the left (which, luckily, only requires 24 mappings), but for now let's just get a couple working in a prototype so we know the circuit is correct and the parts are working properly.

**You will need:**

- Arduino (Uno, Mega, etc)
- 4x Opto-Interruptor (eventually you'll need 65: 41 for the right hand, 24 for the left)
    - I highly recommend using the ITR-9608 - you may have trouble with other components depending on the specifications (see Part 1.3 for details).
- 4x 270 Ω resistor
- 2x 1k Ω resistor
- 2x NPN Transistor (eventually you'll need 8: 5 for the right hand and 3 for the left)
    - I recommend using the 2N2222A, which is what I used in my final project.
- [MIDI Accordion's Opto-Interruptor Tutorials](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/Opto_Interruptor)

### Solution

Before we jump into making the prototypes, it's important to understand a bit about the components we're using and how we intend to use them.

#### How do opto-interruptors work?

An opto-interruptor is a combination of an infrared LED and a transistor, with a gateway inbetween them.  

[//]: # (TODO - insert diagram)  

When the gateway is unobstructed, the infrared light shines directly into the transistor and triggers the switch to flow into the emitter.

[//]: # (TODO - reword)

When the gateway is blocked (or the LED is off), the transistor is powered through the collector.  We can control the flow of current in these interruptors two different ways:

1. By unblocking the gateway (i.e. pressing a key/button on the accoridon)
2. By turning the voltage HIGH and LOW on the interruptor's diode.

The final project will use both of these methods to determine which keys are being pressed at which times, so our prototype needs to test both use cases.

[//]: # (TODO continue filling in.  Also discuss the importance of using pullup resistors.)

#### 1. Hooking up a single interruptor to the Arduino

Before we start getting the interruptor to play music, we'll just write serial output to assert that everything is hooked up properly.  The first prototype proves a few different concepts:

1. When the interruptor is blocked, the digital output is HIGH.
2. When the interruptor is unblocked and the input pin is HIGH, the digital output is LOW. 
3. When the interruptor is unblocked and the input pin is LOW, the digital output is HIGH.

[//]: # (TODO - insert fritzing board and schematics diagram)

[//]: # (TODO - insert and discuss code in each step)

##### 1.1 - When the interruptor is blocked, the digital output is HIGH

Interruptors are typically read as analog output, but we can read digital output hundreds of times faster. 

[//]: # (TODO - insert image of timing output)

In order for digital reads to work, though, we need to make sure there is a significant difference in the analog output when the interruptor is blocked or unblocked.  Analog output can range anywhere between 0 and 1023.  In order to convert our interruptor output to a digital signal, the analog output must be less than 512 when it is unblocked and greater than 512 when it's blocked, and wider the difference in those values are, the more reliable these outputs will be.

##### 1.2 - When the interruptor is unblocked and the input pin is HIGH, digital output is LOW

This is usually the opposite of what you'd expect (normally blocked would be LOW and unblocked would be HIGH), but we're taking advantage of the Arduino's internal pullup resistors, which inverts the output.  To read more about using pullup resistors and how they work, check out these links:

- [Internal pullup resistor tutorial](https://www.arduino.cc/en/Tutorial/InputPullupSerial)
- [Info about switches](http://www.gammon.com.au/switches)

For this project, the purpose of using pullup resistors (as opposed to pulldown resistors) is to be able to turn the LED on and off while the interruptor is unblocked *without* the Arduino detecting a change, and we can do so by only checking for changes when the LED is on.  This allows us to wire together multiple opto-interruptors to the same analog pin, which is necessary because we need 65 sensors for the final project, but the Arduino Mega only has 16 analog pins.
 
[//]: # (TODO - reword/clarify)

##### 1.3 - When the interruptor is unblocked and the input pin is LOW, digital output is HIGH

The last concept is very important for the final project to work, and it depends greatly on having the correct parts.  I had initially ordered the wrong kind of opto-interruptors (ATIR0621DS) which led to a whole slew of problems.  In order to get my circuit working with that part, I had to add a 10kΩ resistor between the cathode and ground pins and had to test the circuit in the dark because natural sunlight was being picked up by the sensor. Also, I had to increase the delay in the program from .5 ms to 12 ms to avoid unwanted notes from being picked up (which is an unacceptable amount of delay for an electronic musical instrument).

As soon as I replaced the ATIR0621DS with the ITR-9608 all these problems went away and everything *just worked.*

#### 2. Chaining multiple interruptors to the same analog pin

The final product will have multiple interruptors connected to a single analog pin (8 sets of 3 on the left hand, 7 sets of 5 and one set of 6 on the right hand).  The Arduino will have to be able to detect which ones are actually being triggered.  We only need 4 (a 2x2 matrix) to test this proof of concept.

AccordionMega solves this by hooking each column of interruptors to a single digital pin (where the +5V comes from for the diode) and continuously iterates turning each one on and off and reading the column to see which interruptors are "on".  We'll be doing the same. 

[//]: # (TODO - insert fritzing board and schematics diagram)

We need the transistor because having all 8 interruptor diodes hooked up to a single pin it will yield a lot of current, and the transistor will reduce the overall current going to GND to a much lower, more tolerable level for the Arduino.  I originally had trouble getting the transistor working properly because I was using the C945 as was specified in AccordionMega's original schematics.  When I replaced the C945 with the 2N2222A everything worked properly. 

[//]: # (TODO - research and compare datasheets to determine why this happened)

If everything is hooked up and working correctly, you should get a single “Note on” message from the serial output when you unblock any of the four interruptors, followed by a single “Note off” event when you block it again.  Make sure that the note number is different for each interruptor, and that the number of note on and off events match the number of open and closed interruptors respectively.

**Bonus:**
I recommend altering your circuit to try different matrix combinations (1x4, 4x1) and make sure everything still works properly.  You can also add more opto-interruptors if you wish; the tutorial as written supports an 8x4 matrix of up to 32 opto-interruptors.


#### 3. Sending MIDI

Now let's configure the interruptors to send MIDI data.  If you're using the Arduino Uno for your prototype, note that the Uno only has one serial port, and we can't send non-MIDI data to the Serial<->MIDI converter, so we need to remove all the debug print statements and rely on our ears instead to make sure the circuit is working properly (or you can read debug statements from your Serial-to-MIDI converter if it supports it).

[//]: # (TODO - insert photo of midi output)

If everything's hooked up properly (which should have been proven in Part 2 above), you should get a single MIDI note on event when you unblock any of the four interruptors, followed by a single MIDI note off event when you block it again.  Make sure that the MIDI note played is different for each interruptor, and that the number of notes sounding matches the number of open interruptors.


### Troubleshooting

- When I unblock the interruptor:
    - Nothing happens
        - This can happen when the difference in analog output is not enough to trigger a change in digital ouput.  Double check the analog output in Part 1 above and make sure the signal is strong enough to trigger a digital read.  Also try changing the resistor value.
        - Also, I've observed that adding more interruptors to the same analog pin may reduce the higher analog output reading, so try testing Part 1 again with 2 interruptors hooked up to the same analog pin.
    - I get two MIDI notes instead of one
        - This is what happens when the interruptor isn't getting a clear reading when the input pin is LOW.  This can happen because natural light is still providing a reading to the interruptor.  Ensure the sensor is not in direct sunlight, or try the sensor in the dark.
        - This also happens sometimes because the Arduino is reading both input pins as HIGH at the same time, and can be fixed by increasing the delay after the PIN HIGH command.
        - NOTE: I had these problems when using the ATIR0621DS interruptor.  As soon as I switched to the ITR-9608 everything worked perfectly.  Check your interruptor's datasheet and make sure it is designed to only read infrared light.
    - I get a continuous string of off/on events
        - Make sure all the wires are firmly connected - if one is loose it could cause this problem.
        - Also make sure there's a clear distinction between having the interruptor blocked and unblocked (i.e. make sure you pull out the obstruction all the way).

### Credit

Thank you to:

- [David Pankhurst](http://www.utopiamechanicus.com/) for making a solid breakdown of [using opto-interruptors with Arduino](http://www.utopiamechanicus.com/article/arduino-photo-interruptor-slotted-optical-switch/).
- [Martyn Currey](http://www.martyncurrey.com/) for also making a solid breakdown of [using opto-interruptors with Arduino](http://www.martyncurrey.com/connecting-an-photo-interrupter-to-an-arduino/).
- [Dmitry Yegorenkov](https://github.com/accordion-mega/AccordionMega) again for his code that proves you can use port manipulation to do lightning-fast digital reads against the opto-interruptors, which would otherwise make this instrument practically unplayable.

