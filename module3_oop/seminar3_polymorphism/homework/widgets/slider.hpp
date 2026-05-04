#pragma once
#include "raylib.h"
#include <algorithm>

class Slider
{
protected:
    Rectangle mTrack {};  // Полоска
    Rectangle mThumb {};  // Ползунок

    bool mIsPressed {false};

public:
    Slider(Vector2 centerPosition, Vector2 trackSize, Vector2 thumbSize)
    {
        mTrack = 
        {
            centerPosition.x - trackSize.x / 2.0f,
            centerPosition.y - trackSize.y / 2.0f,
            trackSize.x,
            trackSize.y
        };

        mThumb = 
        {
            centerPosition.x - thumbSize.x / 2.0f,
            centerPosition.y - thumbSize.y / 2.0f,
            thumbSize.x,
            thumbSize.y
        };
    }

    void draw() const
    {
        DrawRectangleRec(mTrack, Color{200, 200, 220, 255});
        DrawRectangleRec(mThumb, Color{150, 150, 240, 255});
    }

    bool update()
    {
        Vector2 mouse = GetMousePosition();
        bool clickedThisFrame = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, mThumb) || CheckCollisionPointRec(mouse, mTrack))
            {
                mIsPressed = true;
                setRestrictedThumbPosition(mouse.x);
                clickedThisFrame = true;
            }
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mIsPressed)
        {
            setRestrictedThumbPosition(mouse.x);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            mIsPressed = false;
        }

        return clickedThisFrame;
    }

    bool isPressed() const
    {
        return mIsPressed;
    }

    float getValue() const
    {
        float start  = mTrack.x;
        float finish = mTrack.x + mTrack.width;
        float pos    = mThumb.x + mThumb.width / 2.0f;

        return 100.0f * (pos - start) / (finish - start);
    }

private:
    void setRestrictedThumbPosition(float mouseX)
    {
        float min = mTrack.x;
        float max = mTrack.x + mTrack.width;

        float clampedX = std::clamp(mouseX, min, max);
        mThumb.x = clampedX - mThumb.width / 2.0f;
    }
};