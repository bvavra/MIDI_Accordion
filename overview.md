---
layout: ordered_page
title: Project Overview
subtitle: I made a MIDI Accordion, and you can too!
nextUrl: /sending-midi
nextTitle: Sending MIDI
---

<div class="table-of-contents"></div>

| Table of Contents             |
| ----------------------------- |
| [General Requirements](#reqs) |
| [Required Skills](#skills)    |
| [Required Tools](#tools)      |
| [Required Parts](#parts)      |
| [Required Software](#software)|
| [Required Time](#time)        |
| [Expected Cost](#cost)        |

Want to build your own MIDI accordion?  Awesome!  Here's a general overview of the project to give you an idea of what you're getting yourself into:

### <a name="reqs"></a>General Project Requirements 

The goal of this project is to take a piano accordion and turn it into a MIDI Controller capable of playing music from your computer.  Note that the computer is **required** for playback; this project does **not** involve installing speakers to play back MIDI-realized sound directly from the accordion.  I may delve into such a feat someday, but today is not that day.

In order to build a fully functional MIDI accordion, we have a few different problems to solve:

**Must-Have Requirements**

The MIDI accordion must be able to:

1. Send a digital signal from the accordion keys and buttons to the computer 
2. Convert that signal to MIDI 
3. Play the MIDI back with music software 
4. Communicate that signal for each button on the accordion without noticable delay

This is enough to have a functional MIDI instrument, but there are a few additional optional problems that can also be solved if you wish to do so:

**Nice-to-Have Requirements**

The MIDI accordion could also:

5. Communicate MIDI signals wirelessly (via Bluetooth) 
6. Run off an external power supply (i.e. from a battery pack instead of the computer/wall)
7. Add dynamic expression using the accordion bellows (via barometric pressure sensor)

There are, of course, other bells and whistles that can be added, but these are the features I'll be covering in this tutorial.

### <a name="skills"></a>Required Skills

I've designed this tutorial to have a relatively low barrier to entry, but I will assume you have some knowledge about the following:

- **Music**
    - If you want to build a MIDI accordion, I'm assuming you know how to play the accordion or some other musical instrument, and that you have a basic sense of fundamental music theory (e.g. notes and chords).  This is required because you will need to map the accordion keys to MIDI notes by number, and it helps to be able to hear if a particular chord button sounds right or not when played.
- **Arduino**
    - You don't need to be an Arduino master or even have any experience with programming or electrical engineering, but I will assume you have successfully run a basic Arduino prototype at least once and are, hence, relatively familiar with how the Arduino IDE works.  If not, I recommend picking up an [Arduino Getting Started Kit](https://www.amazon.com/s/ref=nb_sb_ss_c_1_18?url=search-alias%3Daps&field-keywords=arduino+getting+started+kit&sprefix=arduino+getting+st%2Caps%2C202), checking out the [Getting Started Guide](https://www.arduino.cc/en/Guide/HomePage), and building a few prototypes to get a feel for how the Arduino works before before jumping too deep into this project.

### <a name="tools"></a>Required Tools

If you, like me, have never dabbed into electrical engineering before, you may not have the tools necessary to build a MIDI accordion.  Here are a list of tools I ended up using throughout the project:

[//]: # (TODO - include images of everything, and links where appropriate)

- Multimeter
    - This will be your primary debugging tool when putting together prototypes and the final project.  I use it to double check voltage and current in my prototypes as well as to check connectivity after soldering.  It doesn't have to be anything fancy; I picked up mine at a local hardware store for $20.
- Soldering Iron (& Accessories)
    - Used to solder wires and components together when building the final project.  I'll go into some basic details on using the iron in the circuit tutorial.  Other things to accompany the soldering iron include:
	    - Solder (I recommend 60/40 with rosin core)
		- Solder pump/wick/bulb
		    - Used to fix your  soldering mistakes.  You _will_ make mistakes.
		- Solder tip cleaning wire (brass)
		    - Used to routinely clean your soldering iron tip(s).
- Adjustable Circuit Board Holder
    - Used to hold the circuit board in place while soldering.
- Wire Strippers
    - Used to cut and strip wires to size.  Can also be used to cut various components and trim circuit boards as needed.
- Wire Cutters
    - Used to trim wires and components after they've been soldered.
- Utility Knife
    - Used to cut the circuit boards.  More details about how I did this in the circuit layout tutorial.
- Sandpaper
    - Used to smooth cuts made to circuit boards.
- Power Drill
    - Used to drill holes in the circuit boards and the accordion.  
	    - For the circuit boards I recommend using a tungsten carbide drill bit (1/8") to drill through the fiberglass.
- Small Flathead Screwdriver (c.1/8")
    - Used to open up and take apart the accordion.
- Crimping pliers (Optional)
    - Used to make jumper wire ends.  Only needed if you want to reduce the amount of wire clutter in your final project by cutting jumper wires to size.

### <a name="parts"></a>Required Parts

Here is the complete Bill of Materials for this project.  Specifics may vary from project to project (since all accordions are different), but this should give you a good idea of what parts will be needed:

[//]: # (TODO - consider linking full BoM)

**Item Name (Part Number)**|**Quantity**
:-----:|:-----:
Accordion|1
Arduino Mega 2560 R3|1
Barometric Pressure Sensor (BMP 180)|1
Bluetooth Transceiver Module (HC-05 RS232)|1
USB Bluetooth Dongle|1
Photo/Opto Interruptor (ITR-9608)|65
270 Ohm Resistor 1/4W 5%|65
1k Ohm Resistor 1/4W 5%|9
BJT NPN Transistor (2N 2222A)|8
Black 8" Zip Ties|65
USB 2.0 Type A Type B M/M Cable|1
USB 2.0 Type A to Type B F/F Adapter Header|1
SB404 PCB (BB400)|2
BR1 PCB (830)|5
.5"x.5" 90 Degree Angle Corner Plate (H# 884487)|10
2.54mm Breakaway PCB Board 40 Pin Header Kit|1
2.54mm Dupont M/F 40 Pin Connector Kit|1
Multicolored Jumper Wire Ribbon Cable Kit|1
M3 M/F Brass Spacer Standoff Assortment Kit|1
Threaded Insert M3 9.52mm|8
White 4" Zip Ties (100pc)|1

### <a name="software"></a>Required Software

To get the most out of this project you'll need a computer (Windows, OSX, or Linux) that can run the following programs:

**Required**

- [Arduino IDE](https://www.arduino.cc/en/main/software)
    - Used to write and upload code for your Arduino.
- [Arduino MIDI Library](http://playground.arduino.cc/Main/MIDILibrary)
    - Used in the MIDI tutorials and the final project to simplify sending data via the MIDI protocol.
- [Sparkfun's Arduino BMP180 Library](https://github.com/sparkfun/BMP180_Breakout)
    - Used to interface with the BMP180 barometric pressure sensor.  
	    - Note: Even if you choose not to implement the BMP180, this library is required for the final project to compile.
- Serial-to-MIDI conversion software
    - Used to convert data coming from the Arduino from Serial to MIDI.  I'll go over the details in the [MIDI Playback tutorial](../midi-playback).
- MIDI controller/sequencer/playback software
    - Used to play back MIDI data triggered by the accordion.  It can be whatever your preferred MIDI playback software is, but if you don't have one the [MIDI Playback tutorial](../midi-playback) offers some suggestions.
	
**Optional**

- Fritzing
    - I used [Fritzing](http://fritzing.org/home/) to write up diagrams and schematics for all of my prototypes and tutorials.  Images of these diagrams are provided, but if you want to dive into the files themselves this program is free to download and install.
- [ASIO4All](http://www.asio4all.com/)
    - If you're running the MIDI Accordion project on a Windows machine, you may run into latency issues if your sound card doesn't support ASIO.  ASIO4All is a workaround used to reduce latency when playing back MIDI on Windows machines without ASIO audio drivers.
	
Note: All of the above programs are free to downaload, install, and use for non-commerical purposes.

### <a name="time"></a>Required Time

I'm gonna be honest with you: this project will take a *long* time, especially if you're not familiar with certain aspects of this project (programming, MIDI protocol, electric engineering, etc.).  For reference, this is the work log summary for how much time I've spent on this project (excluding the time it took to put together this tutorial site and other documentation):

**Hours**|**Category**|**Description**
:-----:|:-----:|:-----:
57|Research|Learning how the code and circuits work, ordering parts
20|Design|Drafting plans to build the final project
101|Development|Building prototypes and the final project
27|Testing|Testing circuits and code, play testing final project
11|Maintenance|Mostly fixing sticky keys on the accordion
216|Total|*This doesn't count the 50+ hours I spent on documentation*

I'm hoping, though, that having all the necessary information here in one place will enable future projects to be completed much faster.  Knowing what I know now, if I were to make a second MIDI accordion I could probably do it in less than half the time.

Although this project page is designed for a user with very little experience and can be followed blindly (in theory), I highly recommend taking the time to research any part of this project tutorial you don't fully understand.  Additionally, I want to make this tutorial as comprehensive as *reasonably* possible, so if you think there's something I didn't cover very well that you think should be explained in greater detail I encourage you to [log an issue](https://github.com/bvavra/MIDI_Accordion/issues) for me to provide more info.

### <a name="cost"></a>Expected Cost

[Dmitry](https://github.com/accordion-mega/AccordionMega/wiki/Accordion-Mega-story) claimed he was able to build his accordion in under $100.  I was not so lucky, as I had to buy a lot of the tools required to build the project, which set me back $100 from the start.  I also ended up buying replacement and redundant parts because the first set either didn't work or I ended up never using them - that was another $50 down the drain.  Oh, and I had to buy the accordion itself because I didn't have one lying around that I was willing to put under the knife, so to speak.  By the time I was done I spent approximately $600 on the entire project.  However, if you know *exactly* what you're buying and you already have an accordion, you can probably expect to spend about $300 total, which is not a bad price for a MIDI accordion when you consider [some of the alternatives](https://www.google.com/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#tbm=shop&q=roland+v-accordion).  

[//]: # (TODO - add this back in when full Bom is up: You can view more details about the price breakdown of this project in the Bill of Materials.)

### Ready?

Still want to build a MIDI accordion?  Great - grab your Arduino and start making some prototypes!  The tutorials are outlined to start on the software side and work your way out to the hardware, but you could do these tutorials in just about any order you want.  Or if you already have a good handle on the fundamentals and just want to dive into the project head first, you can skip over to the [project README](https://github.com/bvavra/MIDI_Accordion) to view the bare-boned essentials.
