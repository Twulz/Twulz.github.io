---
layout: post
title:  "Building Basil Faulty the DonkeyCar"
date:   2019-05-18
categories: Things Mechatronics DonkeyCar
tags: Robot AI MachineLearning Basil DonkeyCar AutonomousCar Self-Driving-Car
related_image: 
  path: /images/donkeyCar/buildDay/01_chassis_group_shot.jpg
  alt: Group Shot
---

Building _Basil Faulty_ the DonkeyCar - a remote control car that becomes a self-driving car using machine learning and artificial intelligence to drive itself around my kitchen.

<!--more-->

# The Build

In [my last blog post]({{ site.baseurl }}{% post_url 2019-05-04-Soldering-donkeycar-hat %}) I attended the soldering day to prepare for this build workshop with a group of like-minded enthusiasts at the [hackerspace][cchs].

![Action shot of the hackerspace](/images/donkeyCar/buildDay/09_hackerspace.jpg)

First I had to put together the laser cut parts and attach the Raspberry Pi and camera.

![Pi Frame](/images/donkeyCar/buildDay/02_pi_frame.jpg)

The actual construction was rather easy, everything is designed to be attached by zipties and rubber bands so modifications can be more easily made.

![Constructing](/images/donkeyCar/buildDay/03_constructing.jpg)

The camera mount even just slots in, no other hardware needed to keep it in place.

![Basil](/images/donkeyCar/buildDay/04_basil.jpg)

The camera is mounted so that it is facing foward and down to get the best view of the path in front of the robot.

![Front View](/images/donkeyCar/buildDay/05_front_view.jpg)

Here he is in all his glory! First up was charging the battery fully before I could start data gathering. My sister came up with the name of _Basil Faulty_ as we're assuming he'll be a little faulty for a while...

![Basil Charging](/images/donkeyCar/buildDay/06_basil.jpg)

# Setting up the Software and Data Gathering

Next step was to set up the software and begin data gathering. The SD cards used by the cars were cloned from the organiser Andy G's DonkeyCar based on the setup from the last OHMC workshop so we could skip the installation and go straight to training. The instructions to install from scratch are in the [OHMC Instructions][ohmc instructions] and the [DonkeyCar Docs][donkeycar docs].

To get training all I had to do was to ssh into the pi and run the 'drive' command.
```
ssh pi@basilfaulty.local
cd play/ohmc_car
python manage.py drive
```

This starts a server at `https://basilfaulty.local:8887` where I could go either on my PC or on my phone and control the car. The first step is to drive the car 6-10 times one way around the track and 6-10 times the other direction while the car records:

1. A picture from the PiCam
1. The throttle value
1. And the steering value

Which will be used by the neural network to train the car to then drive itself!

![Testing](/images/donkeyCar/buildDay/07_testing.jpg)

It was a bit much to manage driving my car and taking a picture at the same time but here is one of the other cars doing its training - I trained mine on the white lines but there were some people experimenting using the red cups as training data too.

![Training track](/images/donkeyCar/buildDay/10_training_track.jpg)

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/buildDay/01_training_another.mp4" type="video/mp4">
        Training some cars
    </video>
</center>

After the data was all gathered it's time to transfer it over to my PC to do the actual training! I didn't quite get this working on the day, so that's a post for another day.

[cchs]: http://www.hackmelbourne.org/
[donkeycar]: https://www.donkeycar.com/
[donkeycar docs]: http://docs.donkeycar.com/
[ohmc instructions]: http://www.openhardwareconf.org/wiki/OHMC2019_Software_instructions
