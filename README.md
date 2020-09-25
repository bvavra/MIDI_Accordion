# DIY MIDI Accordion
Schematics, code, and guide for building your own Arduino-powered MIDI accordion _(based off Dmitry Yegorenkov's [AccordionMega project](https://github.com/accordion-mega/AccordionMega))_

### [Full Project Page](http://bvavra.github.io/MIDI_Accordion/)

### Photos

[MIDI Accordion Project Photo Gallery](http://imgur.com/a/U7L83)

### Videos

[Demo Video #1 - Professor Layton Main Theme (Intro)](https://www.youtube.com/watch?v=s197ojk8npI)

[Demo Video #2 - Stolen Moments (by Oliver Nelson)](https://www.youtube.com/watch?v=Z_4_YdG65XQ)

[Demo Video #3 - Everfrost Peak (from Diddy Kong Racing)](https://www.youtube.com/watch?v=8d2E2YQPqnI)

[Demo Video #4 - Stickerbrush Symphony (from Donkey Kong Country 2)](https://youtu.be/sQWZQSPkWCQ)

| Table of Contents      |
| ---------------------- |
| [Overview](#overview)  |
| [Changelog](#changelog)|
| [Materials](#materials)|
| [Software](#software)  |
| [Quick Guide](#guide)  |
| [Links](#links)        |

## <a name="overview"></a>Overview

The goal of this project is to take a traditional piano accordion and turn it into a MIDI controller capable of playing music through your computer.  To do this requires solving a few different problems; the finished MIDI Accordion needs to be able to:

1. Send a digital signal from the accordion keys and buttons to the computer
2. Convert that signal to MIDI
3. Play that signal back with music software
4. Communicate that signal for each button on the accordion

The above goals are enough to have a functional MIDI instrument, but there are a few additional "nice to have" requirements that can also be implemented, such as the ability to:

5. Communicate MIDI signals wirelessly (via Bluetooth)
6. Decouple the accordion's power supply from the computer/wall
7. Add dynamic expression using the accordion bellows (via barometric pressure sensor)
8. Add other expressions such as pitch bend, panning, and other sound control effects with potentiometers (sliders, knobs, joysticks, etc.)

_Note: In the project, the computer is **required** for playback; this project does **not** involve installing speakers to play back MIDI-realized sound directly from the accordion.  I may delve into such a feat someday, but today is not that day._

## <a name="changelog"></a>Changelog

### v1.3.00 (10/2/2017)

- Added joystick to control pitch bend
    - Can be configured (at compile time) to bend pitch up or down
	- Can be configured (at compile time) to bend pitch for melody, bass, and/or chords
- **Breaking Change!** - Opto-interruptor pin connections have been moved in order to free up analog and PWM pins for future components.  If you are upgrading to v1.3 from an earlier version you will need to adjust your Arduino pin connections and/or code.  [Schematics and Breadboard docs](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion/schematics) have been updated accordingly.

### v1.2.00 (1/2/2017)

- Added BMP180 support, allowing changes in pressure from moving bellows to change MIDI expression (i.e. volume)
   - Made the following changes from the original [AccordionMega](https://github.com/accordion-mega/AccordionMega) BMP085 code:
       - Updated the temperature and pressure reading code to use SparkFun's BMP180 library.
	   - Updated pressure<->velocity mapping algorithm according to various play tests.
       - Pressure is now read asynchronously from the Arduino - adds approximately 2ms delay when enabled (original added delay was about 3-5ms).

### v1.1.00 (12/28/2016)

- Added Bluetooth support (e.g. HC-05), allowing MIDI data to communicate wirelessly instead of over USB
    - Uses #DEFINE variable to toggle between using USB and additional serial port at compile time to reduce bandwidth usage

### v1.0.00 (12/09/2016)

- First working version of final project with all accordion keys mapped according to bvavra's PCB design.
- Made the following changes from the original [AccordionMega](https://github.com/accordion-mega/AccordionMega) code:
    - Updated files (and syntax) from .pde to .ino (new Arduino IDE)
    - Removed register shift code 
	    - Although it's a cool idea that could be realized on the accordion by adding some digital register buttons, I've decided to keep things simple and only transmit one register per button and control which registers sound via MIDI playback software (e.g. Logic, Reason, etc.)
    - Shaved off 2-3 ms of latency by reorganizing how the opto-interruptors are read.
    - Updated MIDI code to use Arduino MIDI Library
    - Added some extra comments to explain what some of the more obtuse lines are doing (port manipulation, bit operations, etc.)

## <a name="materials"></a>Materials

The final project requires the following materials and components:

**Item Name (Part Number)**|**Quantity**
:-----:|:-----:
Accordion|1
Arduino Mega 2560 R3|1
Barometric Pressure Sensor (BMP 180)|1
Bluetooth Transceiver Module (HC-05 RS232)|1
USB Bluetooth Dongle|1
Photo/Opto Interruptor (ITR-9608)|65
270 Ohm Resistor 1/4W 5%|65
1k Ohm Resistor 1/4W 5%|11
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

The total cost of these materials can vary. [The original accordion project](https://github.com/accordion-mega/AccordionMega/wiki/Accordion-Mega-story) cost under $100.  If you exclude the accordion, I spent about $220 on the above materials.  If you don't have an accordion you can get a decent enough one on eBay for as low as $100 (normally I'd advise against buying an accordion off eBay, but it doesn't have to sound good; it just needs to function mechanically).  I bought mine for $150 (plus $30 shipping), bringing my project's grand total cost to about $400.

You will also need the following tools:

**Item**|**Usage**
:-----:|:-----:
Multimeter|Used to debug circuit connectivity.
Soldering Iron|Used to join components to the circuit boards.
60-40 Rosin Core Solder|Used to create circuit joints.
Brass Wire and Holder|Used to clean the soldering iron tip.
Desoldering Wick/Pump/Bulb|Used to fix soldering mistakes.
Adjustable Circuit Board Holder|Used to hold the circuit board in place while soldering.
Wire Strippers|Used to cut and strip wires to size.
Wire Cutters|Used to trim wires and components after they've been soldered.
Utility Knife|Used to cut the circuit boards and sever bad solder connections.
Sandpaper|Used to smooth cuts made to circuit boards.
Power Drill|Used to drill holes in the circuit boards and the accordion.
Small Flathead Screwdriver (c.1/8")|Used to open up and take apart the accordion.
Crimping pliers|(Optional) Used to make jumper wire ends.

I had to buy most of these tools for this project, which rang up to about $100 total.

## <a name="software"></a>Software

### Project Source Code

The only files required for the final project are the Arduino files located in the root level [MIDI_Accordion directory](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion).  Everything else in this repo is supplemental information to help research and build the project (e.g. Prototypes, Datasheets, Design docs, etc.).  Of course, you will need the [Arduino IDE](https://www.arduino.cc/en/main/software) to write and upload the project source code to your Arduino.

### Arduino Libraries

The following libraries are required to compile the MIDI_Accordion Arduino sketch:

- [Arduino MIDI Library](http://playground.arduino.cc/Main/MIDILibrary)
    - Used to simplify sending data via the MIDI protocol.
- [Sparkfun's Arduino BMP180 Library](https://github.com/sparkfun/BMP180_Breakout)
    - Used to interface with the BMP180 barometric pressure sensor.

### Third Party

To play your finished MIDI Accordion you'll need the following additional software:

- Serial-to-MIDI converter
    - Used to convert data coming from the Arduino from Serial to MIDI.  I recommend [Hairless MIDI <-> Serial Bridge](http://projectgus.github.io/hairless-midiserial/).
- Virtual MIDI port
    - Used to connect the MIDI data to playback software.  
	- [OSX configuration instructions](http://feelyoursound.com/setup-midi-os-x/)
	- [Linux (Debian/Ubuntu) config instructions](https://ubuntuforums.org/showthread.php?t=1445186)
	- Windows requires 3rd party software - I recommend [LoopMIDI](http://www.tobias-erichsen.de/software/loopmidi.html).
- MIDI controller/sequencer/player
    - Used to play back MIDI data triggered by the accordion.  It can be whatever your preferred MIDI playback software is (e.g. Logic, Reason, etc.), but if you don't have one I recommend using [Virtual MIDI Piano Keyboard (VMPK)](http://vmpk.sourceforge.net/), which is free and Windows/OSX/Linux compatible.
- (Optional) [ASIO4All](http://www.asio4all.com/)
    - Used to reduce latency when playing back MIDI on Windows machines without ASIO audio drivers.

## <a name="guide"></a>Project Quick Guide

This is meant to be a bare-bones guide to building your own MIDI accordion, providing only a general roadmap for those who already know what they're doing or for those who are curious about the process, but only want a tl;dr.  You can view the [complete guide here](http://bvavra.github.io/MIDI_Accordion/).  I also provided a [set of links](#links) that were helpful to me in getting my project up and running - if any of them are broken please let me know and I'll update the list accordingly.

Note: Although this guide is labelled as "quick", the project itself is not.  Between researching, building prototypes, making a lot mistakes (and learning from them), and designing/building/testing the final product, I spent over 200 hours on this project.  However, I made this guide in hopes that others can do this project with all the necessary information and resources available in one place, which I believe will enable future makers to complete this project in far less time.

### Basic Assembly/Installation Instructions

_In-depth instructions can be found on the [**MIDI Accordion Project Page**](http://bvavra.github.io/MIDI_Accordion/)_

#### [Sending MIDI data from the Arduino](http://bvavra.github.io/MIDI_Accordion/sending-midi/) and [playing it back with music software](http://bvavra.github.io/MIDI_Accordion/midi-playback/)

1. Upload the [MIDI_Tutorial](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/MIDI_Tutorial) prototype to your Arduino.
2. Install the Serial-to-MIDI conversion software of your choice (e.g. [Hairless MIDI](http://projectgus.github.io/hairless-midiserial/))
3. Install (or configure) a virtual MIDI port (e.g. [LoopMIDI](http://www.tobias-erichsen.de/software/loopmidi.html)) and configure the Serial-to-MIDI converter to send data from the connected Arduino to the virtual MIDI port.
4. Open the MIDI playback software of your choice (e.g. [VMPK](http://vmpk.sourceforge.net/)) and configure the MIDI input to read from the virtual MIDI port.  At this point you should hear MIDI being played by the Arduino.

#### [Mapping Accordion button and key presses to digital MIDI signals](http://bvavra.github.io/MIDI_Accordion/opto-interruptor/)

1. Build and upload the [Opto_Interruptor_1](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/Opto_Interruptor/Opto_Interruptor_1) prototype to your Arduino and assert the following:
	1. When the interruptor is blocked, the digital output is HIGH.
	2. When the interruptor is unblocked and the input pin is HIGH, the digital output is LOW. 
	3. When the interruptor is unblocked and the input pin is LOW, the digital output is HIGH.
2. [Cut and mount opto-interruptor blockers](http://bvavra.github.io/MIDI_Accordion/accordion/) to each of the 24 key pads on the left hand and each of the 41 keys on the right hand.  I did this by [cutting and gluing zip ties to the bottom of the keypads](http://i.imgur.com/JqKlctF.jpg) and [mounting circuits inside the bellows](http://i.imgur.com/5CT6w8J.jpg), whereas Dmitry [attached metal rods on the other side of the keypads](http://dimon.shopopalo.com/arduino/left_hand_24.jpg).  You can choose whichever method works best for you and your accordion.
3. Test that the blockers work by uploading the [MIDI_Accordion](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion) sketch to your Arduino, wiring a prototype of 1 or more opto-interruptors away from the breadboard (using M/F jumper wires), and [temporarily adhering them over the blockers](http://i.imgur.com/zXNV6vj.jpg?1) where they will be for the finished product.  Pressing the corresponding accordion keys when all the MIDI software is running should trigger sound playback (though the pitches may be incorrect).
	
#### [Designing](http://bvavra.github.io/MIDI_Accordion/circuit/), [building](http://bvavra.github.io/MIDI_Accordion/assembly/), mounting, and wiring the circuits

1. Design and build circuits for each of the keys that need to be mapped according to the [final project schematics](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/master/MIDI_Accordion/schematics/MIDI_Accordion_schem.png).  You can refer to [these design docs](https://github.com/bvavra/MIDI_Accordion/tree/master/pdf/design), [this Fritzing reference](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/master/MIDI_Accordion/schematics/MIDI_Accordion_bb.png), and my [project photos](http://imgur.com/a/U7L83) for reference.
	* Note: Each accordion is different, so the designs that worked for my accordion may not work for yours.  Stick to the schamtics and plan your boards accordingly.  Be sure to leave enough room for wires to connect everything and for the accordion to be closed up.
2. Mount the circuit boards to the accordion and wire everything together.  If you plan on adding the BMP180 for bellow expression, be sure to provide enough slack for the wires connecting the treble and bass side to allow for pulling the bellows out.
3. Drill a hole to allow for connecting the USB cable from the Arduino to the computer and [mount the USB port in the hole](http://i.imgur.com/rvxLVdk.jpg?1).
4. Once [everything is connected](http://i.imgur.com/3HWcnyW.jpg), upload the [MIDI_Accordion](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion) sketch to your Arduino, open all of your connection software, and [test that every key works properly](http://bvavra.github.io/MIDI_Accordion/testing/) by asserting that the key doesn't stick and that the key or button plays the correct pitch(es).  You will likely have to adjust the pitch mappings in the code based on how you organized and wired your sensor circuits.
	
#### (Optional) Communicating MIDI signals wirelessly via Bluetooth

1. Upload the [Bluetooth_Tutorial](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/Bluetooth/Bluetooth_Tutorial) prototype to your Arduino and follow the instructions on [this instructables page](http://www.instructables.com/id/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/?ALLSTEPS) to hook up the transceiver to the Arduino, configure it with your Bluetooth receiver, and test that it works properly.
2. Upload the [Bluetooth_Tutorial_2](https://github.com/bvavra/MIDI_Accordion/tree/master/Prototypes/Bluetooth/Bluetooth_Tutorial_2) prototype to your Arduino and follow the instructions on [this instructables page](http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/?ALLSTEPS) to access the Bluetooth transceiver's AT mode.  While in AT mode, update the baud rate to 115,200 kb/sec by entering the command "AT+UART=115200,1,0".  You can optionally also change the name and password of the Bluetooth device.
3. If you haven't already, [solder, mount, and wire a circuit board for the HC-05](http://i.imgur.com/t24RJP1.jpg) according to the given [design](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/master/MIDI_Accordion/schematics/MIDI_Accordion_bb.png) and [schematics](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/master/MIDI_Accordion/schematics/MIDI_Accordion_schem.png).
4. Open the [MIDI_Accordion](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion) sketch and uncomment the "//#define BLUETOOTH" line of code to enable the bluetooth serial port.  Upload the changes to your Arduino. 
5. Update your Serial<->MIDI conversion software to point to the Bluetooth COM port instead of the Arduino port.
6. (Optional) Instead of plugging the Arduino into the computer via USB cable, you can now use a battery pack to power the accordion.  A 4xAA pack is recommended, but certain 5V USB phone charger packs may also work (but I haven't tested this yet, so your mileage may vary).
	
#### (Optional) Adding dynamic expression using the accordion bellows via barometric pressure sensor

1. If you haven't already, [solder, mount, and wire a circuit board for the BMP180](http://i.imgur.com/t24RJP1.jpg) according to the given [design](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/master/MIDI_Accordion/schematics/MIDI_Accordion_bb.png) and [schematics](https://raw.githubusercontent.com/bvavra/MIDI_Accordion/master/MIDI_Accordion/schematics/MIDI_Accordion_schem.png).
2. Open the [MIDI_Accordion](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion) sketch and uncomment the "//#define BMP" line of code to enable using the BMP180 to map bellow pressure to MIDI expression.  Upload the changes to your Arduino. 
3. Cover as many unused air holes in the accordion bellows as possible to maximize the amount of air resistance you will feel when squeezing the bellows.
4. (Optional) The bellows may not feel right based on your playing style or the amount of air resistance.  To improve this, you may need to tweak the numbers in the function used to map the difference in air pressure to MIDI expression values.

#### (Optional) Adding a joystick to pend pitch when pressing the master palm switch

1. Solder, mount, and wire a circuit board for a mini joystick so it [gets triggered when you press the register switch](https://i.imgur.com/hfIESQA.gif).
2. Open the [MIDI_Accordion](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion) sketch and uncomment the "//#define JOYSTICK" line of code to enable mapping the joystick tilt to MIDI pitch bend data. 
3. Adjust the configuration variables in [Pitch_Bend.ino](https://github.com/bvavra/MIDI_Accordion/blob/master/MIDI_Accordion/Pitch_Bend.ino) as desired.

## <a name="links"></a>Links

The following links were helpful in making this project happen.  If any of these links are broken, or if you have any additional links that you found helpful, please [contact me](https://github.com/bvavra/MIDI_Accordion/issues) and let me know so I can update this list accordingly.

### Accordion

- [Lots of accordion repair resources](http://www.accordionrevival.com/Home.php)
- [Taking apart the Stradella bass system](http://paisanoaccordions.blogspot.com/2009/09/not-for-faint-of-heart.html)
- [Taking apart the piano keyboard](http://www.instructables.com/id/How-to-fix-an-accordion-keyboard/)
- [Accordion repair videos](http://www.ehow.com/videos-on_2531_apart-accordion.html)
- [Accoridon repair tools](http://accordionplus.com/tools.html)

### Arduino

- [Internal pullup resistor tutorial](https://www.arduino.cc/en/Tutorial/InputPullupSerial)
- [Info about switches](http://www.gammon.com.au/switches)
- [Arduino baud rates](http://arduino.stackexchange.com/questions/296/how-high-of-a-baud-rate-can-i-go-without-errors)
- [Arduino port manipulation](https://www.arduino.cc/en/Reference/PortManipulation)
- [Port manipulation tutorial](http://www.instructables.com/id/Arduino-is-Slow-and-how-to-fix-it/?ALLSTEPS)
- [Another port manipulation tutorial](http://www.instructables.com/id/Fast-digitalRead-digitalWrite-for-Arduino/?ALLSTEPS)
- [Organizing Arduino code with tabs](https://liudr.wordpress.com/2011/02/16/using-tabs-in-arduino-ide/)

### MIDI

- [MIDI Protocol essentials](https://ccrma.stanford.edu/~craig/articles/linuxmidi/misc/essenmidi.html)
- [Arduino MIDI Library docs](http://fortyseveneffects.github.io/arduino_midi_library/index.html)
- [MIDI CC List](http://nickfever.com/music/midi-cc-list)
- [Send and receive MIDI with Arduino](http://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/?ALLSTEPS)
- [When does audio latency matter and not matter?](http://music.stackexchange.com/questions/30323/when-does-audio-latency-matter-and-not-matter)
- [Latency problem using MS GS Wavetable Synth](https://answers.microsoft.com/en-us/windows/forum/windows_7-pictures/latency-problem-using-ms-gs-wavetable-synth/1e85704a-803c-438f-b472-fb0cb5211be4)
- [Reducing latency on MIDI-over-USB keyboard](http://sound.stackexchange.com/questions/27583/reducing-latency-on-midi-over-usb-keyboard)
- [Arduino MIDI Expression Pedal](https://www.codeproject.com/articles/38203/arduino-based-midi-expression-pedal)
- [Difference between MIDI velocity and Expression](http://www.sweetwater.com/insync/what-difference-between-midi-volume-expression/)
- ["Unexpected data byte" error when sending CC data over Hairless MIDI](https://github.com/projectgus/hairless-midiserial/issues/16)

### Opto-Interruptors

- [How To Set Up A Photo Interrupter (or Slotted Optical) Switch On The Arduino](http://www.utopiamechanicus.com/article/arduino-photo-interruptor-slotted-optical-switch/)
- [Connecting a photo interrupter/optoisolator to an Arduino](http://www.martyncurrey.com/connecting-an-photo-interrupter-to-an-arduino/)
- [ITR-9608 Datasheet](http://www.electrodragon.com/w/images/6/60/ITR9608.pdf)

### Bluetooth

- [Cheap 2-Way Bluetooth Connection Between Arduino and PC](http://www.instructables.com/id/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/?ALLSTEPS)
- [Modify The HC-05 Bluetooth Module Defaults Using AT Commands](http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/?ALLSTEPS)
- [Arduino with HC-05 Bluetooth module - AT MODE](http://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/)

### Barometric Pressure Sensor

- [BMP180 Barometric Pressure Sensor Hookup](https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-)

### Power

- [Feeding power to Arduino: the ultimate guide](http://www.open-electronics.org/the-power-of-arduino-this-unknown/)
- [Arduino power sharing](http://electronics.stackexchange.com/questions/36947/arduino-power-sharing)
- [9V is not a good power source](http://cybergibbons.com/uncategorized/arduino-misconceptions-6-a-9v-battery-is-a-good-power-source/)
- [Arduino power switch](http://www.instructables.com/id/Powering-Arduino-with-a-Battery/)
- [Is it bad practice to provide power through the VIN Pin?](https://www.reddit.com/r/arduino/comments/2jdyba/is_it_bad_practice_to_provide_power_through_the/)
- [Powering an Arduino Mega with external USB Power Bank?](http://arduino.stackexchange.com/questions/9069/powering-an-arduino-mega-with-external-usb-power-bank)

### Wiring

- [Soldering 101 (adafruit)](https://learn.adafruit.com/lets-put-leds-in-things/soldering)
- [How to solder electronics (wikiHow)](http://www.wikihow.com/Solder-Electronics)
- [How to solder (instructables)](http://www.instructables.com/id/How-to-solder/?ALLSTEPS)
- [Basic de-soldering guide](http://www.epemag.wimborne.co.uk/desolderpix.htm)
- [Custom Cables & Guide to Crimping Dupont PCB Interconnect Cables](https://www.youtube.com/watch?v=GkbOJSvhCgU)

### Electronics

- [How to read a schematic](https://learn.sparkfun.com/tutorials/how-to-read-a-schematic)
- [Understanding the functions of a multimeter](https://learn.adafruit.com/multimeters/)
- [Light-Emitting Diodes (LEDs)](https://learn.sparkfun.com/tutorials/light-emitting-diodes-leds)
- [How to test diodes using a digital multimeter](http://en-us.fluke.com/training/training-library/test-tools/digital-multimeters/how-to-test-diodes-using-a-digital-multimeter.html)
- [Why exactly can't a single resistor be used for many parallel LEDs?](http://electronics.stackexchange.com/questions/22291/why-exactly-cant-a-single-resistor-be-used-for-many-parallel-leds)
- [8 Tips On How To Pick A Resistor For An Arduino (Circuit)](http://www.utopiamechanicus.com/article/arduino-resistor-selection/)
- [Voltage Dividers tutorial](https://learn.sparkfun.com/tutorials/voltage-dividers)
- [Transistors tutorial](https://learn.sparkfun.com/tutorials/transistors)
- [How transistors work](http://www.build-electronic-circuits.com/how-transistors-work/)