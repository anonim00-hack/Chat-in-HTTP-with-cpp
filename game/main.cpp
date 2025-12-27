#include "raylib.h"
#include <cstdarg>
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

    InitWindow(screenWidth, screenHeight, "Learning Base");
    SetTargetFPS(60);

    Texture2D image = LoadTexture("./background.jpg");
    Texture2D playerImage = LoadTexture("./player.png");

    image.width = screenWidth;
    image.height = screenWidth / 2;


    Vector2 playerPos = {screenWidth / 2, screenHeight / 2};
    float sizeX = 40;
    float sizeY = 40;
    float speed = 5.0f;
    float velY = 0;
    int direction = 1;
    bool jump = true;

    playerImage.width = sizeX;
    playerImage.height = sizeY;

    Rectangle playerSource = {0,0,(float)playerImage.width * direction, (float)playerImage.height};

    useles_objects objects(420, 100, 80, 80, RED);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_UP) && !jump)
        {
            jump = true;
            velY = -12.0f;
        }
        if (IsKeyDown(KEY_RIGHT) && playerPos.x < screenWidth - sizeX)
        {
            playerSource = {0,0,(float)playerImage.width * direction, (float)playerImage.height};
            playerPos.x += speed;
            if (direction == -1)
            {
                direction = 1;
            }
        }
        if (IsKeyDown(KEY_LEFT) && playerPos.x > 0)
        {
            playerSource = {0,0,(float)playerImage.width * direction, (float)playerImage.height};
            if (direction == 1)
            {
                direction = -1;
            }
            playerPos.x -= speed;
        }

    if (CheckCollisionRecs(
            {playerPos.x, playerPos.y, sizeX, sizeY}, objects.rect))
    {
        playerPos = {0, 0};
    }

    playerPos.y += velY;
    velY += speed * 0.2;
    if (playerPos.y + sizeY >= 150 + image.height - 100)
    {
        velY = 0;
        jump = false;
    }

    BeginDrawing();
    ClearBackground({10,10,15,255});
    DrawTexture(image, 0, 150, WHITE);

    DrawTextureRec(playerImage,playerSource,playerPos,WHITE);

    objects.Draw();

    DrawText("Move with Arrows", 10, 10, 20, DARKGRAY);
    DrawFPS(screenWidth - 100, 10);

    EndDrawing();
}
UnloadTexture(image);
UnloadTexture(playerImage);
CloseWindow();
return 0;
}