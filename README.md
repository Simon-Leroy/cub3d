# cub3D

A small 3D game engine written in C with raycasting, inspired by Wolfenstein 3D.
Project of the 42 curriculum, built on top of [MiniLibX](https://github.com/42paris/minilibx-linux).

## Features

- Raycasting renderer with textured walls (one texture per cardinal direction)
- Configurable floor and ceiling colors
- Map parsing and validation (closed walls, single player start, valid textures and colors)
- Smooth movement and camera rotation

## Build

The MiniLibX is a git submodule, so clone with:

```sh
git clone --recurse-submodules git@github.com:Simon-Leroy/cub3d.git
cd cub3d
make
```

Requires `cc`, `make`, and the X11 development libraries (`libxext-dev`, `libx11-dev`).

Other targets: `make clean`, `make fclean`, `make re`.

## Usage

```sh
./Cub3d map/good/subject_map.cub.cub
```

Sample maps are provided in `map/good/` (valid) and `map/bad/` (invalid, should be rejected with an error).

## Controls

| Key        | Action               |
|------------|----------------------|
| `W` / `S`  | Move forward / back  |
| `A` / `D`  | Strafe left / right  |
| `←` / `→`  | Rotate the camera    |
| `Esc`      | Quit                 |

## Map format

A `.cub` file contains texture paths, colors, then the map:

```
NO assets/grey_stone.xpm
SO assets/purple_stone.xpm
WE assets/red_brick.xpm
EA assets/wood.xpm

F 220,100,0
C 225,254,6

1111111
1000001
10N0001
1111111
```

- `NO`, `SO`, `WE`, `EA`: `.xpm` textures for each wall direction
- `F` / `C`: floor / ceiling color as `R,G,B` (0-255)
- `1` wall, `0` empty space, `N` `S` `E` `W` player start and orientation
- The map must be surrounded by walls

## Project layout

```
exec/      rendering, raycasting, movement, game loop
parsing/   .cub file parsing and validation
init/      data initialization and map building
include/   headers
libft/     custom C library
assets/    textures
map/       sample maps
```
