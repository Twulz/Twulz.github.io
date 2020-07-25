---
layout: post
title:  "Building a Smart Parking Demo Model"
date:   2018-10-10
categories: Things Mechatronics FYP
tags: SmartParking ESP32 NodeMCU NodeJs
related_image: 
  path: /images/parking/01_parking_setup.jpg
  alt: Smart Parking Setup
---

A summary of building a model of the future vision for the _Smart Parking for Smart Cities_ project I was a part of for my Computer Science final year project that we presented at the Capstone Expo (CapEx) at Swinburne.

<!--more-->

# Introduction

In [my last blog post]({{ site.baseurl }}{% post_url 2018-09-18-Building-a-smart-parking-server %}) I was part of the team creating the server to be used by the Smart Parking app. I was then tasked with creating a hardware demo model to demonstrate the different stages of the parking app with whatever hardware I could mock up to get the idea across. Check out that post for more details on the overview of the project.

So I decided to use ESP32s to be the brains of the spaces as they could easily connect to WiFi to send HTTP requests to the Node.js server we created. These could also easily control small 9g servo motors to act as the "bollards" that raise/lower depending on the proximity of the cars and/or the booking status of the space. ESP32s can also directly interface with a MFRC522 RFID reader at 3.3V so this could be use to detect the cars... and obviously a few LEDs just to show what was going on behind the scenes.

The design was based around the four stages described in [this post]({{ site.baseurl }}{% post_url 2018-09-18-Building-a-smart-parking-server %}) , but here is a quick run-down:

1.	**Stage 1 - Searching for a space: Ready for real-world.**
2.	**Stage 2 – Booking a space: Ready for real-world.**
3.	**Stage 3 – Blocking unauthorised access:**
4.	**Stage 4 – Dynamically allocated spaces:**

# Hardware Design

![Lego Cars](/images/parking/08_lego_cars.jpg)

Next I needed some 'cars' - I initially wanted to use matchbox cars but they were slightly too small for the passive RFID tags. So I made use of a few lego cars I had just laying on my shelves (...actually a car and a digger...) that I just taped some RFID tags to the bottom - hey, if it works!

![Display](/images/parking/05_lego_cars.jpg)

This gave me the scale for the rest of the demo. I used some MDF as the base with 3D printed control panels that would be used to indicate the state of each of the spaces (in real life these wouldn't exist). I could also cut holes in the base to allow for the bollards to raise and lower. I designed it all in solidworks first.

![Hardware demo designed in Solidworks](/images/parking/09_solidworks.jpg)

Two of the spaces used the standard control plate which are permanent permit-only spaces. The _Booked Now_ space lights up when the space is booked at this time and the _Correctly Parked_ LEDs are green and red indicating if the car parked in the space is the one that booked it (green) or should not be parked there (red).

![Standard control plate](/images/parking/10_standard_control_plate.jpg)

The third park is a variable space which only becomes permit-only when the first two spaces are taken. The centre disabled symbol indicates its status. It then behaves the same as the first spaces' control plate.

![Variable control plate](/images/parking/11_variable_control_plate.jpg)

The control plate stand was designed to be printed separately so there would be no overhangs (and therefore supports) required to 3D print.

![Control plate stand](/images/parking/12_control_plate_stand.jpg)

![Sliced plate](/images/parking/14_sliced.jpg)

![3D Printed Parking sign](/images/parking/02_parking_signs.jpg)

![3D Printed Variable Parking Sign](/images/parking/03_disabled_sign.jpg)

The bollards were designed to slip over and be glued to the 9g servo motor arm.

![Bollard](/images/parking/13_bollard.jpg)

![Complete hardware demo](/images/parking/07_hardware_demo_complete.jpg)

# Electronics Design

Here is the design for the electronics - each park would have its own ESP32 (NodeMCU) connected to the MFRC522 and LEDs for that space. The bollards were all attached to the fourth ESP32 and RFID reader which would raise/lower the correct bollard independently for stage 3.

![Mounting locations](/images/parking/16_mounting_locations.jpg)

![Wiring Diagram](/images/parking/15_wiring_diagram.jpg)

In terms of the logic, here is the flowchart for spaces 1 and 2:

![Flowchart for spaces 1 & 2](/images/parking/17_flowchart_spaces_1_2.jpg)

Also for space 3:

![Flowchart for space 3](/images/parking/18_flowchart_space_3.jpg)

And finally for the bollards:

![Flowchart for the bollard](/images/parking/19_flowchart_bollard.jpg)

# Final Presentation

I forgot to take a normal picture of the display so here's a fantastic screenshot from my Snapchat story - I do apologise! It was a big hit as all the other Computer Science projects were on PC/Phones only.

![Parking](/images/parking/04_parking_display.jpg)

# Working Model

Here are a few videos of the stages working!

## Stage 1 & 2 - Booking & Parking in a Space

<center>
    <video width="960" height="540" controls muted>
        <source src="{{ site.baseurl }}/images/parking/01_stage_1_2.mp4" type="video/mp4">
        Parking Stages 1 and 2
    </video>
</center>

## Stage 3 - Bollards

<center>
    <video width="960" height="540" controls muted>
        <source src="{{ site.baseurl }}/images/parking/02_stage_3.mp4" type="video/mp4">
        Parking Stage 3
    </video>
</center>

## Stage 4 - Variable Permit Parking

<center>
    <video width="960" height="540" controls muted>
        <source src="{{ site.baseurl }}/images/parking/03_parking_stage_4.mp4" type="video/mp4">
        Parking Stage 4
    </video>
</center>