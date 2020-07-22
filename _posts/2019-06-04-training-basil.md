---
layout: post
title:  "Actually Training Basil Faulty the DonkeyCar"
date:   2019-06-04
categories: Things Mechatronics DonkeyCar
tags: Robot AI MachineLearning Basil Solder DonkeyCar AutonomousCar Self-Driving-Car Data Training
related_image: 
  path: /images/donkeyCar/setup/05_basil.jpg
  alt: Basil
---

I could finally set up the training environment using Ubuntu in VirtualBox on Windows to allow Basil to learn to race around the track in my kitchen!

<!--more-->

# Working with Virtual Environments

I went to the hackerspace this week and everybody jumped on board with helping me get Basil trained. I'd made a few mistakes in setting up the training environment - the [ohmc instructions][ohmc instructions] outlined how to set up the virtual environment but I didn't know I needed to re-activate it each time I wanted to train.

Here are the steps I needed to use to use it properly:
``` shell
virtualenv -p python3 ~/virtualenvs/donkeycar
source ~/virtualenvs/donkeycar/bin/activate
```

To make sure I'm using the virtual environment, the console changes to `(donkeycar) $`

I re-installed tensorflow in this environment, but didn't use the cached version, in case I'd messed it up or it was otherwise corrupted. I also re-installed donkeycar and run the training inside the virtual environment.
```shell
pip install --no-cache tensorflow==1.13.1
git clone https://github.com/autorope/donkeycar donkey_two
cd donkey_two/
pip install -e .
cd  ohmc_car/
python manage.py train --tub tub/ --model models/test.hdf5
```

And finally the training began! The training process goes through a number of epochs - it stops automatically when the training does not result in a better model, for me this was after 27 epochs.

I then copied the finished model to the pi:

```shell
scp test.hdf5 pi@basilfaulty.local:play/ohmc_car/models
```

From the ssh interface on Basil I could then run the model using a similar command to the training:
```shell
ssh pi@basilfaulty.local
cd play/ohmc_car
python manage.py drive --model ./models/test.hdf5
```

I then accessed the web interface at `https://basilfaulty.local/8887` and instead of driving in 'manual' mode, I could select the automated driving options - I used 'Local Angle' so I could control the speed manually while the model controlled the steering.

And here he is after the first training! He can't do the full track; I think this is a 'garbage in-garbage out' scenario where my potato training didn't do Basil any favours but boy was it exciting to see him try to steer!

Here's the first video, yep, he went straight into the chair!

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/setup/01_first_straight.mp4" type="video/mp4">
        Basil taking on the first straight
    </video>
</center>

Here he could do a corner and the straight but ran off the track instead of trying this corner!

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/setup/02_straight_reversed.mp4" type="video/mp4">
        Basil driving a corner and the straight
    </video>
</center>

Yes... I stopped the video to stop him hitting the wall!

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/setup/03_corners.mp4" type="video/mp4">
        Basil taking some corners
    </video>
</center>

And here he didn't even attempt to go around this corner.

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/setup/04_off_track.mp4" type="video/mp4">
        Basil taking the corners and completely off track
    </video>
</center>

It's safe to say that I think I need to try training again...

[donkeycar docs]: http://docs.donkeycar.com/
[ohmc instructions]: http://www.openhardwareconf.org/wiki/OHMC2019_Software_instructions