---
layout: post
title:  "Attempting to Train Basil Faulty the DonkeyCar"
date:   2019-05-25
categories: Things Mechatronics DonkeyCar
tags: Robot AI MachineLearning Basil Solder DonkeyCar AutonomousCar Self-Driving-Car Data Training
related_image: 
  path: /images/donkeyCar/setup/03_controller_basil.jpg
  alt: Basil Wired
---

I tried to set up the training environment using Ubuntu in VirtualBox on Windows to train Basil Faulty the DonkeyCar.

<!--more-->

# Setting up the Training Environment

## Installing Ubuntu on VirtualBox

The first step in training was to set up Linux on my laptop. The training for a DonkeyCar could be done on the pi itself but it would be quite limited by the Pi's resources, it is very much recommended to train on a more powerful computer. Another hurdle was that I run Windows on my laptop and although apparently it is _possible_ to train on Windows, I thought this was a good opportunity to brush up on my linux skills. The fastest way to get up and running was to install VirtualBox and run Ubuntu 18.4 in a virtual machine.

The instructions for doing this are all over the internet, but two parts I need to add - I needed to use a fixed-size hard drive rather than variable (which causes problems with rsync) and to ensure that the network adapter was in _bridging mode_ otherwise I would not be able to connect to the network (and connect to Basil).

![Bridged adapter settings](/images/donkeyCar/setup/05_bridged_adapter.jpg)

## Set up DonkeyCar on Ubuntu

I again followed the instructions on the [OHMC Instructions][ohmc instructions] and [DonkeyCar Docs][donkeycar docs] to set up DonkeyCar on Ubuntu but with a minor change - we used TensorFlow V1.13.1 instead of the version in the other docs.

To change the resolution in Ubuntu: `xrandr -s 1440x900`

SSH into the pi: `ssh pi@basilfaulty.local`

I decided at this point I should change the default password for added security like this: `sudo passwd pi`

Normally you should be able to type `passwd` to trigger the change but this wasn't working for me, specifying the user and sudo privileges worked.

I went into the right folder and made sure to back up all my training data:
```shell
cd play/ohmc_car
mv tub tub_ps3_not_working
```

### Copying the files

`rsync` was the recommended method of copying the files between the Pi and the PC but for some reason this wasn't working for me. I think this was due to my VM setup initially being a dynamic-hard-drive rather than fixed-size but I've included the other options I tried here, in case I need them later, but in the end I went back and did a fresh install.

I first found the size of the tub (this is the place where all the training data is kept): `du -h tub` - it was 5.5Mb - so what's the problem?

I deleted the old tub `rm -r tub`

I zipped up the whole ohmc_car folder: `zip -r ohmc_car.zip ohmc_car`

I tried enabling copy/paste between the virtualbox:
Go to `Settings -> General -> Advanced -> Copy/paste bidirectional`.
This seems to enable the option for text but not for files.

#### Copying to a USB stick

Next I tried just copying onto a USB stick to transfer the file. I followed [these instructions][usb rpi], here are the results:
```shell
ls -l /dev/disk/by-uuid
--- noticed my id was sda1
sudo mkdir /media/twulzblue
sudo chown -R pi:pi /media/twulzblue
sudo mount /dev/sda1 /media/twulzblue -o uid=pi,gid=pi
cd /media/twulzblue
ls
```
This showed me all the files on the usb so it was mounted successfully! I copied the zip with `cp ~/play/ohmc_car.zip .` and unmounted the drive with `sudo umount /media/twulzblue` - notice this is _umount_ not _unmount_!

This way I could get the files off the Pi but still had troubles with enabling the sharing of the USB between the host PC and VM.

#### Sharing a Folder between Ubuntu in a VM and Windows

To set up sharing between my host PC (Wndows) and the VM (Ubuntu) I had to first install the Guest Additions `Devices -> Insert Guest Additions CD Image` and go through the install process.

These are the windows sharing settings I needed:

![Windows Sharing Settings](/images/donkeyCar/setup/02_Sharing_WindowsSettings.PNG)

And the Linux settings `Devices -> Shared Folders -> Settings`
![Windows Sharing Settings](/images/donkeyCar/setup/01_Sharing_LinuxSettings.PNG)

To find out the ID:
```shell
id
uid=1000(twulz) gid=1000(twulz) groups=1000(twulz),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),116(lpadmin),126(sambashare),999(vboxsf)
```

Then add user for vboxsf group and finally mount the drive.
```shell
sudo usermod -G vboxsf -a twulz`
sudo mount -t vboxsf -o rw,uid=1000,gid=1000 SurfaceDownloads ~/share/
```

I could _finally_ access the data!

```
cd ~
cp /share/ohmc_car.zip .
unzip ohmc_car.zip
cd ohmc_car
```

In linux you can view the images using `oeg image.jpg`.

With all that sorted, training is done with one command:

`python manage.py train --tub tub --model /models/model_first.hdf5`

# Troubleshooting

After running the training command I got the following error: 
````
ModuleNotFoundError: No module named 'donkeypart_ps3_controller'
````

I don't need these to train the model so I commented the relevant parts in `config.py` and `manage.py` (the same to enable/disable the controller to begin with).

```shell
nano manage.py
#from donkeypart_ps3_controller import PS3JoystickController
...
#ctr = PS3JoystickController(
#   throttle_scale=cfg.JOYSTICK_MAX_THROTTLE,
#   steering_scale=cfg.JOYSTICK_STEERING_SCALE,
#   auto_record_on_throttle=cfg.AUTO_RECORD_ON_THROTTLE
#)

#V.add(ctr,
#      inputs=['cam/image_array'],
#      outputs=['user/angle', 'user/throttle', 'user/mode', 'recording'],
#      threaded=True)
```

After this I got an error that python wasn't installed correctly so I added it to the path using the [instructions from the ohmc link][ohmc instructions].

I kept hitting problem after problem with the training, I decided to take Basil along to the hackerspace so I could get some help from people who often used linux. The next post will be about any progress I make there.

[sharing]: https://unix.stackexchange.com/questions/16199/how-to-transfer-files-from-windows-to-ubuntu-on-virtualbox
[usb rpi]: https://www.raspberrypi-spy.co.uk/2014/05/how-to-mount-a-usb-flash-disk-on-the-raspberry-pi/
[donkeycar ps3]: http://docs.donkeycar.com/parts/controllers/#bluetooth-joystics
[donkeycar docs]: http://docs.donkeycar.com/
[ohmc instructions]: http://www.openhardwareconf.org/wiki/OHMC2019_Software_instructions
[ps3_link]: https://github.com/autorope/donkeypart_ps3_controller