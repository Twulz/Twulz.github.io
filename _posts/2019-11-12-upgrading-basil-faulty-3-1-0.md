---
layout: post
title:  "Upgrading Basil Faulty to DonkeyCar v3.1.0"
date:   2019-11-12
categories: Things Mechatronics DonkeyCar
tags: Robot AI MachineLearning Basil Solder DonkeyCar AutonomousCar Self-Driving-Car
---

Today I'm upgrading my DonkeyCar Basil Faulty to donkey v3.1.0! A number of members of the Hackerspace have got the DonkeyCar training working on Windows (rather than a Linux Virtual Machine) and there have been a number of updates since my last install so what better time to upgrade?

<!--more-->

The [DonkeyCar Docs to install on Windows][windows] has been updated since I first tried the Windows install and the main install went without any error messages.

A major improvement with using the native Windows install instead of the Virtual Machine - Tensorflow has been optimised for PCs with Nvidia graphics cards (such as my laptop with a GTX 1050) using Cuda SDK.

## Issue: Pi Camera Permissions

The errors came on the Pi itself - a permissions problem with the camera:

```sh
(env) twulz@basilFaulty:~/mycar $ python manage.py drive
using donkey v3.1.0 ...
loading config file: /home/twulz/mycar/config.py
loading personal config over-rides

config loaded
cfg.CAMERA_TYPE PICAM
cfg.CAMERA_TYPE PICAM
mmal: mmal_vc_shm_init: could not initialize vc shared memory service
mmal: mmal_vc_component_create: failed to initialise shm for 'vc.camera_info' (7:EIO)
mmal: mmal_component_create_core: could not create component 'vc.camera_info' (7)
Traceback (most recent call last):
  File "manage.py", line 572, in <module>
    meta=args['--meta'])
  File "manage.py", line 100, in drive
    cam = PiCamera(image_w=cfg.IMAGE_W, image_h=cfg.IMAGE_H, image_d=cfg.IMAGE_DEPTH)
  File "/home/twulz/projects/donkeycar/donkeycar/parts/camera.py", line 20, in __init__
    self.camera = PiCamera() #PiCamera gets resolution (height, width)
  File "/usr/lib/python3/dist-packages/picamera/camera.py", line 367, in __init__
    with mo.MMALCameraInfo() as camera_info:
  File "/usr/lib/python3/dist-packages/picamera/mmalobj.py", line 2346, in __init__
    super(MMALCameraInfo, self).__init__()
  File "/usr/lib/python3/dist-packages/picamera/mmalobj.py", line 633, in __init__
    prefix="Failed to create MMAL component %s" % self.component_type)
  File "/usr/lib/python3/dist-packages/picamera/exc.py", line 184, in mmal_check
    raise PiCameraMMALError(status, prefix)
picamera.exc.PiCameraMMALError: Failed to create MMAL component b'vc.camera_info': I/O error
```

**SOLUTION**: I found the solution from [this link][rpi-solution] - I just needed to change the permissions on the `/dev/vcsm` directory:

```sh
(env) $ ls -la /dev/vcsm
crw-rw---- 1 root video 244, 0 Oct 16 10:17 /dev/vcsm
(env) $ sudo chmod ugo+rw- /dev/vcsm
(env) $ ls -la /dev/vcsm
crw-rw-rw- 1 root video 244, 0 Oct 16 10:17 /dev/vcsm
```

## Installing the PS3 Controller

Getting the Ps3 controller working:
follow the instructions here for bluetooth: 

The [ps3 controller instructions][bluetooth] have also been updated and were very straight-forward, the only change I had to make was I needed to use `sudo bluetoothctl` instead, otherwise no devices will show up.

#### Outputs:

```sh
sudo apt-get install bluetooth libbluetooth3 libusb-dev
sudo systemctl enable bluetooth.service
sudo usermod -G bluetooth -a pi
sudo reboot
wget http://www.pabr.org/sixlinux/sixpair.c
gcc -o sixpair sixpair-c -lusb
ls
gcc -o sixpair sixpair.c -lusb
sudo ./sixpair
sudo bluetoothctl
systemctl start hciuart
sudo systemctl start hciuart
ls /dev/input/js0
sudo reboot
```

### Issue: Permission denied on i2c

Next I was getting this error: `PermissionError: [Errno 13] Permission denied: '/dev/i2c-1'` so I needed to add myself to the i2c user group:
```sh
sudo usermod -a -G i2c twulz
exit
```
Log back in

Then the problem was the joystick permissions, so to fix I needed to see what group owns the joystick permissions then add to the 'input' group:
```sh
ls -l /dev/input/js0
sudo usermod -a -G input twulz
exit
```

log back in, then:
```sh
cd mycar/
python manage.py drive --js
```

Success! Now I can go ahead with the training again!

[windows]: https://docs.donkeycar.com/guide/host_pc/setup_windows/
[rpi-solution]: https://www.raspberrypi.org/forums/viewtopic.php?t=247867
[bluetooth]: http://docs.donkeycar.com/parts/controllers/