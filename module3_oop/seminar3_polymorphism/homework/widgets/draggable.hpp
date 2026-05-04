#pragma once
#include "raylib.h"

class Draggable
{
protected:
    Rectangle mRect {};
    Color mColor {};

    bool mIsDragged {false};
    Vector2 mOffset {0.0f, 0.0f};

public:
    Draggable(Vector2 position, Vector2 size, Color color)
    {
        mRect = { position.x, position.y, size.x, size.y };
        mColor = color;
    }

    void update()
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, mRect))
            {
                mIsDragged = true;
                mOffset = {mouse.x - mRect.x, mouse.y - mRect.y};
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            mIsDragged = false;
        }

        if (mIsDragged)
        {
            mRect.x = mouse.x - mOffset.x;
            mRect.y = mouse.y - mOffset.y;
        }
    }

    void draw() const
    {
        DrawRectangleRec(mRect, mColor);
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

    void setPosition(Vector2 p)   
    { 
        mRect.x = p.x; 
        mRect.y = p.y; 
    }

    Rectangle getRect() const { return mRect; }
};