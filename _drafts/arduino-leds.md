---
layout: post
title:  "Playing with Arduino LEDs"
date:   
categories: arduino
tags: arduino, LED
---

I have previously played with Arduino projects, today I decided to play around with some LEDs and re-familiarise myself with the platform.

<!--more-->

## Setting up the board
As it has been a while since I last played with an Arduino, I had to reinstall the software.
This is as simple as the following from the official Arduino site: 

1. Heading over to the [instructions page](https://www.arduino.cc/en/Guide/Windows), 
2. Downloading and installing the software, 
3. Loading up the 'Blink' example (the hardware equivalent of 'Hello World!'), 
4. Configuring the board type 
5. Ensuring the correct port is selected and
6. Testing the program.

## Pulsing LEDs
I've been asked by a friend to help out with lighting up a future cosplay of hers so I connected up a few LEDs to get a feel for what kind of effects that were possible and what she was after.

Starting with this great [SparkFun][sparkfun] link, turns out using PWM to pulse and LED is super simple

[sparkfun]: 	https://www.sparkfun.com/tutorials/329