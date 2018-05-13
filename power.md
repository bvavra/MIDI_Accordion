---
layout: ordered_page
title: Power
subtitle: Portable Power Supply
prevUrl: /bluetooth
prevTitle: Bluetooth
nextUrl: /volume
nextTitle: Dynamic Volume
---

If you've followed the [Bluetooth tutorial](../bluetooth), you'll need an alternative way to provide power to the Arduino now that you're no longer getting it from the USB port.

### Goal

Power the Arduino with a battery pack so that the accordion doesn't have to be tethered to the wall, and provide an easy way to turn the power on and off.

### The Problem

You could buy a battery holder with a built in on/off switch, but you can't use it unless you expose the battery holder somewhere on the accordion where you can easily access the switch.  If you don't mind attaching the battery pack on the outside of the accordion then you can just buy a holder with a switch and barrel jack and be done.  Easier yet, you can also use a 5V USB rechargeable battery pack and just strap that onto the accordion instead and connect it to the Arduino's USB port.*  However, if you'd rather hide the battery pack and expose only a switch, then read on.

**You will need:**

- Arduino (Uno, Mega, etc)
- 4xAA Battery Holder
- Toggle switch of your choice

### Solution

#### 1. Choosing a Battery Holder

The first step is choosing which kind of batteries to use.  Most Arduino intro kits supply a 9V battery connector as the default, but [numerous](https://forum.arduino.cc/index.php?topic=87806.0) [sources](https://cybergibbons.com/uncategorized/arduino-misconceptions-6-a-9v-battery-is-a-good-power-source/) [indicate](https://arduino.stackexchange.com/questions/3688/arduino-powering-from-9v-battery) that 9V is a terrible source of power for the Arduino. 

[//]: # (insert links indicating as such along with explanations as to why )

So instead we'll use AA batteries (1.5V each).  The number that you need depends strongly on how much power the circuit requires to function properly.  For this project, 4 AA alkaline batteries are sufficient.  Note that the amount of voltage you get from AA batteries depends on how new the battery is (brand new batteries typically exceed 5V), and whether or not you're using alkaline or NiMH (rechargeable) batteries.

**Note:** 4 Alkaline Batteries may be sufficient, but 4 NiMH batteries may not be enough - May need to get 6.

Another decision to make is whether or not you want to use the barrel jack connector on the Arduino or hook the power directly to the Vin pin.  Both provide the same amount of power to the Arduino (brought down to 5V by the internal regulator).  The only difference is that the barrel jack has a diode that prevents reverse polarity from frying the board. 

[//]: # (TODO: need more research on this - I don't fully know what I'm talking about here)

[//]: # (should include a test on using a multimeter to compare voltage of different batteries in the battery pack)

#### 2. Choosing a Toggle Switch

Next is choosing a power switch.  There are numerous kinds of switches to choose from - for this project all you need is a simple on/off functionality.  I chose a [rocker switch with a built in LED](https://cdn.shopify.com/s/files/1/1490/5112/products/02750018_01_7097e7d8-73c9-4597-8490-ca61c1177e7e_grande.jpg?v=1487005669). This particular switch is rated at 30mA and 12V, but works just fine at 5V.

#### 3. Wiring the Switch

Next is a simple test to make sure we've wired the switch correctly.  Although we're only connecting two wires, most switches have 3 pins, so we should make sure we're making the right connections.

[//]: # (insert Fritzing board and circuit diagram here)

One pin should be labelled "Supply" or "Power" - this is wired to the battery pack.  The other pin should be labelled "Load" - this is wired to the Arduino's Vin pin.  The ground wire on the battery pack is then wired directly to the Arduino's Gnd pin.    If you are using a barrel jack, you will have to take it apart and replace the power wire with a wire connecting to the switch. 

[//]: # (insert link of someone else doing it, because I might not get around to doing this.)

If the switch is hooked up correctly, when you switch it on the LED should light up, and when it's off the LED should turn off.  

### Troubleshooting

- If the LED stays on or off no matter what way the switch is toggled, change your switch wiring.

* Note: many USB battery packs are designed to automatically turn off if not enough power is being drawn (e.g. < 50mA), which makes them unusable for most Arduino projects.  The amount of power used for the MIDI accordion project depends on which components are used in the circuit.  I recommend using a multimeter to check the mA usage of your project and research a comnpatible 5V battery pack that will support this usage.
