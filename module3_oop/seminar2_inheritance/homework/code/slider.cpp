#include "raylib.h"
#include <iostream>
#include <algorithm>

class Slider
{
protected:
    Rectangle mTrackRect{};
    Rectangle mThumbRect{};

    bool mIsPressed{false};

public:
    Slider(Vector2 centerPosition, Vector2 trackSize, Vector2 thumbSize)
    {
        mTrackRect.width = trackSize.x;
        mTrackRect.height = trackSize.y;
        mTrackRect.x = centerPosition.x - trackSize.x / 2.0f;
        mTrackRect.y = centerPosition.y - trackSize.y / 2.0f;

        mThumbRect.width = thumbSize.x;
        mThumbRect.height = thumbSize.y;
        mThumbRect.x = centerPosition.x - thumbSize.x / 2.0f;
        mThumbRect.y = centerPosition.y - thumbSize.y / 2.0f;
    }

    void draw()
    {
        DrawRectangleRec(mTrackRect, {200, 200, 220, 255});
        DrawRectangleRec(mThumbRect, {150, 150, 240, 255});
    }

    void setRestrictedThumbPosition(Vector2 position)
    {
        float min = mTrackRect.x;
        float max = mTrackRect.x + mTrackRect.width;
        float clampedX = std::clamp(position.x, min, max);
        mThumbRect.x = clampedX - mThumbRect.width / 2.0f;
    }

    bool handleEvent()
    {
        Vector2 mousePosition = GetMousePosition();
        bool result = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, mThumbRect) ||
                CheckCollisionPointRec(mousePosition, mTrackRect))
            {
                mIsPressed = true;
                setRestrictedThumbPosition(mousePosition);
                result = true;
            }
        }

        if (mIsPressed && (GetMouseDelta().x != 0 || GetMouseDelta().y != 0))
        {
            setRestrictedThumbPosition(mousePosition);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            mIsPressed = false;
        }

        return result;
    }

    bool isPressed() const
    {
        return mIsPressed;
    }

    float getValue() const
    {
        float start = mTrackRect.x;
        float finish = mTrackRect.x + mTrackRect.width;
        float position = mThumbRect.x + mThumbRect.width / 2.0f;
        return 100.0f * (position - start) / (finish - start);
    }
};



int main()
{
    InitWindow(800, 800, "Slider Class!");
    SetTargetFPS(60);

    Slider slider({400, 400}, {500, 20}, {25, 90});

    while (!WindowShouldClose())
    {
        slider.handleEvent();

        if (slider.isPressed() && (GetMouseDelta().x != 0 || GetMouseDelta().y != 0))
        {
            std::cout << slider.getValue() << std::endl;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        slider.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}