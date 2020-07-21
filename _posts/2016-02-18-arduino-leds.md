---
layout: post
title:  "Playing with Arduino LEDs"
date:   2016-02-18
categories: Things Mechatronics OtherMecha
tags: Arduino LED
---

I have previously played with Arduino projects, today I decided to play around with some LEDs and re-familiarise myself with the platform.

<!--more-->

## Setting up the board
As it has been a while since I last played with an Arduino, I had to reinstall the software.
This is as simple as the following from the official Arduino site: 

1. Heading over to the [instructions page](https://www.arduino.cc/en/Guide/Windows), 
2. Downloading and installing the software, 
3. Loading up the 'Blink' example (the hardware equivalent of 'Hello World!'), 
4. Configuring the board type 
5. Ensuring the correct port is selected and
6. Testing the program.

## Pulsing LEDs
I've been asked by a friend to help out with lighting up a future cosplay of hers so I connected up a few LEDs to get a feel for what kind of effects that were possible and what she was after.

Starting with this great [SparkFun][sparkfun] link, turns out using PWM to pulse and LED is super simple so I quickly expanded to use 4 LEDs fading at equal intervals:

``` C
const int LED1 = 11;
const int LED2 = 10;
const int LED3 = 9;
const int LED4 = 6;

void setup()
{
}

void loop()
{
  float in, out;
  
  for (in = 0; in < 6.283; in = in + 0.001)
  {
    out = cos(in) * 127.5 + 127.5;
    analogWrite(LED1,out);
    out = cos(in+1.5708) * 127.5 + 127.5;
    analogWrite(LED2,out);
    out = cos(in+3.1415) * 127.5 + 127.5;
    analogWrite(LED3,out);
    out = cos(in+4.7124) * 127.5 + 127.5;
    analogWrite(LED4,out);
  }
}
```


[sparkfun]: 		https://www.sparkfun.com/tutorials/329
[ws2812-guide]:		https://learn.sparkfun.com/tutorials/ws2812-breakout-hookup-guide
[digital-leds]:		https://learn.adafruit.com/digital-led-strip/overview
[analog-leds]:		https://learn.adafruit.com/rgb-led-strips/
[analog-blog-leds]:	http://www.jerome-bernard.com/blog/2013/01/12/rgb-led-strip-controlled-by-an-arduino/
[Neopixels]:		https://learn.adafruit.com/adafruit-neopixel-uberguide/overview

[my-leds]:			http://www.aliexpress.com/item/1m-4m-5m-WS2812B-Smart-led-pixel-strip-Black-White-PCB-30-60-144-leds-m/2036819167.html?smToken=82b40931e4c54a4086c7f55a8d734b6e&smSign=oEl3GazTf43bYwco81HOGw%3D%3D

[highPowerControl]:	http://bildr.org/2012/03/rfp30n06le-arduino/ 