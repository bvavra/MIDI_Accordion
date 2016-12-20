---
layout: ordered_page
title: Testing
subtitle: Making sure it works
prevUrl: /assembly
prevTitle: Final Assembly
---

//This will be the tutorial for testing the final product.  I'll go over what we're testing and highlight some of the issues I ran into.

### Goal

Test the final product for playability.

### The Problem

Okay, so we finally have a finished MIDI accordion... but does it actually work?  We'll need to test the following:

1. Do all keys sound?
2. Are all keys mapped correctly to their proper pitches?
3. Do any keys stick?
4. Are there latency issues?

### Solution

//need to discuss testing, and some issues that I ran into.

**1. Putting it all together**

Once you have a solid draft for your components and you feel good about it, it's “go” time.  I'm not going to go into the ins and outs of soldering and wiring (there are plenty of resources online to help you if you need it), but I will include what I think are a few helpful tips that are specific to this project:

- Do the left hand first.
    - There's a lot less that needs to be wired (24 keys instead of 41), and the keys are spaced farther apart, so it's a significantly less daunting task to complete the left hand vs the right hand.  Once the left hand is complete, you should feel comfortable enough with what you needed to do to get that side working to tackle the right hand.
- Make sure everything fits
    - I thought I lined up all my PCBs perfectly, but when it came time to finally solder components on I realized they were too close, and I had to desolder and move around some things.  Leave ample room for everything.
- Test as you go.
    - The multi-meter is your friend.  Be sure to test frequently that every pin of every component is soldered properly, meaning that it makes a solid connection to the parts you want and, more importantly, doesn't make a connection to the parts you don't want.  The way I cut my PCBs it was easy to do this every 6-8 interruptors or so.  Additionally, I set up the PCBs in a way that was easy for me to hook up to the Arduino at any time to test input. <insert photos of working left hand initial interruptors?>
    - Always check your code first; software is much easier to change than hardware.  I found that out the hard way after I resoldered several components I thought were broken just to find out that I plugged them into the wrong Arduino pin.
- Give your wires some slack.
    - This is especially important for the wires connecting the left and right hand if you plan on pulling the bellows out.  I recommend at least 16 inches of slack for a full-size accordion.  Also, you may find as you're putting everything together that you may want to rearrange where you put some of your components, so having that flexibility is helpful.