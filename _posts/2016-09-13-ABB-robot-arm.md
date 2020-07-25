---
layout: post
title:  "Programming an ABB Robot Arm"
date:   2016-09-13
categories: Things Mechatronics OtherMecha
tags: Robot ABB PickAndPlace
related_image: 
  path: /images/abb/01_full_setup.jpg
  alt: Full setup
---

Here is a quick post on one of my projects I'm working on at uni programming an ABB branded robot arm using the Flexpendant controller.

<!--more-->

At uni I have a project currently to program a pick-and-place robot to identify a number of objects and move them to another defined place based upon some characteristic. I am in a group of three working on this project and I took the lead on programming the robot behaviour itself, another teammate worked on the image processing and the last teammate worked on the interface between the two.

Here is the starting position we decided upon, the robot will identify which coloured block is present in which position and will move the block to its corresponding colour on the left.

![The starting position](/images/abb/02_starting_position.jpg)

This is the finishing position. The robot paths are programmed using the Flexpendant (which is the hand-held controller of this ABB robot).

![Finishing position](/images/abb/03_finishing_position.jpg)

The robot starts in the centre position, picks up the first block and moves it to the centre position. This block's colour was previously identified using the webcam mounted above the setup so when the centre position has been reached it moves over to the right spot on the podium. Then it moves onto the next block and so on.

![Finishing blocks](/images/abb/04_finishing_position.jpg)

The following is a demo of the working program, notice the image from the webcam on the right identifying the colours and the robot operating.

<center>
    <video width="960" height="540" controls muted>
        <source src="{{ site.baseurl }}/images/abb/pick_and_place.mp4" type="video/mp4">
        Final Video
    </video>
</center>