#include "raylib.h"

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "Moving circle WASD");
    SetTargetFPS(100);

    Vector2 position = {100, 100};
    float radius = 20;
    float velocity = 1000;
    float dt = 0.01;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_W))
            position.y -= velocity * dt;

        if (IsKeyDown(KEY_S))
            position.y += velocity * dt;
        
        if (IsKeyDown(KEY_A))
            position.x -= velocity * dt;
        
        if (IsKeyDown(KEY_D))
            position.x += velocity * dt;
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(position, radius, BLUE);
        EndDrawing();
    }

    CloseWindow();
}