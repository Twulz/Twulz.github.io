---
layout: project
group: Mechatronics
title: Final Year Projects
posts_title: "Here are the posts I have made about my Final Year Projects:"
category: FYP
breadcrumbs: 
- Things
- Mechatronics
---

I completed two Final Year Projects for my Bachelor of Engineering (Mechatronics) and Computer Science degrees.

![Package Box from my Mechatronics FYP](/images/mechatronicsFYP/10_package_box.jpg)

For Mechatronics I was part of a 3-person team who built a Smart Home system which had the following features:

* A Node.js server running on a Raspberry Pi (Linux).
* A SQL database to record the data also on the server.
* Automated testing on the server using Knex and Mocha.
* Communication with the modules via HTTP and a RESTful API.
* A package box module using ESP32 chips, a MFRC522 RFID reader, a keypad and a 16x2 screen connected using the I2C interface.
* A heating and cooling system implemented mainly by my groupmate which also used an ESP32 with a small fan and cooling pad.
* A garden watering system which actuated an electric water valve implemented by a groupmate.
* A lighting system also implemented by a groupmate.

![Parking Demo Model for my Computer Science FYP](/images/parking/01_parking_setup.jpg)

For Computer Science I was part of a 10-person team who built a Smart Parking solution for a future of Smart Cities to allow people with disabilities to find, book and use car parking. I was on the back-end team and also implemented the hardware demo. The overall system had the following features:

* A Node.js server.
* A SQL database.
* Automated testing with Knex and Mocha which integrated with Jenkins for a CI/CD pipeline.
* An Android app which communicated with the server using a RESTful API.
* An Angular web interface which also used the RESTful API allowing the configuration of the system.
* A hardware demo using ESP32s and small 9g servo motors to demonstrate the functionality of the whole system (...using Lego cars!).