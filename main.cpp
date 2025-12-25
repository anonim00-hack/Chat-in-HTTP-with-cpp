#include "raylib.h"
#include <vector>

class useles_objects
{
  public:
    Rectangle rect;
    Color color;
    useles_objects(float x, float y, float sizeX, float sizeY, Color c)
    {
        rect = {x, y, sizeX, sizeY};
        color = c;
    }
    void Draw() { DrawRectangleRec(rect, color); }
};

int main()
{
    // 1. Настройка окна
    const int screenWidth = 1000;
    const int screenHeight = 800;

    float sizeX = 40;
    float sizeY = 40;
    InitWindow(screenWidth, screenHeight, "Learning Base");
    SetTargetFPS(60);

    Vector2 playerPos = {screenWidth / 2, screenHeight / 2};
    float speed = 5.0f;

    useles_objects objects(420, 100, 80, 80, RED);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT) && playerPos.x < screenWidth - sizeX)
            playerPos.x += speed + (playerPos.x < screenWidth / 2 ? speed : 0);
        if (IsKeyDown(KEY_LEFT) && playerPos.x > 0)
            playerPos.x -= speed + (playerPos.x < screenWidth / 2 ? speed : 0);
        if (IsKeyDown(KEY_UP) && playerPos.y > 0)
            playerPos.y -= speed + (playerPos.x < screenWidth / 2 ? speed : 0);
        if (IsKeyDown(KEY_DOWN) && playerPos.y < screenHeight - sizeY)
            playerPos.y += speed + (playerPos.x < screenWidth / 2 ? speed : 0);

        if (CheckCollisionRecs({playerPos.x,playerPos.y,sizeX,sizeY},objects.rect)) {
            playerPos = {0,0};
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleV(playerPos, (Vector2){sizeX, sizeY}, BLUE);

        objects.Draw();

        DrawText("Move with Arrows", 10, 10, 20, DARKGRAY);
        DrawFPS(screenWidth - 100, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}