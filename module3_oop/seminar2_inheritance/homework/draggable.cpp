#include <iostream>
#include <cmath>
#include <raylib.h>


class Draggable
{
private:

    Rectangle mRect {};
    Color mColor {};
    bool mIsDragged {false};
    Vector2 mOffset {0.0f, 0.0f};

public:
    Draggable(Vector2 position, Vector2 size, Color color) : mColor{color}
    {
        mRect.x = position.x;
        mRect.y = position.y;
        mRect.width = size.x;
        mRect.height = size.y;
    }

    bool onMousePressed(Vector2 mousePosition)
    {
        if (CheckCollisionPointRec(mousePosition, mRect))
        {
            mIsDragged = true;
            mOffset.x = mousePosition.x - mRect.x;
            mOffset.y = mousePosition.y - mRect.y;
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
            mRect.x = mousePosition.x - mOffset.x;
            mRect.y = mousePosition.y - mOffset.y;
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

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || GetMouseDelta().x != 0 || GetMouseDelta().y != 0)
        {
            onMouseMoved(mousePosition);
        }
    }

    void setColor(Color c)
    {
        mColor = c;
    }

    void setSize(Vector2 sz)
    {
        mRect.width = sz.x;
        mRect.height = sz.y;
    }

    void setPosition(Vector2 pos)
    {
        mRect.x = pos.x;
        mRect.y = pos.y;
    }

    void draw() const
    {
        DrawRectangleRec(mRect, mColor);
    }
};



int main()
{
    InitWindow(800, 600, "Draggable Test");
    SetTargetFPS(100);

    Draggable d {{100, 100}, {200, 400}, {80, 80, 120, 255}};


    while (!WindowShouldClose())
    {
        d.handleEvents();

        BeginDrawing();
        ClearBackground(BLACK);
        d.draw();
        EndDrawing();
    }

    CloseWindow();
}