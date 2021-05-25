# 3d-solarsystem
<p> Modify your solar system with the following <br>
o Set up SOIL as Instructed <br>
o Without using glutSolidSphere() to create planets use the following<br>
GLUquadricObj *sphere= NULL; // global variouble<br>
gluSphere(sphere,3.0, 40,40); //in display<br>
 For the texture settings<br>
o Follow the instructions on Texture setup and implement the texture code to
framework<br>
o Apply images of your liking to the planets<br>
v Speeds of rotation and orbits<br>
o Replace all glRotated() with quaternions <br>
Make you simulation start once UP_KEY pressed
</p>
