#include "raylib.h"


int main()
{
    InitWindow(800, 600, "Inverted Image");
    SetTargetFPS(60);

    Image im = LoadImage("grass.png");
    ImageColorInvert(&im);
    ImageCrop(&im, {0, 0, 200, 200});
    Texture t = LoadTextureFromImage(im);

    float alpha = 0;

    while (!WindowShouldClose())
    {
        alpha += 2;

        BeginDrawing();
        ClearBackground(BLACK);
        //DrawTexture(t, GetScreenWidth() - t.width, GetScreenHeight() - t.height, WHITE);

        DrawTexturePro(t, {0, 0, 200, 200}, {400, 400, 200, 200}, {100, 100}, alpha, WHITE);

        DrawText("Hello World", 0, 0, 100, WHITE);
        EndDrawing();
    }


    CloseWindow();
}