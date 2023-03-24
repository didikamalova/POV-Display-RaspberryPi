## Project Title
Persistence of Vision (POV) Display

## Team Members
Didi Kamalova

Naomi Mo

Aanya Tashfeen

## Project Description
We created a spherical persistence of vision (POV) LED Display that works by spinning a circular array of LEDs and relies on our eyes' natural “refresh rates” to create the illusion of a solid image on a sphere. Equipped with an LED strip, a hall sensor, 3 battery packs and framed with a desk fan, it creates patterns upon reacting to magnets spaced out across the circular base of the fan.

## Member contribution
Aanya: graphics code, 3D modeling


Didi: led driver code, soldering & cable management


Naomi: hall sensor code, mechanical assembly

## References
POV Globe Video and GitHub Repo: https://www.youtube.com/watch?v=E4yqSw38R_Q&t=178s

Julie's LED strip driver code and Pat's hall effect sensor code


Math libraries from CS107E Repo

## Self-evaluation
We created a fully functioning prototype of a spherical LED Display that allows for free spinning, coded up an LED Strip driver, successfully integrated hall sensor interrupts and created a soccerball pattern on the sphere. While we have not been able to project a spherical image of the globe as initally planned, we were able to complete all other goals that we have set for this project. 

One of the most memorable moments of this past week is definitely the moment when we stumbled upon an interesting bug: the motor on our fan was generating a magnetic field which would induce current interfering with our circuitry, thus displaying weird artifacts and undefined behavior on the strip. In attempts to block/redirect the magnetic field, we created a shield made out of thin stainless steel plates layered onto one another. However, this ended up trapping the heat and ultimately overheated the motor, making it no longer functionable - at 12:30AM, the night before the demo. Thankfully, we were able to find a different fan (shoutout to Frances!) to reinstall our ring onto a new fan 15 minutes before the demo session.


## Photos
Photos provided in the media folder!

