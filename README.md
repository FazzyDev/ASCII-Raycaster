# ASCII-Raycaster
A Wolfenstein-style 3D raycaster rendered entirely in the terminal using ASCII characters, built from scratch in C++ with no external graphics libraries.

![ascii_raycaster](https://github.com/user-attachments/assets/f7e9f68d-b110-46db-b55d-bd26fcb33cd3)

## Features
- Real-time raycasting engine
- Player movement and rotation
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
