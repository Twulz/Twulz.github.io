---
layout: post
title:  "Re-Training Basil Faulty the DonkeyCar"
date:   2019-06-08
categories: Things Mechatronics DonkeyCar
tags: Robot AI MachineLearning Basil Solder DonkeyCar AutonomousCar Self-Driving-Car Data Training
related_image: 
  path: /images/donkeyCar/setup/06_action_shot.jpg
  alt: Basil Action Shot
---

I could finally set up the training environment using Ubuntu in VirtualBox on Windows to allow Basil to learn to race around the track in my kitchen!

<!--more-->

# Data Gathering Take 2

My [last attempt]({{ site.baseurl }}{% post_url 2019-05-25-Attempting-to-train-basil %}) to train Basil Faulty the DonkeyCar was only somewhat successful. He still couldn't go around the track I trained him on so this time I decided to have a more methodical approach to the data-gathering.

I re-laid one corner of the track that was particularly tricky, even just while _I_ was training him and deleted the old tub so none of the old tub data would taint the new neural network.

```shell
cd play/ohmc_car
rm -r tub
```
I also had to re-enable the joystick in manage.py/config.py:
```shell
nano manage.py
nano config.py
```

I did a few practise runs around the track without recording the data to make sure I wouldn't be giving him the wrong information. 

# Training Take 2

This time when I was back on the main pc, rsync worked! Maybe this had to do with the virtual environment setup but copying the tub was so easy this time:

```shell
source ~/virtualenvs/donkeycar/bin/activate
cd ohmc_car/
ls
rm -r tub
rsync -av pi@basilfaulty.local:play/ohmc_car/tub .
```

I could then train the neural network again the same way `python manage.py train --tub tub/ --model models/take2.hdf5`

The neural network again took approximately 28 epochs to train the model, I copied this back to the pi using `scp` this time:

```shell
scp take2.hdf5 pi@basilfaulty.local:play/ohmc_car/models
python manage.py drive --model ~/play/ohmc_car/models/rae_one_way.hdf5
```

He could then drive around the _whole_ track (albeit slowly)! Success!

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/setup/05_slow_complete_track.mp4" type="video/mp4">
        Basil slowly went around the whole track!
    </video>
</center>

I tried increasing the speed but he was very wobbly and did go off the track a few times.

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/setup/06_fast_wobbly.mp4" type="video/mp4">
        Basil completed the track but was a bit wobbly
    </video>
</center>

# Take 3!

I did all the data-gathering and training again but this time I focussed on having a near-constant throttle and instead of 'twitching' the steering as I went around the track I tried having a consistent steer around a corner in an attempt to get rid of some of Basil's wobbles.

This was very successful - after retraining, Basil could smoothly take the whole track!

<center>
    <video width="540" height="960" controls muted>
        <source src="{{ site.baseurl }}/images/donkeyCar/setup/07_fast_complete.mp4" type="video/mp4">
        Basil speeding along around the whole track!
    </video>
</center>

