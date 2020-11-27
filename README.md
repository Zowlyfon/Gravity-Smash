# Gravity Smash

Gravity smash is a seemingly simple game where the player
must smash into smaller objects in order to gain mass,
however if they collide with something larger than themselves
will die and respawn with half their mass.

The player will start off as an asteroid, floating around 
with other asteroids, as they gain mass their asteroid
will become more spherical, due to the force of it's own
gravity.
 
Eventually, when the player becomes a full sphere, they 
will become a dwarf planet. Dwarf planets regularly receive
impacts from asteroids due to their attractive mass,
and will be covered in craters.

Once the player has accumilated enough mass, they will find
that an atmosphere will start to form around them, and may
be able to sustain liquid water and possibly even life!

As the player's planet get's even bigger, the atmosphere will
thicken and the planet will become a gas giant!

If a gas giant gains enough mass, it will eventually become
a star, which is where this game ends.

## Development

My development ethos has been to start with the most
essential features first. To that end I started by rendering
a triangle to the screen, then turning that triangle into 
a spinning cube, and then into a sphere.

Once I had my sphere it was time to add some gravity.
I implemented this using a naive n-body simulation, using
formula that I learned during my A-Level physics.

Although the algorithm has an O(n<sup>2</sup>) complexity,
it is much easier to parallelise than the more efficient
variants. I found that my Ryzen 3700X CPU could run around
300 - 400 particles on a single thread, and around 1200
when utilising all of my threads.

Using this data, I decided that the maximum number physical
objects in my game should be set to around 500, as this
will leave plenty of room for other calculations and
allow it to run on older machines.

Next I added collisions, because the objects are all spheres,
collision detection is extremely simple. I then gave my
objects mass and added this into my collision algorithm.

As objects gain mass, they need to grow in size. I started
doing this linearly, however this is not realistic.
I approximated how this would really work by making an
objects radius the cube root of it's mass divided by pi.

Now I have objects that can collide with each other
and exchange mass, I started making my spheres look
more like asteroids. To do this I added into my vertex
shader some fractal simplex noise, and changed the
weightings of each octave to produce a nice looking asteroid.

Then to calculate the new normals, I added a geometry shader
which calculates the normal for each triangle. Unfortunately
this meant that the objects were flat shaded, as a geometry
shader is unable to calculate the normals per vertex.

To overcome this I created a compute shader that added the 
noise to the vertices before they were rendered, then
pre-calculated the normals which are fed into the shader
stack.

At this point, I decided it was time to change my sphere
representation from a UV sphere to an icosphere as a UV
sphere has a higher vertex density at it's poles, and
it would be best if I had an equal vertex density over the
surface of my sphere.

To do this I first generate an icosahedron, and normalise
it's vertices so that they lie on the unit sphere.
Then I wrote my own algorithm which subdivides each triangle
and normalises the added vertices onto the unit sphere,
making sure not to duplicate any vertices.


