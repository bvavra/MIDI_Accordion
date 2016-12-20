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
| [Expected Cost](#cost)       |

Want to build your own MIDI accordion?  Awesome!  Here's a general overview of the project to give you an idea of what you're getting yourself into:

### <a name="reqs"></a>General Project Requirements 
*(what we need to accomplish)*

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

There are other possibilities, but these are the features I'll be covering in this tutorial.

### <a name="skills"></a>Required Skills

I've designed this tutorial to have a relatively low barrier to entry, but I will assume you have some knowledge about the following:

- **Music**
    - If you want to build a MIDI accordion, I'm assuming you know how to play the accordion or some other musical instrument, and that you have a basic sense of fundamental music theory (e.g. notes and chords).  This is required because you will need to map the accordion keys to MIDI notes by number, and it helps to be able to hear if a chord button sounds right or not when played.
- **Arduino**
    - You don't need to be an Arduino master or even have any experience with programming or electrical engineering, but I will assume you have successfully run a basic Arduino prototype at least once and are, hence, relatively familiar with how the Arduino IDE works.  If not, I recommend picking up an [Arduino Getting Started Kit](https://www.amazon.com/s/ref=nb_sb_ss_c_1_18?url=search-alias%3Daps&field-keywords=arduino+getting+started+kit&sprefix=arduino+getting+st%2Caps%2C202), checking out the [Getting Started Guide](https://www.arduino.cc/en/Guide/HomePage), and building a few prototypes to get a feel for how the Arduino works before before jumping too deep into this project.

### <a name="tools"></a>Required Tools

If you, like me, have never dabbed into electrical engineering before, you may not have the tools necessary to build a MIDI accordion.  Here are a list of tools I ended up using throughout the project:

//TODO - include images of everything

- Multimeter
    - This will be your primary debugging tool when putting together prototypes and the final project.  I use it to double check voltage and current in my prototypes as well as to check connectivity after soldering.  It doesn't have to be anything fancy; I picked up mine at a local hardware store for $20.  //TODO - include links
- Soldering Iron (& Accessories)
    - Used to solder wires and components together when building the final project.  I'll go into some basic details on using the iron in the final tutorial.  //TODO - details on what kind to get if you don't have one.  Other things to accompany the soldering iron include:
	    - Solder (I recommend 60/40 with rosin core)
		- Solder pump/wick/bulb
		    - Used to fix your mistakes.
		- Solder tip cleaning wire
		    - Used to routinely clean your soldering iron tip(s).
- Wire Strippers
    - Used to cut and strip wires to size.  Can also be used to cut various components as needed.
- Wire Cutters
    - Used to trim wires and components after they've been soldered.
- Utility Knife
    - Used to cut the circuit boards.  More details about how I did this in the circuit layout tutorial.
- //TODO - add more

### <a name="parts"></a>Required Parts

Here is the complete Bill of Materials for this project.  Specifics may vary from project to project (since all accordions are different), but this should give you a good idea of what parts will be needed and about how much you're likely to spend on them:

- //TODO

### <a name="software"></a>Required Software

To get the most out of this project you'll need a computer (Windows, OSX, or Linux) that can run the following programs:

**Required**

- Arduino IDE
    - Used to write and upload code for your Arduino.
- Serial-to-MIDI conversion software
    - Used to convert data coming from the Arduino from Serial to MIDI.  I'll go over the details in the [MIDI Playback tutorial](../midi-playback).
- MIDI controller/sequencer/playback software
    - Used to play back MIDI data triggered by the accordion.  It can be whatever your preferred MIDI playback software is, but if you don't have one the [MIDI Playback tutorial](../midi-playback) offers some suggestions.
	
**Optional**

- Fritzing
    - I used [Fritzing](http://fritzing.org/home/) to write up diagrams and schematics for all of my prototypes and tutorials.  Images of these diagrams are provided, but if you want to dive into the files themselves this program is free to download and install.
	
Note: All of the above programs are free to downaload, install, and use (for non-commerical purposes, at least).

### <a name="time"></a>Required Time

I'm gonna be honest with you: this project will take a *long* time, especially if you're not familiar with certain aspects of this project (programming, MIDI protocol, electric engineering, etc.).  For reference, this is the work log summary for how much time I've spent on this project (excluding the time it took to put together this tutorial site):

//TODO - include hours breakdown

Although this project page is designed for a user with very little experience and can be followed blindly (in theory), I highly recommend taking the time to research any part of this project tutorial you don't fully understand.  Additionally, I want to make this tutorial as comprehensive as *reasonably* possible, so if you think there's something I didn't cover very well that you want elaborated I encourage you to [log an issue](https://github.com/bvavra/MIDI_Accordion/issues) for me to provide more info.

### <a name="cost"></a>Expected Cost

[Dmitry](https://github.com/accordion-mega/AccordionMega/wiki/Accordion-Mega-story) claimed he was able to build his accordion in under $100.  I was not so lucky, as I had to buy a lot of the tools required to build the project.  I also ended up buying replacement and redundant parts because the first set either didn't work or I ended up never using.  Oh, and I had to buy the accordion itself because I didn't have one lying around that I was willing to put under the knife, so to speak.  By the time I was done I spent approximately $600 on the entire project.  However, if you know *exactly* what you're buying and you already have an accordion, you can probably expect to spend about $300 total, which is not a bad price for a MIDI accordion when you consider [some of the alternatives](https://www.google.com/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#tbm=shop&q=roland+v-accordion).  You can view more details about the price breakdown of this project in the Bill of Materials.

### Ready?

Still want to build a MIDI accordion?  Great - grab your Arduino and start making some prototypes!  The tutorials are outlined to start on the software side and work your way out to the hardware, but you could do these tutorials in just about any order you want.  Or if you already have a good handle on the fundamentals and just want to dive into the project head first, you can skip over to the [project README](https://github.com/bvavra/MIDI_Accordion) to view the bare-boned essentials.