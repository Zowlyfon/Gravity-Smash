# Idea Pitch
## Gravity Smash

I would like to create a game in which the player controls a planet/asteroid in space.
The objective is to collide with planets smaller than the player while avoiding larger ones,
as the player collides with more planet, they gain mass and size. The player must keep gaining
mass until they reach the next stage. The input controls will be "WASD" to move up, left, down and right.

The game takes inspiration from Solar 2, however uses 3d graphics and procedural techniques in order
to create an infinite world.

There will be a basic 2d n-body gravity simulation using the newtonian physics model, this can sacrifice
accuracy for fun gameplay.

The physics engine will make use of the builtin multi-threading tools from the C++ standard library.

There will be a basic GUI implemented using ImGUI.

