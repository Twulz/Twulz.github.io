---
layout: post
title:  "Building the LED Cube"
date:   2014-09-10
categories: Things Mechatronics Cube4x4x4
tags: Cube4x4x4 LED LEDCube Solder
related_image: 
  path: /images/c4x4x4/holes_LEDs.jpg
  alt: Drilled Holes with LEDs
---

While waiting for the main electronics to arrive, I got started on building the LED cube matrix.

<!--more-->

Please note throughout this project I was referring heavily to [this Instructible][Instructable]

Building the LED Cube was the most fiddly of the whole build, as each of the 64 LEDs had to be soldered together properly ensuring the anodes and cathodes were aligned correctly with the neighbouring LEDs. LEDs generally exploit the human eye's persistence of vision by using multiplexing to only turn on one layer of the cube at a time, but also to be able to switch this to another layer at a high enough frequency that we percieve the different layers as on simultaneously.

To achieve this, the LEDs are soldered so that each group of 4 LEDs vertically share a common anode (positive) and all of the horizontal layers of 16 LEDs share a common cathode (negative). Therefore to turn on an individual LED the VCC must be supplied to the corresponding anode and ground to that layer's cathode to close the circuit and turn on that particular LED.

Before diving into the build, I decided to rig up a small circuit on my breadboard with power and a resistor to test 64 of the LEDs from my kit. Though in the end all of the LEDs were working correctly - it's better to be safe than sorry if the LED in the middle of my cube was faulty!

Now to the build; following the instructions on the [Instructible][Instructible], I measured up a grid of holes to drill based on the length of the legs on the LEDs I had bought to make a template for the LED layers.

![Drilled Holes](/images/c4x4x4/holes.jpg)

The following image was of my original practise go at soldering the legs together, I realised after soldering the second layer that if I had not rotated the legs the same amount on each of the layers, soldering the whole cube together was going to be harder and the final product would not be as well-aligned as it could be. So after these photos were taken I actually soldered another 4 layers each with the same rotation on the legs of the LEDs within the template.

![Drilled Holes with LEDs](/images/c4x4x4/holes_LEDs.jpg)

After a lot of fiddling around I finally got a completed cube, but ended up going to bed before taking a proper picture of just the completed cube before it was connected to anything! But there will be plenty more progress pictures in the next post - testing the cube.


[Instructable]: http://www.instructables.com/id/LED-Cube-4x4x4/