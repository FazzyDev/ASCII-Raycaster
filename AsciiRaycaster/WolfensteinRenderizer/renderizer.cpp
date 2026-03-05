// ascii-raycaster-cpp

#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>

bool running = true;

int map[8][8] = { // Map saved in memory. bit-per-bit boolean system
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,2,0,0,0,0,1},
    {1,0,0,0,0,0,2,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,2,2,2,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
};

struct Player {
    float x = 4.0f, y = 4.0f; // Position in world.
    float angle = 0.0f;       // Where its looking.

    // Configs:
    float RotSpeed = 0.05f; // Rotation Speed.
};

float Raycast(float x, float y, float angle) { // Raycast
    float rx = cos(angle); // We mathematically calculate the rotation with its respective function.
    float ry = sin(angle); // We mathematically calculate the rotation with its respective function.
    float dist = 0.0f; // Distance variable.

    while (dist < 20.0f) { // If the distance is less than 20...
        dist += 0.05f; // Add 0.05 to the distance
        int mapX = (int)(x + rx * dist); // Get bit on map at distance and angle X
        int mapY = (int)(y + ry * dist); // Get bit on the map at distance and angle Y
        if (map[mapY][mapX] != 0) return dist; // If the char is not 0, positive, return the distance so that the rendering can create depth.
    }
    return 20.0f; // Return 20.

    // It should be emphasized that this rendering method does not allow for gaps in the map; it only calculates distance.
}

int GetCharTexture(float x, float y, float angle)
{
    float rx = cos(angle);
    float ry = sin(angle);
    float dist = 0.0f; 

    while (dist < 20.0f) {
        dist += 0.05f;
        int mapX = (int)(x + rx * dist);
        int mapY = (int)(y + ry * dist);
        if (map[mapY][mapX] != 0) return map[mapY][mapX]; // Return on hit.
    }
    return 1;
}

void render(Player& j) {
    int width = 60; // Screen Width in chars.
    int height = 20; // Screen Height in chars.
    float fov = 3.14159f / 3.0f; // Field of View.

    // HORIZONTAL RENDERING:
    // First we calculate all the heights
    std::vector<int> alturas(width); // Create a variable for the height to render the wall, the size.
    for (int col = 0; col < width; col++) { // For each column in width per char...
        float angle = j.angle - fov / 2 + fov * col / width; // Calculate the ray angle. The player's angle - fov / 2 + fov * column in char width / width in char
        float dist = Raycast(j.x, j.y, angle); // It launches the beam from the player's position and returns the distance it hits the wall.
        alturas[col] = (int)(height / dist); // The height, that is, the size of the next row to be rendered, is the height in characters / the distance to the wall.
        // Creating a depth effect
    }

    // VERTICAL RENDERING:
    // Then we draw row by row
    for (int row = 0; row < height; row++) { // For each row in height per char...
        for (int col = 0; col < width; col++) { // For each column in width per char...
            int half = height / 2; // We calculate half the screen, height divided by 2
            if (row >= half - alturas[col] && row <= half + alturas[col]) // For each row, draw a symbol if the row is larger or smaller. Otherwise, leave a space.
            { 
                float angle = j.angle - fov / 2 + fov * col / width; // Get angle again.
                int tex_type = GetCharTexture(j.x, j.y, angle); // Obtain texture type.

                switch (tex_type) // Render a different char for different textures.
                {
                    case 1:
                        std::cout << '#';
                    break;

                    case 2:
                        std::cout << '*';
                    break;
                }
                
            }
            else 
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n'; // End rendering
    }
}

int main()
{
    // Activate ANSI codes in Windows:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // It obtains a handle (Windows identifier) ​​and chooses standard output, print.
    DWORD mode; // 32 bits int mode.
    GetConsoleMode(hConsole, &mode); // It reads the current configuration and saves it in mode.
    SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING); // Activate the ANSI codes on the terminal and retrieve the console settings.

    // Hide the cursor so it doesn't blink on the screen.
    std::cout << "\033[?25l";

    Player player; // Create player instance.
    char key; // Keyboard
    float _rotspeed = player.RotSpeed;
    while (running)
    {
        // INPUT
        if (_kbhit()) // Check if a key is pressed.
        {
            key = _getch(); // Get current key pressed.

            switch (key)
            {
                // Rotate
                case 'a':
                    player.angle -= _rotspeed;
                break;

                case 'd':
                    player.angle += _rotspeed;
                break;

                // Move
                case 'w': // forward
                    player.x += cos(player.angle) * _rotspeed; // Sumar la velocidad con la rotacion del jugador. (Mover hacia delante)
                    player.y += sin(player.angle) * _rotspeed;
                break;

                case 's': // backward
                    player.x -= cos(player.angle) * _rotspeed; // Restar la velocidad con la rotacion del jugador. (Mover hacia atras)
                    player.y -= sin(player.angle) * _rotspeed;
                break;
            }
        }

        // RENDERING
        std::cout << "\033[H"; // Clear Screen.
        render(player); // Render Next Frame
    }
}