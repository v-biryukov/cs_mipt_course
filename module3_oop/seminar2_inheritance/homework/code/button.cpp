#include "raylib.h"
#include <string>

class Button
{
private:
    inline static const Color sDefaultColor{220, 220, 220, 255};
    inline static const Color sHoverColor{180, 200, 180, 255};
    inline static const Color sPressedColor{140, 160, 140, 255};

    Rectangle mRect;
    Vector2 mTextPosition;
    std::string mText;
    int mFontSize;
    Color mCurrentColor;
    bool mIsPressed;

public:
    Button(Rectangle rect, int fontSize, const std::string& textData)
        : mRect(rect), mText(textData), mFontSize(fontSize)
    {
        int textWidth = MeasureText(mText.c_str(), mFontSize);
        mTextPosition.x = mRect.x + (mRect.width - textWidth) / 2.0f;
        mTextPosition.y = mRect.y + (mRect.height - mFontSize) / 2.0f;
        mCurrentColor = sDefaultColor;
        mIsPressed = false;
    }

    void draw()
    {
        DrawRectangleRec(mRect, mCurrentColor);
        DrawText(mText.c_str(), (int)mTextPosition.x, (int)mTextPosition.y, mFontSize, BLACK);
    }

    bool handleEvent()
    {
        Vector2 mouse = GetMousePosition();
        bool hovered = CheckCollisionPointRec(mouse, mRect);

        if (!mIsPressed)
            mCurrentColor = hovered ? sHoverColor : sDefaultColor;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hovered)
        {
            mIsPressed = true;
            mCurrentColor = sPressedColor;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            bool clicked = mIsPressed && hovered;
            mIsPressed = false;
            mCurrentColor = hovered ? sHoverColor : sDefaultColor;
            return clicked;
        }

        return false;
    }
};

int main()
{
    InitWindow(800, 600, "Button Example");
    SetTargetFPS(60);

    Button button({300, 250, 200, 60}, 20, "Click Me");

    while (!WindowShouldClose())
    {
        if (button.handleEvent())
        {
            TraceLog(LOG_INFO, "Button clicked");
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        button.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}