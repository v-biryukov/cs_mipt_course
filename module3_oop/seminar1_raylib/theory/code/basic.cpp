#include <raylib.h>

int main()
{
    InitWindow(800, 800, "Test Window");
    SetTargetFPS(60);

    float x = 400;
    float y = 400;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
            x += 3;

        if (IsKeyDown(KEY_LEFT))
            x -= 3;

        if (IsKeyDown(KEY_DOWN))
            y += 3;

        if (IsKeyDown(KEY_UP))
            y -= 3;


        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(x, y, 100, {30, 100, 100, 255});
        EndDrawing();
    }


    CloseWindow();
}