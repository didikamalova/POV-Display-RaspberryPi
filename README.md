<h1> :earth_asia:  Persistence of Vision (POV) Display  :earth_asia: </h1>

<h1> Team Members </h1>
- Didi Kamalova <br>
- Naomi Mo <br>
- Aanya Tashfeen <br>

<h1> Project Description </h1>
We created a spherical persistence of vision (POV) LED Display that works by spinning a circular array of LEDs and relies on our eyes' natural “refresh rates” to create the illusion of a solid image on a sphere. Equipped with an LED strip, a hall sensor, 3 battery packs and framed with a desk fan, it creates patterns upon reacting to magnets spaced out across the circular base of the fan.

<h1> Member Contribution </h1>
- Aanya: graphics code, 3D modeling, .... <br>
- Didi: led driver code, soldering, cable management <br>
- Naomi: hall sensor code, graphics code, .... <br>

<h1> References </h1>
- POV Globe Video and GitHub Repo: https://www.youtube.com/watch?v=E4yqSw38R_Q&t=178s <br>
- Julie's LED strip driver code <br>
- Pat's hall effect sensor code <br>
- Math libraries from CS107E Repo <br>

<h1> Self-Evaluation </h1>
<p> We created a fully functioning prototype of a spherical LED Display that allows for free spinning, coded an LED strip driver, integrated hall sensor interrupts and successfully projected a soccerball pattern on the sphere. While we have not been able to project a spherical image of the globe as was initally planned, we were able to complete all other goals that we have set for this project! </p>

One of the most memorable moments of this past week is definitely the moment when we stumbled upon an interesting bug: the motor on our fan was generating a magnetic field which would induce current interfering with our circuitry, displaying weird artifacts and an undefined behavior on the strip. In attempts to block/redirect the magnetic field, we created a shield made out of thin stainless steel plates layered onto one another. However, this ended up trapping the heat and ultimately overheated the motor, making it no longer functionable... at 12:30AM, the night before the demo. Thankfully, we were able to find a different fan (shoutout to Frances!) to reinstall our ring onto a new fan 15 minutes before the demo session.


**Aanya**: ... 


**Didi**: Understanding how to drive an LED strip was not trivial; however, I felt comfortable navigating the datasheet for the APA10 communication protocols in the absense of reliable information! What helped me the most was using the logic analyzer to debug and experiment with data frames bit by bit (one of many useful skills learned in class!). I'm also happy with the electrical assembly of the display! I focused on placing our wires and circuit components in way that would look neat & help wires remain static during the rotation of the ring - mission accomplished!


**Naomi**: ...

<p align="center">
  <img src="media/IMG_8513.jpg" title="LED Display" width = "500">
</p>
<p align="center">
  <img src="media/IMG_1285.JPG" title="LED Display" width = "300">
  <img src="media/IMG_8415.jpg" title="LED Display" width = "300">
  <img src="media/IMG_8499.jpg" title="LED Display" width = "300">
</p>


More images provided in the "media" folder!
