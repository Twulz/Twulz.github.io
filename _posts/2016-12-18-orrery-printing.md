---
layout: post
title:  "Building an Orrery: Printing the Parts"
date:   2016-12-18
categories: Things Mechatronics Orrery
tags: 3DPrint Orrery Build
related_image: 
  path: /images/orrery/finished_01.jpg
  alt: Almost finished Orrery
---

An Orrery is a mechanical model of the Solar System where the planets orbit around the Sun with a combination of gears allowing for relative motion between the sun and planets. I found a great tutorial on a 3D printed version that I could make as a present for my Dad.

The build guide comes from [Ytec3d's guide][Orrery] which links to the [instructible][instructible] he wrote, be sure to check it out and support this amazing maker.

<!--more-->

This one was actually a present for my Dad for Christmas, but due to some items being lost in the post I wasn't able to finish the motorised version for him for Christmas, but it was enough to get the idea! (See the pic above).

My dad is quite passionate about stargazing and so I'd long been looking for an Orrery I could give to him but most were very high-end machined, handmade, very beautiful and also very expensive models that I'm sure he would absolutely love, but were well out of my student's price range. I was also interested in potentially buying a kit or otherwise making it myself but there are limited resources for this I'd found, especially as I was after an orrery with at least some attempt to keep the speed of the orbits of each of the planet relatively correct - if not just approximate. The breakthrough happened when I was searching for other new projects to attempt with my newly built 3D printer. Yvo de Haas on his site [Ytec 3D][Ytec3d] built a fantastic model of [GLaDOS][GLaDOS]; the main villian from one of my all-time favourite games: *Portal*. That one went straight on the to-make list (standby for the build log, probably years in the future!). I also saw he had made a [3D printable orrery][Orrery] complete with gears which allowed the planets from Mercury to Saturn to orbit at different speeds and I jumped straight on the build wagon.

# Printing!

![Printing the Gears](/images/orrery/06_printing_gears.jpg)

This was my first big project using my 3D printer so there were a number of false-starts. I chose to print the majority of the parts in PLA as I hadn't started playing with ABS and my PLA prints were turning out very nicely. I chose black for the main body including all the gears and white for the planets. I split the print into I think 15 different prints so as to maximise the use of the bed which was especially useful for the smaller pieces which benefit from being allowed to cool slightly more before printing the next layer if there are multiple parts on the bed. I only had two failures and had to reprint the Moon and Mercury but otherwise the printing process went smoothly.

![Printing the Sun](/images/orrery/05_printing_sun.jpg)

I also ran the straight line (z-height) and cubes calibration print a few times to properly level the bed before printing, as I was planning to print multiple parts at once it was important that the bed was properly calibrated.

![Calibration Line](/images/orrery/01_calibration.jpg)

![Calibration Cubes](/images/orrery/03_calibration.jpg)

![Calibration Cubes](/images/orrery/04_calibration.jpg)

The following table shows how I split up the prints on my Official Prusa i3 MK2, those without the time were grouped with those parts above them in the table. The total print time was 22 hours 14 minutes, not including false starts and the few failed parts. Unfortunately I don't know what happened to my photos!! So I'll make up for that in the next post, have some tabley-goodness instead:

## Printed Parts list

|Item|     Part Number      |       Description       |Qty | Hr|Min |
|----|----------------------|-------------------------|----|---|----|
| 8  | SS orrery Y10-P02-00 | Sun bearing holder      | 1  | 0 | 23 |
| 9  | SS orrery Y10-P03-00 | Base body               | 1  | 4 | 37 |
| 10 | SS orrery Y10-P04-00 | Base Leg                | 5  | 3 | 32 |
| 11 | SS orrery Y10-P05-00 | Motor mount             | 1  | 0 | 13 |
| 12 | SS orrery Y10-P06-00 | Motor driver gear       | 1  | 1 | 31 |
| 13 | SS orrery Y10-P07-00 | Motor driven gear       | 1  |   |    |
| 14 | SS orrery Y20-P02-00 | Sun Mercury gear 1      | 1  |   |    |
| 15 | SS orrery Y20-P03-00 | Sun Mercury gear 2      | 1  |   |    |
| 16 | SS orrery Y20-P04-00 | Sun Mercury gear 3      | 1  |   |    |
| 17 | SS orrery Y20-P05-00 | Sun Mercury gear 4      | 1  |   |    |
| 19 | SS orrery Y20-P08-00 | Mercury Venus gear 1    | 1  | 1 | 04 |
| 20 | SS orrery Y20-P09-00 | Mercury Venus gear 2    | 1  |   |    |
| 21 | SS orrery Y20-P10-00 | Mercury Venus gear 3    | 1  |   |    |
| 22 | SS orrery Y20-P11-00 | Venus Earth gear 1      | 1  |   |    |
| 18 | SS orrery Y20-P07-00 | Gear arm Mercury Venus  | 1  | 1 | 5  |
| 23 | SS orrery Y20-P12-00 | Gear arm Venus Earth    | 1  |   |    |
| 24 | SS orrery Y20-P13-00 | Venus Earth gear 2      | 1  |   |    |
| 25 | SS orrery Y20-P14-00 | Venus Earth gear 3      | 1  |   |    |
| 26 | SS orrery Y20-P15-00 | Gear arm Earth Mars     | 1  |   |    |
| 27 | SS orrery Y20-P16-00 | Earth Mars gear 1       | 1  | 1 | 27 |
| 28 | SS orrery Y20-P17-00 | Earth Mars gear 2       | 1  |   |    |
| 29 | SS orrery Y20-P18-00 | Earth Mars gear 3       | 1  |   |    |
| 31 | SS orrery Y20-P20-00 | Mars Jupiter gear 1     | 1  |   |    |
| 32 | SS orrery Y20-P21-00 | Mars Jupiter gear 2     | 1  |   |    |
| 33 | SS orrery Y20-P22-00 | Mars Jupiter gear 3     | 1  |   |    |
| 30 | SS orrery Y20-P19-00 | Gear arm Mars Jupiter   | 1  | 0 | 26 |
| 34 | SS orrery Y20-P23-00 | Gear arm Jupiter Saturn | 1  |   |    |
| 35 | SS orrery Y20-P24-00  | Jupiter Saturn gear 1  | 1  | 1 | 34 |
| 36 | SS orrery Y20-P25-00  | Jupiter Saturn gear 2  | 1  |   |    |
| 37 | SS orrery Y20-P26-00  | Jupiter Saturn gear 3  | 1  |   |    |
| 40 | SS orrery Y30-P01-00  | Mercury                | 1  | 2 | 1  |
| 41 | SS orrery Y30-P02-00  | Venus                  | 1  |   |    |
| 42 | SS orrery Y30-P03-00  | Earth                  | 1  |   |    |
| 43 | SS orrery Y30-P04-00  | Mars                   | 1  |   |    |
| 44 | SS orrery Y30-P05A-00 | Jupiter                | 1  |   |    |
| 45 | SS orrery Y30-P05B-00 | Jupiter                | 1  |   |    |
| 46 | SS orrery Y30-P06A-01 | Saturn                 | 1  |   |    |
| 47 | SS orrery Y30-P06B-01 | Saturn                 | 1  |   |    |
| 61 | SS orrery Y50-P05-00  | Mercury                | 1  |   |    |
| 54 | SS orrery Y40-P01A-00 | Sun                    | 1  | 1 | 57 |
| 55 | SS orrery Y40-P01B-00 | Sun                    | 1  |   |    |
| 58 | SS orrery Y50-P02-00  | Moon gear fragment     | 4  | 1 | 54 |
| 60 | SS orrery Y50-P04-00  | Moon pinion            | 1  |   |    |
| 59 | SS orrery Y50-P03-00  | Post                   | 4  | 0 | 30 |
| 63 | SS orrery Y50-P07-00  | Stopper                | 1  |   |    |

## Non-printed Parts

The following parts were also required in the build, but were not 3D printed.


|Item|     Part Number       |       Description      |Qty |
|----|-----------------------|------------------------|----|
| 1  | 624 bearing           |                        | 1  |
| 2  | 683 bearing           |                        | 14 |
| 3  | 684 bearing           |                        | 1  |
| 4  | 688 bearing           |                        | 11 |
| 5  | DC gear motor 12dia   |                        | 1  |
| 6  | Slipring              |                        | 1  |
| 7  | SS orrery Y10-P01-00  | Base tube              | 1  |
| 38 | SS orrery Y20-P35-00  | Gear shaft 1           | 5  |
| 39 | SS orrery Y20-P36-00  | Gear shaft 2           | 1  |
| 48 | SS orrery Y30-P09-00  | Mercury carrier        | 1  |
| 49 | SS orrery Y30-P10-00  | Venus carrier          | 1  |
| 50 | SS orrery Y30-P11-00  | Earth carrier          | 1  |
| 51 | SS orrery Y30-P12-00  | Mars carrier           | 1  |
| 52 | SS orrery Y30-P13-00  | Jupiter carrier        | 1  |
| 53 | SS orrery Y30-P14-00  | Saturn carrier         | 1  |
| 56 | SS orrery Y40-P02-00  | Sun shaft              | 1  |
| 57 | SS orrery Y50-P01-00  | Moon gear arm          | 4  |
| 62 | SS orrery Y50-P06-00  | Moon arm               | 1  |

[GLaDOS]: http://ytec3d.com/glados-lamp/
[Orrery]: http://ytec3d.com/orrery/
[Ytec3d]: https://ytec3d.com/
[instructible]: http://www.instructables.com/id/Solar-System-Orrery-3D-Printed/