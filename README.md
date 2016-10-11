# MIDI_Accordion
Steps and code for building an Arduino-powered MIDI accordion (based off Dmitry Yegorenkov's AccordionMega project: https://github.com/accordion-mega/AccordionMega)

| Table of Contents      |
| ---------------------- |
| [Intro](#p0)           |
| [Overview](#p1)        |
| [Materials](#p2)       |

## <a name="p0"></a>Intro

The information and code on the AccordionMega project was invaluable to getting my MIDI accordion up and running, but as someone who has never worked on an electronics project before, the documentation was a bit bare-boned for my lack of experience and much of it was outdated (broken links, deprecated parts, etc.).  My hope with this project is to organize and break down each of the components necessary to build a MIDI Accordion so that any aspiring accordionist/musician/programmer/maker has all the information they need in one place to make it happen.

That being said, while it IS theoretically possible to just follow these instructions blindly, I highly recommend taking some time to research the ins and outs of each step of this project to gain a better understanding of how everything works in case you find yourself troubleshooting or fixing mistakes.  I've provided a set of links that I've used to help get my project up and running - if any of them are broken please let me know and I'll update the list accordingly.

In addition to writing up a bunch of documentation, I also made a few changes to AccordionMega's code:
- Updated files (and syntax) from .pde to .ino (new Arduino IDE)
- Removed register shift code (although it's a cool idea that could be realized on the accordion by adding some register buttons, I've decided to keep things simple and only transmit one register per button and control which registers sound via MIDI playback software (e.g. Logic, Reason, etc.)
- Shaved off 2-3 ms of latency by reorganizing how the opto-interruptors are read.
- Updated MIDI code to use Arduino MIDI Library
- Updated BMP085 code to use SparkFun's BMP180 library.
- Added some extra comments to explain what some of the more obtuse lines are doing (port manipulation, bit operations, etc.)

## <a name="p1"></a>Overview

The goal of this project is to take a piano accordion and turn it into a MIDI Controller capable of playing music from your computer.  To do this requires solving a few different problems:

1 - Sending a digital signal from the accordion keys and buttons to the computer
2 - Converting that signal to MIDI
3 - Playing that signal back with music software
4 - Communicating that signal for each button on the accordion

This is enough to have a functional MIDI instrument, but there are a few additional optional problems that can also be solved:

5 - Communicating MIDI signals wirelessly (via Bluetooth)
6 - Decoupling the accordion's power supply from the computer/wall
7 - Adding dynamic expression using the accordion bellows (via barometric pressure sensor)




## <a name="p2"></a>Materials
//TODO - fill in
