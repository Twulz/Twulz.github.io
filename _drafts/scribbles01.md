The day finally came last Tuesday the 22nd of August; the Dark Souls Board Game by Steamforged games arrived at my door!

I realised when the game arrived that I hadn't even gotten close to finishing my zombicide figures as this particular hobby had fallen by the wayside but I am confident the practise I had with these figures will be invaluable now that I'll be painting the main event.

The Dark Souls Board Game (DSBG) is coming in two waves - the first wave contains only the base game whereas the wave two shipment will contain all of the stretch goals and add-ons. This was great news as I could really focus my efforts on painting the first set of figures without being overwhelmed like I have been with Zombicide.

Over the past few months I've kept an eye on my Local Game Stores (LGS) for deals and sales they have had on paints. After using the Army Painter paint sets for Zombicide I decided for Dark Souls I was going to use the Citadel paint range for these minis. I did enjoy using Army Painter however their line isn't available at my favourite LGS and they are more celebrated for their range for use on planes, ships and the like. Citadel are considered a 'premium' brand and are recommended to experts and beginners alike for their fantastic quality. I also joined a Facebook group for the other DSBG backers and many others have used Citadel paints on their models and shared their colour choices which also made paint selection much easier.

In the end I ended up with quite the Citadel Paint collection [ALICIA]; I certainly think that you can definitely paint these models with less standard paint colours and instead try mixing your own colours. I didn't go for that option simply because there's such a number of models to paint and I wanted to try experimenting... also I may have got carried away in the sales!





So this week the ceiling light over my desk has decided to break any globe I stuck in there so the obvious solution I came up with while waiting for the tradies to come round was to hook up my LED strip to light up my desk. That is the obvious solution yeah?

I bought this 5m WS1121B [ALICIA] LED strip a while ago on one of my AliExpress shopping sprees and had never played with it. I was initially concerned with the power requirements and concern with accidentally lighting the whole thing up to white light, drawing too much current and blowing up the power supply (I'm not sure how unlikely that is...). But after cleaning out my box of cords and old tech I found that I had a 5V power supply that could supply up to 8A (yes EIGHT AMPS) so I thought my chances of blowing something up were quite slim.

I did need to purchase an adapter 2.5mm DC Socket with Screw Terminals adapter from JayCar [ALICIA link] to go with my power supply but then I was ready to go!

I followed the Adafruit WS [ALICIA and LINK] guide to hook up the LED strip. I wish I'd realised while I was worrying about power supply ratings that for these LED strips (as opposed to the RGB ones) that you can specify the number of LEDs to use in the strip object so as to keep the power requirements down at least until I understood how to use the strips.

In using the hookup guide I made sure to apply a 1000uF capacitor across the power supply terminals to minimise the impact of a sudden voltage spike and also used a 470 Ohm resistor between the Data line on the strip and the Arduino pin.

From there I ran the example code from the Adafruit guide and marvelled at my great new desk light!