---
layout: ordered_page
title: Testing
subtitle: Making sure it actually works
prevUrl: /assembly
prevTitle: Final Assembly
---

[//]: # (This will be the tutorial for testing the final product.  I'll go over what we're testing and highlight some of the issues I ran into.)

### Goal

Test the final product for playability.

### The Problem

Okay, so we finally have a finished MIDI accordion... but does it actually work?  We'll need to test the following:

1. Do all keys sound?
2. Are all keys mapped correctly to their proper pitches?
3. Do any keys stick?
4. Are there latency issues?

### Solution

Start by booting up all the software and getting the [final project](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion) running on the accordion:

1. Start your virtual MIDI port (if it's not running already).
2. Open your MIDI playback software of choice and verify it's hooked up to your virtual MIDI port.
3. Upload the [final project](https://github.com/bvavra/MIDI_Accordion/tree/master/MIDI_Accordion) code to your Arduino (if it's not on there already).
4. Start your Serial-to-MIDI conversion software and connect it to your Arduino and virtual MIDI port.

Now it's time to start testing.  It's easier if you already have the accordion open and still have access to pressing all of the buttons so you can easily switch between key testing and circuit testing.
