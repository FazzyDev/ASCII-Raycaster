# ASCII-Raycaster
A Wolfenstein-style 3D raycaster rendered entirely in the terminal using ASCII characters, built from scratch in C++ with no external graphics libraries.

## Features
- Real-time raycasting engine
- Player movement and rotation
- Wall collision detection
- Multiple wall types with different characters
- Flicker-free rendering using ANSI escape codes

## How it works
For each column on the screen, a ray is cast from the player's position at a calculated angle. The distance to the wall determines the height of that column, creating the illusion of depth and perspective.

## Controls
- W / S — Move forward / backward
- A / D — Rotate left / right

## Build
Compiled with any C++ compiler on Windows. Open in Visual Studio or use g++:
g++ ascii_raycaster.cpp -o raycaster
