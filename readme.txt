cub3D Project

Team Members
- Leo (lstorey)
- Marius (mmeiers)

Introduction

cub3D is a project from the 42 School that challenges students to create a basic 3D game
engine inspired by the early FPS games, specifically Wolfenstein 3D. 
The project involves building a 3D world using raycasting techniques, rendering graphics 
from a first-person perspective. Our goal is to complete the core requirements along with 
the collision detection and mouse movement bonuses.

Features Implemented

Mandatory Features
- Raycasting Engine: Displaying walls, floor, and ceiling in a 3D perspective using 
raycasting techniques.
- Basic Movement: Ability to move the player forward, backward, and sideways.
- Textures: Walls and floor textures are displayed based on the game's map.
- Simple Map Parsing: The game reads a .cub map file to generate the environment.

Bonuses we are aiming to complete
- Collision Detection: Our implementation includes proper collision detection, ensuring 
that the player cannot move through walls or other obstacles.
- Mouse Movement: We implemented mouse control for player camera rotation, allowing for 
smooth and intuitive looking around the environment.

Controls

- W / A / S / D: Move the player forward, left, backward, and right.
- Arrow Keys: Rotate the camera (left or right).
- Mouse: Move the mouse to rotate the camera (enabled for bonus).
- ESC: Exit the game.

Map Format

The map file should be a .cub file, which defines the layout of the walls and the spawn 
point of the player. Example map format:
111111
100001
100001
1000N1
111111

In this example:
- 1 represents walls
- 0 represents empty space
- N represents the player spawn point (facing north)

Known Issues

- The project does not yet include advanced bonus features like sprite rendering or floor 
casting.
- Some edge cases in map parsing might not be fully handled.

Future Improvements

- Implementing more bonuses such as minimap display and dynamic lighting.
- Adding more advanced collision mechanics, such as sliding along walls when hitting them 
at an angle.

Conclusion

to be written.......

