---
layout: post
title:  "Fixing old Dell screens"
date:   2017-04-21
categories: fix tester
tags: fix dell screen
---

I have two Dell screens that started to have the flashing power button fault, which after a little googling seems to generally be caused by one or more of a group of 4 transistors on the board that may be faulty. In this post I built a transistor/capacitor tester kit I got from banggood.com and used it to test these transistors as I replaced them to fix the screens.
 
<!--more-->

![Banggood Transistor Checker](/images/screenFix/set_contents.jpg)
 
I initially started this project a few months ago but after taking one of the screens apart I discovered my beloved Amprobe X38-R Multimeter was missing in action. I was heartbroken. I tore my house apart looking for it, last seen last year when making my shitty robot for one of my classes but I had to come to terms with the fact that it was gone. So naturally after deciding I’d buy the OTHER model I was considering those years ago as a replacement (Amprobe X37-R) I went on a bit of a shopping spree on banggood.com and aliexpress.com to stock up my random electronics supply too. I got a number of assorted kits of capacitors, transistors, inductors, timers, op amps, logic chips, header connectors and wires; I needed a lot of retail therapy. Along with these, I decided to try out this $20 transistor tester that I’d found online and to have as an extra project.

![Soldering with my Helping Hands](/images/screenFix/solder_helping_hands.jpg)
 
So 4-6 weeks later, most of my shopping spree had arrived, along with my multimeter so I got to work putting together the transistor tester. There were no explicit instructions but the board is well-labelled.

![Soldering the board](/images/screenFix/board01.jpg)
![Soldering the board](/images/screenFix/board02.jpg)
![Soldering the board](/images/screenFix/board03.jpg)
![Soldering the board](/images/screenFix/board04.jpg)
 
I did make one big error with the test input region. This same board is used for projects without an enclosure also so I just went along and soldered the other test input straight onto the board, not realising it had the option for this OR you could fit it into the enclosure. This mistake cost me a quick trip to JayCar to replenish my solder braid and sucker collection as this guy just did not want to come off! 

![Soldering the front panel](/images/screenFix/front_panel_soldering.jpg)

After removing this part I could fit the board inside the case and connect up the inputs that were mounted on the outside of the case. This was a little fiddly as the wires from the inputs were freestanding and all had to be inserted correctly before soldering but then it was time to test this baby out!

![Broken Transistors](/images/screenFix/broken_transistors01.jpg)
![Broken Transistors](/images/screenFix/broken_transistors02.jpg)
 
I took apart the screens and de-soldered each of the suspected transistors. I had bought replacements for all of them in my shopping spree so I did end up just replacing them all for good measure, but there was one transistor for each screen that did not read properly on my new tester.