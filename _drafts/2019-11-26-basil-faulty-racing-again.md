---
layout: post
title:  "Basil Faulty the DonkeyCar is racing again!"
date:   2019-11-25
categories: Things Mechatronics DonkeyCar
tags: Robot AI MachineLearning Basil Solder DonkeyCar AutonomousCar Self-Driving-Car Data Training
---

After my [last blog post]({% post_url 2019-11-12-upgrading-basil-faulty-3-1-0 %}) where I set up the newest version of DonkeyCar - I've got Basil Faulty driving around the Hackerspace once more!

<!--more-->

## Training Basil

It's been a while, so I'm just going to copy the commands that I needed to re-train Basil again, including changing myconfig.py to use the Joystick:

```sh
cd ~/mycar
nano myconfig.py
python manage.py drive
```

This new version of DonkeyCar allows me to use the Joystick wirelessly - the console gives the controls and it is MUCH easier for when Basil gets a little too excited...

So with everything configured, I then drove approx 8 times around the track each way, until I had approx 10,000 images in my training data.

I used [Filezilla][filezilla] to copy the tub via FTP to my laptop, this actually turned out to be the most time-consuming part!

The training took 3.47 seconds to complete! What an upgrade!

To get Basil driving himself, I just had to run the driving commands and I could still use the joystick to control it, switching between the 3 levels of automation using the `SELECT` button.

```sh

```

Please forgive my potato cam, I was too overexcited!

[filezilla]: https://filezilla-project.org/
