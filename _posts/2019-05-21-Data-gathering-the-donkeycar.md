---
layout: post
title:  "Data Gathering for Basil Faulty the DonkeyCar"
date:   2019-05-21
categories: Things Mechatronics DonkeyCar
tags: Robot AI MachineLearning Basil Solder DonkeyCar AutonomousCar Self-Driving-Car
related_image: 
  path: /images/donkeyCar/buildDay/04_basil.jpg
  alt: Basil
---

I'd got Basil up and running on the workshop day but he was still a normal RC car until I could get him trained up and driving himself. I had a few hiccups trying to gather data using a ps3 controller and while I set up the training environment which I've outlined here.

<!--more-->

# More Data Gathering

I had gathered some data at the hackerspace on the workshop day but after I'd left I decided to re-gather the data using the track I'd laid out in my own kitchen. The other guys at the build workshop had said that different lighting and other variables could make the data less-than-ideal in different environments, and there were a lot of data points I would have to delete anyway (while Basil was still on stilts, for example).

## Controlling using a PS3 Controller

The first time data-gathering I had used my phone to access the web server for Basil and used my thumb to steer him around. I found that I was absolutely _terrible_ at controlling him this way and that I would have been training Basil to do a lot of the wrong things if I continued to train him like that. Also, when I took my thumb off the controls he either:

1. Stopped completely _or_
1. Goes full speed straight ahead.

This is less than ideal so I have a few spare PS3 controllers around and I decided to set one up to control Basil directly.

The [DonkeyCar Docs][donkeycar ps3] provide the instructions to install it using [this GitHub repo][ps3_link] from AutoRope. This seemed straight-forward to begin with, but actually took a lot of troubleshooting. 

First I found that the instructions skipped turning on bluetooth on the Pi: `sudo systemctl start bluetooth` then I could follow [the instructions in the repo readme][ps3_link].

This got the controller working to control the steering if I followed these steps:
1. Followed the instructions to install above (previously)
1. Have Basil switched on and connected to the network.
1. Press the centre button on the PS3 controller until it vibrates and connects.
1. Start Basil's server to drive: `python manage.py drive`
1. Use the ps3 controller to drive.

But this would not work to control the throttle. I tried re-installing and re-connecting but nothing would get the throttle working. I also tried connecting the controller to my PC and controlling that way but at the time I didn't realise I still had the controller connected to the Pi!

Eventually I discovered that turning on Basil with the controller plugged _in_ before pressing the centre button and starting the drive server - only _then_ would the throttle be responsive using the second joystick.

## Calibrating Steering and Throttle

Before continuing I decided to calibrate the steering and throttle as recommended in the DonkeyCar Docs. Here are the results for each:

`donkey calibrate --channel 0` is for the throttle.
```
THROTTLE_FORWARD_PWM = 430
THROTTLE_STOPPED_PWM = 400
THROTTLE_REVERSE_PWM = 350
```

`donkey calibrate --channel 1` is for steering. Instead of plotting the graphs for the steering calibration I set the steering all the way left and established the point at which it began moving to the right. I did the same for the right side and found the middle.

Left: 290
Middle: 355
Right: 420


With that renamed the old 'tub' which contained the old training data, put down a new track using masking tape that did a lap of my kitchen and was able to train Basil once more!

Next time I'll hopefully get to the training...

[donkeycar ps3]: http://docs.donkeycar.com/parts/controllers/#bluetooth-joystics
[donkeycar docs]: http://docs.donkeycar.com/
[ohmc instructions]: http://www.openhardwareconf.org/wiki/OHMC2019_Software_instructions
[ps3_link]: https://github.com/autorope/donkeypart_ps3_controller