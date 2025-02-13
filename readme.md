<h1 align="center">Cub3D</h1>

> Hive Helsinki (School 42) 11th project (Rank04/06) of core curriculum.

<h2 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#program">Program</a>
	<span> · </span>
	<a href="#requirements">Requirements</a>
	<span> · </span>
	<a href="#instructions">Instructions</a>
</h2>

## About
The repository contains a pseudo-3D game inspired by the early FPS games, specifically Wolfenstein 3D. 
The project involves parsing map data and building a 3D world using raycasting techniques and texture mapping from a first-person perspective.
The project was done in collaboration with Leo Storey (https://github.com/Ginger-Leo/Cub3D).  
Worksplit:
- File parameters parsing (Leo)
- Map parsing (Marius)
- Flood fill algorithm (both)
- Raycaster (Marius)
- Texture mapping (both)
- Testing and bugfixing (both)

## Program
The game is launched by passing a `.ber file`, containing a valid map to the executable. A flood fill algorithm is utilised in order to determine
whether the passed map and player are surrounded by walls. A DDA algorithm with a vertical and horizontal intersection check determines the height of the walls and distance to the player. A minimap, displaying a fraction of the actual rays casted (amount of rays equal amount of pixels of screen width) is displayed in the top left corner of the game window. Textures of the walls are projected onto the different cubesides by a texture mapping algorithm. The program among others utilises the MLX42 graphics library and the C math.h. library. The entire game is rendered in realtime and every frame is drawn pixel by pixel.

## Requirements
- `gcc` compiler

## Instructions

### 1. Compiling the program

To compile the files run the following command in the repository:

```
$ make 
```

### 2. Launch the game

The game can be launched by passing a valid map (included in valid_maps directory) as an argument to the executable.
```
$ ./cub3D valid_maps/first_test.cub
```
For higher resolution:
```
$ ./cub3D valid_maps/high_res.cub
```
### 3. Navigation within the game map
```
 W / A / S / D: Move the player forward, left, backward, and right.
```
```
Arrow Keys: Rotate the camera (left or right).
```
### 4. Alteration of map
The map can the altered e.g. walls, player positions can be changed and different textures can be placed into the respective map file.
Changing the colours of floor and ceiling can be done by altering the respective RBG values of `F` and `C`. For the changes to be accepted, the game needs to be relaunched again.
