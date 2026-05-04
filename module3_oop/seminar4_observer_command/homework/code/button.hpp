#pragma once
#include "raylib.h"
#include <string>
#include <algorithm>

class Button
{
private:
    Color mDefaultColor {179, 230, 255, 255};
    Color mHoverColor   {128, 212, 255, 255};
    Color mPressedColor {  0, 136, 204, 255};

    Rectangle mRect {};
    std::string mText;

    int mFontSize {30};
    bool mIsPressed {false};

public:
    Button(Rectangle rect, const std::string& textData)
        : mRect(rect), mText(textData)
    {
        mFontSize = 20;
    }

    void setFontSize(int fontSize)
    {
        mFontSize = fontSize;
    }

    void draw() const
    {
        DrawRectangleRec(mRect, getCurrentColor());
        int textWidth = MeasureText(mText.c_str(), mFontSize);

        Vector2 position = 
        {
            mRect.x + (mRect.width - textWidth) / 2,
            mRect.y + (mRect.height - mFontSize) / 2.0f
        };

        DrawText(mText.c_str(), (int)position.x, (int)position.y, mFontSize, BLACK);
    }

    bool update()
    {
        Vector2 mouse = GetMousePosition();
        bool isHover = CheckCollisionPointRec(mouse, mRect);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isHover)
        {
            mIsPressed = true;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (mIsPressed && isHover)
            {
                mIsPressed = false;
                return true;
            }
            mIsPressed = false;
        }

        return false;
    }

    bool handle()
    {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, mRect))
        {
            return true;
        }
        return false;
    }

private:
    Color getCurrentColor() const
    {
        Vector2 mouse = GetMousePosition();
        bool isHover = CheckCollisionPointRec(mouse, mRect);

        if (mIsPressed)
            return mPressedColor;
        else if (isHover)
            return mHoverColor;
        else
            return mDefaultColor;
    }
};