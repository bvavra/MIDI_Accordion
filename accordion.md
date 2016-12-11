---
layout: ordered_page
title: Accordion Setup
subtitle: Preparing your accordion for MIDI-fication
prevUrl: /opto-interruptor
prevTitle: Mapping Input
nextUrl: /circuit
nextTitle: Circuit Layout
---

//This will be the tutorial for obtaining an accordion and preparing it for midification - this has to be a bit vague since it will differ for each accordion, but it should include
- how to find an accordion (sites, things to consider, etc.)
- how to take apart an accordion
- how to do minor repairs (unsticking buttons/keys, etc.)
- mapping out how to apply the digital circuits.
many of these will also point to other sites that have greater info already written for some of these topics.

### Goal

Obtain an accordion and design a plan for hooking up the opto-interruptors to register changes to key presses.

### The Problem 

Can't build a MIDI accordion without an accordion!  Once you have one, you'll need to make sure all the keys are in working order.  From there, you'll need to decide how you want to set up the opto-interruptor triggers (which may differ from my personal solution depending on your accordion model and personal preference).

**Disclaimer:** The accordion is not a standardized instrument - they vary greatly in how they are manufactured, so the inner workings can be different from accordion to accordion.  That being said, take this guide with a grain of salt, as not all of these instructions may exactly apply to your model of accordion.  Take discretion and seek other accordion repair guides if needed.

### Solution

**1. Finding an accordion**

If you already have an accordion, then you're good to go.  If not, Craigslist and eBay are your friend.  Normally if you're looking for an accordion to play I'd advise against buying one online since you don't really know what you're getting - the reeds could be in terrible condition and require significant repair or replacement.  Luckily for us, we don't care what condition the reeds are in because we won't be using them!  Given that we're replacing the reed blocks with opto-interruptor sensors, you can probably find an accordion in decent mechanical condition (regardless of how it sounds) for a fairly cheap price online, and any minor issues should be easily repairable.  

Some things you should be considering when selecting an accordion:

- Bass system: This project assumes the accordion uses a 120-button Stradella bass system, which would also work for a 72 or 96 button system.  The code and circuit design would have to be modified slightly to support smaller bass systems.  If the accordion uses a free-bass system, you're on your own.
- Keyboard size: A full-size accordion has a 19” keyboard, which was one of my personal requirements (but it usually comes with a higher price tag).  17” keyboard accordions are pretty easy to come by on eBay and tend to be cheaper.
- Key condition: Do any of the buttons stick?  Are any of the keys broken, out of place, or missing?  Unsticking keys is usually pretty easy to do (albeit tedious), and bending bass buttons back into place can be done without much effort, but replacing missing keys or lining up an unlevel keyboard may prove to be a bit more difficult.
- Bellows condition: Are there any leaks in the bellows?  Are any of the edge caps <get proper name> missing?  This typically isn't a deal-breaker, especially if you don't plan on using the pressure sensor to read volume data from the bellows.
- Tone Chamber: Personally, I would recommend avoiding accordions with a tone chamber.  Not only will they be a lot more expensive (for a feature you won't even be using), but the internal layout is a bit more involved and may make it more difficult for you to place the opto-interruptors and/or circuits.

**2. Taking apart the accordion**

Once you get your accordion, you should test it to assert its condition.  Press every key in the right hand, and every button the left hand.  If any of them stick, you may need to repair them - see Part 3 below for more details.  Either way, you'll need to open up the accordion to take out the reed blocks.  Start by taking out the bellow pins closest to the right hand (there are likely 3 in the front and 3 in the back).  You should be able to use a pair of pliers and carefully twist them out.  You should keep track of which pin went where so you can put them back in the same place (for some accordions, the pins may differ between the front and back, and left and right).  Once you take out all the pins from the right hand side of the bellows, you should be able to carefully remove the keyboard side from the bellows.  Now take out the pins on the left hand side of the bellows.

Once the bellows have been removed from both sides, it's time to remove the reed blocks.  For both sides, there should only be a screw or two that need to be removed before you're able to take out all of the reed blocks. 

//insert images of reed blocks in the accordion and removing them

**3. Fixing up the accordion (if necessary)**

If you're lucky, your accordion is already in great shape and there's nothing you need to do.  However, if you're like me and have an accordion with some sticky bass buttons or keys, you may need to go in and unstick them.  I recommend checking out these links, which go into great detail on how to take apart the accordion keys and buttons. <insert accordion repair links here>

**4. Deciding how to trigger the opto-interruptors**

Now that the accordion is in playable shape, it time to figure out how you want to trigger the opto-interruptor sensors.  AccordionMega solved this problem by gluing metal rods to every key pad on both the left and right hand keys. /*link to his images online*/  If you choose to follow this path, you're on your own to figure out the details.  If you wish to explore an alternative, I decided to solve this problem from the other side by attaching blockers on the underside of the key pads of both the left and right hand keys. /*insert image of inserted blockers*/ I made the blockers out of zip ties and glued them to the key pads using E6000 (//add link), as shown here: 

// insert images of making zip tie blockers here

The height of the blockers depend on the key pads.  I had to make two different heights for the left and right hand keys, so be sure to measure and make sure that the height of the blockers on the keypad is the same as the height of the opto-interruptor placed over the keypad.  Note that, when you press the key, the pad goes both down and away in a certain direction.  I suggest positioning the opto-interruptor such that the blocker moves both down and away from it (you may run into collision issues otherwise).

//add a section about the glue and re-positioning the blockers if needed.

If you choose to attach blockers to the inside of the keypads you will need to find a way to disable the register buttons from closing in on the reed hole where you placed the blockers.  I did this on my accordion by pulling a metal rod out of its slot for each register that could close in on the blockers. 

// insert images of removed register levers

From here you should take some time to analyze the inner layout of your accordion's key pads and determine the best way to lay out the circuits for the opto-interruptors.  Also decide where you want to place the Arduino Mega (I chose the middle of the treble side because my accordion's layout leaves a gap in where the keypads are placed right in the center).  I'll discuss some of the options I considered for my project in the next guide.

### Troubleshooting

> I can't find an accordion I want (at a price I want to pay).

- Be patient!  I searched online for about 4 weeks before I found an accordion in my price range that I was happy with.  eBay gets new accordions all the time, so check frequently. 

> I want to attach blockers under the keys, but I can't unhook the register buttons.

- I was lucky enough to be able to disable the register button triggers by hand, but you may need to use more force than I did to unhook yours, which may require dismantling or even destroying the connectors.  Use your own discretion and decide what you're willing to do to your accordion.

### Credit

// links to accordion repair links, eBay searches?, other helpful things?

