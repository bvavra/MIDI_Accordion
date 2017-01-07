# MIDI_Accordion
Steps and code for building an Arduino-powered MIDI accordion (based off Dmitry Yegorenkov's AccordionMega project: https://github.com/accordion-mega/AccordionMega)



| Table of Contents      |
| ---------------------- |
| [Intro](#p0)           |
| [Overview](#p1)        |
| [Changelog](#p2)       |
| [Materials](#p3)       |
| [Software](#p4)        |
| [Quick Guide](#p5)     |
| [Links](#p6)           |

//TODO - reorganize all of this.  It should link to the detailed project page (and maybe have links to photos/videos), but this should only be a Quick Guide with the minimum amount needed to get the project working:

- demo videos
- brief intro
- changelog
- BoM
- software list
- schematics/code
- bare-boned instructions
- links

## <a name="p0"></a>Intro

The information and code on the AccordionMega project was invaluable to getting my MIDI accordion up and running, but as someone who has never worked on an electronics project before, the documentation was a bit bare-boned for my lack of experience and much of it was outdated (broken links, deprecated parts, etc.).  My hope with this project is to organize and break down each of the components necessary to build a MIDI Accordion so that any aspiring accordionist/musician/programmer/maker has all the information they need in one place to make it happen.

That being said, while it IS theoretically possible to just follow these instructions blindly, I highly recommend taking some time to research the ins and outs of each step of this project to gain a better understanding of how everything works in case you find yourself troubleshooting or fixing mistakes.  I've provided a set of links that I've used to help get my project up and running - if any of them are broken please let me know and I'll update the list accordingly.

## <a name="p1"></a>Overview

The goal of this project is to take a piano accordion and turn it into a MIDI Controller capable of playing music from your computer.  To do this requires solving a few different problems:

1. Sending a digital signal from the accordion keys and buttons to the computer
2. Converting that signal to MIDI
3. Playing that signal back with music software
4. Communicating that signal for each button on the accordion

This is enough to have a functional MIDI instrument, but there are a few additional optional problems that can also be solved:

5. Communicating MIDI signals wirelessly (via Bluetooth)
6. Decoupling the accordion's power supply from the computer/wall
7. Adding dynamic expression using the accordion bellows (via barometric pressure sensor)

## <a name="p2"></a>Changelog

### v1.2.00 (1/2/2017)

- Added BMP180 support, allowing changes in pressure from moving bellows to change MIDI expression (i.e. volume)
   - Made the following changes from the original [AccordionMega](https://github.com/accordion-mega/AccordionMega) BMP085 code:
       - Updated the temperature and pressure reading code to use SparkFun's BMP180 library.
	   - Updated pressure<->velocity mapping algorithm according to various play tests.
       - Pressure is now read asynchronously from the Arduino - adds approximately 2ms delay when enabled (original delay was 3-5ms).

### v1.1.00 (12/28/2016)

- Added Bluetooth support (e.g. HC-05), allowing MIDI data to communicate wirelessly instead of over USB
    - Uses #DEFINE variable to toggle between using USB and additional serial port to reduce bandwidth usage

### v1.0.00 (12/09/2016)

- First working version of final project with all accordion keys mapped according to bvavra's PCB design.
- Made the following changes from the original [AccordionMega](https://github.com/accordion-mega/AccordionMega) code:
    - Updated files (and syntax) from .pde to .ino (new Arduino IDE)
    - Removed register shift code 
	    - Although it's a cool idea that could be realized on the accordion by adding some digital register buttons, I've decided to keep things simple and only transmit one register per button and control which registers sound via MIDI playback software (e.g. Logic, Reason, etc.)
    - Shaved off 2-3 ms of latency by reorganizing how the opto-interruptors are read.
    - Updated MIDI code to use Arduino MIDI Library
    - Added some extra comments to explain what some of the more obtuse lines are doing (port manipulation, bit operations, etc.)

## <a name="p3"></a>Materials
//TODO - fill in - add BoM

## <a name="p4"></a>Software
//TODO - fill in - add Links to code and 3rd party software

## <a name="p5"></a>Quick Guide

This is meant to be a bare-bones guide to building your own MIDI accordion, providing only a general roadmap for those who already know what they're doing or for those who are curious about the process, but only want a tl;dr.  A complete guide is in the works and will be made available soon.

[MIDI Accordion Photo Gallery](http://imgur.com/a/U7L83)

//TODO - fill in outline steps

## <a name="p6"></a>Links
//TODO - fill in - group by category
