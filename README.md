# 3d-solarsystem
v Modify your solar system with the following
o Set up SOIL as Instructed
o Without using glutSolidSphere() to create planets use the following
GLUquadricObj *sphere= NULL; // global variouble
gluSphere(sphere,3.0, 40,40); //in display
v For the texture settings
o Follow the instructions on Texture setup and implement the texture code to
framework
o Apply images of your liking to the planets
v Speeds of rotation and orbits
o Replace all glRotated() with quaternions (Follow the implementation
on lecture notes)
v Make you simulation start once UP_KEY pressed

