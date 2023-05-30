<h1> :earth_asia:  Persistence of Vision (POV) Display  :earth_asia: </h1>

<h1> Team Members </h1>
- Didi Kamalova <br>
- Naomi Mo <br>
- Aanya Tashfeen <br>

<h1> Project Description </h1>
We created a spherical persistence of vision (POV) LED Display that works by spinning a circular array of LEDs and relies on our eyes' natural “refresh rates” to create the illusion of a solid image on a sphere. Equipped with an LED strip, a hall sensor, 3 battery packs and framed in a desk fan, it creates patterns upon reacting to magnets spaced out across the circular base.

<h1> Member Contribution </h1>
- Aanya: graphics code, 3D modeling, .... <br>
- Didi: led driver code, soldering, cable management, hardware sourcing <br>
- Naomi: hall sensor code, graphics code, hardware assembly and troubleshooting <br>

<h1> References </h1>
- POV Globe <a href="https://www.youtube.com/watch?v=E4yqSw38R_Q&t=178s](https://youtu.be/E4yqSw38R_Q">Video</a> and <a href="https://github.com/rottaca/PovGlobe.git">GitHub Repository</a> <br>
- SPI module code by <a href="https://github.com/cs107e/cs107e.github.io/blob/25d6d0b08f8accd1bdcaf4e400c9574a3f2c0dcf/lectures/Sensors/code/arducam/spi.c">Arducam</a> <br>
- Pat's hall effect sensor code <br>

<h1> Self-Evaluation </h1>
<p> We created a fully functioning prototype of a spherical LED Display that allows for free spinning, coded an LED strip driver, integrated hall sensor interrupts and successfully projected a soccerball pattern on the sphere. While we have not been able to project a spherical image of the globe as was initally planned, we were able to complete all other goals that we have set for this project! </p>

One of the most memorable moments of this past week is definitely the moment we stumbled upon an interesting bug: the motor on our fan was generating a magnetic field which would induce current interfering with our circuitry, displaying weird artifacts and an undefined behavior on the strip. In attempts to block/redirect the magnetic field, we created a shield made out of thin stainless steel plates layered onto one another. However, this ended up trapping the heat and ultimately overheated the motor, making it no longer functionable... at 12:30AM, the night before the demo. Thankfully, we were able to find a different fan (shoutout to Frances!) to reinstall our ring onto a new fan 15 minutes before the demo session.

<p align="center">
  <img src="media/IMG_8513.jpg" title="LED Display" width = "500">
</p>
<p align="center">
  <img src="media/IMG_1285.JPG" title="LED Display" width = "250">
  <img src="media/IMG_8415.jpg" title="LED Display" width = "250">
  <img src="media/IMG_8499.jpg" title="LED Display" width = "250">
</p>


More images provided in the "media" folder!

NOTE ABOUT CODE ORGANIZATION:
The simple code that we ran during demo day is under main, but more intricate implementations involving round trip time and displaying image arrays (the globe, soccer ball, and checkerboard) are under globe.c and RTTmeasure.c. We unfortunately did not get these to be fully optimized and integrated by the end of the project deadline, although we made the soccer ball display operational after our demonstration.
