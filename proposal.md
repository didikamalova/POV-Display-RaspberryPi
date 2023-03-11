## Title:
Persistence of Vision (POV) Display

## Team Members:
Naomi Mo
Didi Kamalova
Aanya Tashfeen

## Project Description:
We want to create a spherical persistence of vision (POV) LED Display. 

Our goal is to create a fully functinoning LED Display that works by spinning a circular array of LEDs and relies on our eyes' natural “refresh
rates” to create the illusion of a solid image on a sphere.

We want to be able to display fun patterns (disco ball, for example) on it. If that works, we want to try encoding an image of the globe on our display and/or adding peripherals to it.

## Hardware & Budget:
Required hardware:
- x1 A3134 Hall Effect Sensor - Pat
- x8 Neodymium Magnets - Pat
- x2 AdaFruit DotStar LED strip 144 LED/m 0.5m - lab64
- x1 3AA Battery Pack - lab64
- x10 M4, M5 bolts & nuts - lab64/room 36
- x5 3D Printed Parts - lab64
- x1 ~200x200x20mm Steel/Wood Base Plate - lab64/room 36 wood scraps
- x1 2000-3000RPM DC Motor (4mm) - Stanford Robotics Lab/Aanya's Fan
- x1 6.3mm aluminum/steel rod - Room 36
- x1 (^) DC Motor Adapter (5mm to 6mm) - Stanford Robotics Lab
- x1 Ball Bearing - Stanford Robotics Lab/Room 36
- x1 Power Supply (for testing purposes) - lab64

(^) - items we're still searching for and may need to purchase elsewhere.
Rough Budget: $50-60 for components we won't be able to find.

## Tasks & Member Responsibilities:
Our project will be divided into the following categories:
Software: graphics module (gl_draw() functions), hall sensor driver, led driver, implementing interrupts throughout
Electrical: circuit schematics, power management, soldering.
Mechanical: ring, frame, motor, cable management, assembly.

Division of tasks (not final):

Aanya: mechanical assembly, math for graphics

Didi: led setup, circuits, hardware sourcing, mechanical assembly

Naomi: hall sensors setup, mechanical assembly

## Schedule & Midpoint Milestones:
By the end of the upcoming weekend, we want our entire mechanical assembly in place. By the end of the following weekend, we want a working sphere 
with a functional LED display. 

## Resources Needed & Issues:
Our possible concerns include mechanical/electrical assembly problems that we may run into, such as rotating wires getting tangled up, poor electrical power trasmission, lack of frame stability, extra motor vibrations  and lack of battery capacity.

In the event we encounter issues with the 3D display, we plan on working on a 2D LED display instead.

Resources: POV globe video and github repo: https://www.youtube.com/watch?v=E4yqSw38R_Q&t=178s
		   Julie's LED strip driver code and Pat's hall effect sensor code
		   Math libraries from cs 107e repo
