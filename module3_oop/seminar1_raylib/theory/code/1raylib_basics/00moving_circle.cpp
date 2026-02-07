#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Moving Circle");
    SetTargetFPS(60);

    int x = 100;
    int y = 100;

    while (!WindowShouldClose())
    {
        x += 2;
        y += 2;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(x, y, 50, BLUE);
        EndDrawing();
    }
}