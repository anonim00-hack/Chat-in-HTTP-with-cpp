#include "raylib.h"
#include <climits>
#include <iterator>
#include <vector>

#define WIDTH 1000
#define HEIGHT 800

struct physic {
    struct particle {
        unsigned char ID;
        unsigned char temperature;
        bool isUpdated;
    };
};

Color pallet[4]{{10, 10, 10, 255}, {200, 200, 10, 255}, {100, 100, 100, 255},
    {20, 20, 200, 255}};

int main()
{
    InitWindow(WIDTH, HEIGHT, "Title");
    SetTargetFPS(60);


    short cell_size = 10;
    short cols = WIDTH / cell_size;
    short rows = HEIGHT / cell_size;

    short mode = 0;

    std::vector<physic::particle> world(cols * rows, {0, 20});

    Image canvas = GenImageColor(cols, rows, BLACK);
    Texture2D screen = LoadTextureFromImage(canvas);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(0))
        {
            short mx = GetMouseX() / cell_size;
            short my = GetMouseY() / cell_size;
            if (mx >= 0 && mx < cols && my >= 0 && my < rows)
            {
                int index = my * (cols) + mx;
                if (mode == 0)
                    world[index].ID = 1;
                else if (mode == 1)
                    world[index].ID = 2;
                else if (mode == 2)
                    world[index].ID = 3;
                else
                    world[index].ID = 0;
            }
        }
        if (IsKeyPressed(KEY_TAB))
        {
            mode += 1;
            if (mode >= std::size(pallet))
            {
                mode = 0;
            }
        }
        if (IsKeyPressed(KEY_R))
        {
            for (auto &obj : world)
            {
                if (obj.ID != 0)
                {
                    obj.ID = 0;
                }
            }
        }

        for (auto &p : world)
            p.isUpdated = false;

        for (int y = rows - 2; y >= 0; y--)
        {
            for (int x = 0; x < cols; x++)
            {
                int i = y * cols + x;

                if (world[i].ID == 1 && !world[i].isUpdated)
                {
                    int below = (y + 1) * cols + x;
                    int bLeft = (y + 1) * cols + (x - 1);
                    int bRight = (y + 1) * cols + (x + 1);
                    int right = y * cols + (x + 1);
                    int left = y * cols + (x - 1);

                    if (world[below].ID == 0)
                    {
                        world[below] = world[i];
                        world[below].isUpdated = true;
                        world[i].ID = 0;
                    } else if (x > 0 && world[bLeft].ID == 0 &&
                               world[left].ID == 0)
                    {
                        world[bLeft] = world[i];
                        world[bLeft].isUpdated = true;
                        world[i].ID = 0;
                    } else if (x < cols - 1 && world[bRight].ID == 0 &&
                               world[right].ID == 0)
                    {
                        world[bRight] = world[i];
                        world[bRight].isUpdated = true;
                        world[i].ID = 0;
                    }
                }
            }
        }
        Color *pixels = (Color *)canvas.data;
        for (int i = 0; i < cols * rows; i++)
        {
            pixels[i] = pallet[world[i].ID];
        }
        UpdateTexture(screen, canvas.data);

        BeginDrawing();
        ClearBackground({10, 10, 10, 250});

        DrawTextureEx(screen, {0, 0}, 0, (float)cell_size, WHITE);

        DrawText(TextFormat("Mode: %i", mode), 20, 20, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}