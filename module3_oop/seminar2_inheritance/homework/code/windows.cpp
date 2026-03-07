#include "raylib.h"

class BaseWindow
{
private:
    static constexpr float dragAreaHeight = 30.0f;

    Rectangle mBaseRect{};
    Rectangle mDragRect{};

    bool mIsDragged{false};

    Vector2 mDragBaseDistance{};
    Vector2 mOffset{};

public:
    BaseWindow(Rectangle borders)
    {
        mDragRect = { borders.x, borders.y, borders.width, dragAreaHeight };
        mBaseRect = { borders.x, borders.y + dragAreaHeight, borders.width, borders.height - dragAreaHeight };

        mDragBaseDistance = {
            mDragRect.x - mBaseRect.x,
            mDragRect.y - mBaseRect.y
        };
    }

    bool onMousePressed(Vector2 mousePosition)
    {
        if (CheckCollisionPointRec(mousePosition, mDragRect))
        {
            mIsDragged = true;
            mOffset = {
                mousePosition.x - mDragRect.x,
                mousePosition.y - mDragRect.y
            };
        }
        return mIsDragged;
    }

    void onMouseReleased()
    {
        mIsDragged = false;
    }

    void onMouseMoved(Vector2 mousePosition)
    {
        if (mIsDragged)
        {
            mDragRect.x = mousePosition.x - mOffset.x;
            mDragRect.y = mousePosition.y - mOffset.y;

            mBaseRect.x = mDragRect.x - mDragBaseDistance.x;
            mBaseRect.y = mDragRect.y - mDragBaseDistance.y;
        }
    }

    void handleEvents()
    {
        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            onMousePressed(mousePosition);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            onMouseReleased();
        }

        if (GetMouseDelta().x != 0 || GetMouseDelta().y != 0)
        {
            onMouseMoved(mousePosition);
        }
    }

    void setBaseColor(Color c) { }
    void setBaseSize(Vector2 sz) { mBaseRect.width = sz.x; mBaseRect.height = sz.y; }
    void setDragColor(Color c) { }
    void setDragSize(Vector2 sz) { mDragRect.width = sz.x; mDragRect.height = sz.y; }

    void setPosition(Vector2 p)
    {
        mBaseRect.x = p.x;
        mBaseRect.y = p.y;

        mDragRect.x = mBaseRect.x + mDragBaseDistance.x;
        mDragRect.y = mBaseRect.y + mDragBaseDistance.y;
    }

    void draw(Color baseColor, Color dragColor) const
    {
        DrawRectangleRec(mBaseRect, baseColor);
        DrawRectangleRec(mDragRect, dragColor);
    }
};

int main()
{
    InitWindow(800, 600, "Windows");
    SetTargetFPS(60);

    BaseWindow bw1({100, 200, 300, 200});
    BaseWindow bw2({500, 100, 200, 400});

    while (!WindowShouldClose())
    {
        bw1.handleEvents();
        bw2.handleEvents();

        BeginDrawing();
        ClearBackground(BLACK);

        bw1.draw({100, 50, 90, 255}, {200, 200, 150, 255});
        bw2.draw({240, 240, 240, 255}, {150, 150, 150, 255});

        EndDrawing();
    }

    CloseWindow();
    return 0;
}