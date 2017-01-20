---
layout: ordered_page
title: Dynamic Volume
subtitle: Turning Bellow Pressure into MIDI Velocity Data
prevUrl: /bluetooth
prevTitle: Bluetooth
---

//This will be the tutorial for using the BMP sensor to allow dynamic expression using the bellows.

### Goal

Add expressiveness to the MIDI accordion by reading the air pressure differences in the bellows and converting it into MIDI velocity.

### The Problem

Accordion keys are not pressure-sensitive - the volume of the accordion is dictated by how hard you push or pull on the bellows.  We need to find out how we can convert that action into a digital signal.  We can use a barometric pressure sensor to do just that.

**You will need:**

- Arduino (Uno, Mega, etc)
- BMP180 Barometric Pressure Sensor
    - Note: Most components I've seen require head pins to be soldered on before you can use it, so if you need to and haven't yet I suggest brushing up on your soldering skills.
- BMP180 Arduino Library

### Solution

**1 - Hooking the BMP to the Arduino**

Start by hooking up the BMP180 to the Arduino.  You can get details on how to do that here: https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup- 

// insert fritzing image and schematics here

Note that the SDA and SCL pins are different depending on which Arduino board you're using.  This example uses the Uno, which uses A4 and A5, whereas the Mega has dedicated SDA and SCL pins (20 and 21).

Once it's hooked up, you should be ready to test the circuit. //refer to BMP tutorial 1

Once you have the Arduino displaying changes in pressure read from the BMP, it's time to try converting the message to MIDI. //refer to BMP tutorial 2
You don't need to have an accordion to test that it works; all you need to do is blow on the BMP and you should see changes in the pressure reading.

**2 - Converting pressure into velocity**

Once you have the Arduino displaying changes in pressure from the BMP, it's time to try converting the message to MIDI velocity. //refer to BMP tutorial 2

**3 - Sending MIDI Control Changes**

Now that we have the BMP reading pressure and the Arduino converting the pressure data to velocity, we need to send that data as proper MIDI and update the MIDI output software to read that data.

//TODO - discuss MIDI CC and how BMP tutorial 3 sends it

//also need to show how to update MIDI output software to interpret MIDI CC, specifically
Reason
VMPK (still need to figure this one out)

**4 - Calibrating the BMP with your accordion**

This is the tricky part - we need to hook up the BMP to the accordion such that squeezing the bellows feels and makes dynamic changes as realistically as possible.  We'll need to do the following:

- Close as many air holes as possible to get the maximum amount of resistance when moving the bellows while playing.
- Adjust the function used to map BMP pressure output to MIDI velocity so that changes in bellow movement accurately reflect expected changes in dynamics.

At this point you're going to need your accordion.  It doesn't need to be fully working (though it helps), but you'll need to at least put the Arduino and BMP inside it wherever you plan on putting it when it's completed so that pressure readings remain relatively the same.

4.1 - Plug the leaks

When playing a real accoustic accordion there is a lot of resistance when squeezing the bellows because air has to go through the reeds to make sound, and the airways to do so are quite small.  Our MIDI accordion, however, has no reeds, so the airways are much larger and it doesn't take a lot of effort to pull and push the bellows.  We need to try and mitigate this discrepancy as much as possible, which means closing any airways that aren't being used.

The number of airways that need to be blocked largely depend on the type of accordion you have.  Mine is a 4/5 accordion, meaning it has 4 reed blocks on the right hand and 5 blocks on the left, giving those keys 4 and 5 air holes repectively. //insert images

If your MIDI accordion is set up to read the opto-interrupers on the bellows side with blockers on the key pads then at least one air hole needs to remain open per key* - the rest can and should be closed.  Most of these can probably be closed by moving the register switches to the off position, unhooking the plates from the register buttons, and securing them so that they don't move. //insert image
Some key hole rows might not have plates though (particularly the left hand) - in this case cover the holes any way you see fit.  I just taped strips of cardboard. //insert image

Once you're done closing as many air holes as you can, put the accordion back together and try squeezing the bellows in and out while fingering some tunes - it'll likely still not feel as tight as a real accoustic accordion, but it should be close enough to get the job done.

* However, If you decided to do what Dmitry and Jason did and put the interruptors on the outside with metal rods blockers, you have the option of closing all air holes and leaving one row open slightly for each key.  This will likely give you a much more realistic feel when moving the bellows while playing.

4.2 - Adjust the pressure mapping function


### Troubleshooting

//insert issues here

### Credit

// thank sparkfun for the component and library here, and AccordionMega for his code
