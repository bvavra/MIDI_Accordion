---
layout: page
title: About me
subtitle: Some stuff you may or may not want to know
---

//This will be the tutorial for using the BMP sensor to allow dynamic expression using the bellows.

### Goal

Add expressiveness to the MIDI accordion by reading the air pressure differences in the bellows and converting it into MIDI velocity.

### The Problem

Accordion keys are not pressure-sensitive - the volume of the accordion is dictated by how hard you push or pull on the bellows.  We need to find out how we can convert that action into a digital signal.  We can use a barometric pressure sensor to do just that.

**You will need:**

- Arduino (Uno, Mega, etc)
- BMP180 Barometric Pressure Sensor
- BMP180 Arduino Library

### Solution

Start by hooking up the BMP180 to the Arduino.  You can get details on how to do that here: https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup- 

// insert fritzing image and schematics here

Note that the SDA and SCL pins are different depending on which Arduino board you're using.  This example uses the Uno, which uses A4 and A5, whereas the Mega has dedicated SDA and SCL pins (20 and 21).

Once it's hooked up, you should be ready to test the circuit. //refer to BMP tutorial 1

Once you have the Arduino displaying changes in pressure read from the BMP, it's time to try converting the message to MIDI. //refer to BMP tutorial 2

### Troubleshooting

//insert issues here

### Credit

// thank sparkfun for the component and library here, and AccordionMega for his code
