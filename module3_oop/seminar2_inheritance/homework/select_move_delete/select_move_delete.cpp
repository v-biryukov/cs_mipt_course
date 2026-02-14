#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>
#include <list>
#include <cstdlib>
#include <algorithm>


struct Ball
{
    Vector2 position;
    float radius;
    bool isChoosen;

    Ball(Vector2 p, float r) : position(p), radius(r), isChoosen(false) {}

    void draw() const
    {
        DrawCircleV(position, radius, WHITE);

        if (isChoosen)
        {
            const float f = 0.7f;

            DrawLineV({position.x - radius, position.y + radius}, {position.x - radius, position.y + radius*f}, WHITE);
            DrawLineV({position.x - radius, position.y + radius}, {position.x - radius*f, position.y + radius}, WHITE);

            DrawLineV({position.x + radius, position.y + radius}, {position.x + radius, position.y + radius*f}, WHITE);
            DrawLineV({position.x + radius, position.y + radius},{position.x + radius*f, position.y + radius}, WHITE);

            DrawLineV({position.x + radius, position.y - radius}, {position.x + radius*f, position.y - radius}, WHITE);
            DrawLineV({position.x + radius, position.y - radius}, {position.x + radius, position.y - radius*f}, WHITE);

            DrawLineV({position.x - radius, position.y - radius}, {position.x - radius*f, position.y - radius}, WHITE);
            DrawLineV({position.x - radius, position.y - radius}, {position.x - radius, position.y - radius*f}, WHITE);
        }
    }
};

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "Select, Move, Delete!");
    SetTargetFPS(60);

    std::list<Ball> balls;
    balls.emplace_back(Vector2{200, 200}, 26);
    balls.emplace_back(Vector2{400, 300}, 20);
    balls.emplace_back(Vector2{500, 100}, 16);
    balls.emplace_back(Vector2{200, 400}, 18);
    balls.emplace_back(Vector2{350, 150}, 22);
    balls.emplace_back(Vector2{750, 400}, 21);

    Rectangle selectionRect{0, 0, 0, 0};
    bool isSelecting = false;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (!IsKeyDown(KEY_LEFT_CONTROL))
            {
                for (auto& b : balls)
                    b.isChoosen = false;
            }

            for (auto& b : balls)
            {
                if (Vector2Distance(mouse, b.position) < b.radius)
                {
                    b.isChoosen = true;
                    break;
                }
            }

            if (IsKeyDown(KEY_LEFT_ALT))
                balls.emplace_back(mouse, 5 + rand() % 40);

            isSelecting = true;
            selectionRect.x = mouse.x;
            selectionRect.y = mouse.y;
            selectionRect.width = 0;
            selectionRect.height = 0;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            isSelecting = false;

        if (isSelecting)
        {
            selectionRect.width = mouse.x - selectionRect.x;
            selectionRect.height = mouse.y - selectionRect.y;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto& b : balls)
            b.draw();

        if (isSelecting)
        {
            Rectangle drawRect = selectionRect;

            if (drawRect.width < 0)
            {
                drawRect.x += drawRect.width;
                drawRect.width = -drawRect.width;
            }
            if (drawRect.height < 0)
            {
                drawRect.y += drawRect.height;
                drawRect.height = -drawRect.height;
            }

            DrawRectangleRec(drawRect, Color{150,150,240,50});
            DrawRectangleLinesEx(drawRect, 1, Color{200,200,255,255});
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}