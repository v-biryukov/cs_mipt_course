#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>

class ContextMenu
{
private:
    inline static const Color kDefaultColor {190,210,190,255};
    inline static const Color kHoverColor {150,170,150,255};
    inline static const Color kTextColor {0,0,0,255};

    inline static const int kCharacterSize = 22;

    inline static const int kTextLeftIndent = 10;
    inline static const int kTextRightIndent = 20;
    inline static const int kTextTopIndent = 4;
    inline static const int kTextBottomIndent = 4;

    std::vector<std::string> mButtons;

    Vector2 mPosition {0,0};
    float mButtonWidth = 0;
    float mButtonHeight = 0;

    bool mIsOpened = false;
    bool mIsUpdated = false;
    int mHoverPosition = -1;

    Font mFont;

    int onMousePressed()
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            mIsOpened = true;
            mPosition = mouse;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mIsOpened)
        {
            mIsOpened = false;
            return mHoverPosition;
        }

        return -1;
    }

    void onMouseMove()
    {
        if (!mIsOpened) return;

        Vector2 mouse = GetMousePosition();
        Rectangle bounds {mPosition.x, mPosition.y, mButtonWidth, (float)(mButtonHeight * mButtons.size())};

        if (CheckCollisionPointRec(mouse, bounds)) 
            mHoverPosition = (mouse.y - mPosition.y) / mButtonHeight;
        else mHoverPosition = -1;
    }

public:

    ContextMenu()
    {
        mFont = GetFontDefault();
    }

    void addButton(const std::string& name)
    {
        mButtons.push_back(name);
        mIsUpdated = false;
    }

    int handleInput()
    {
        onMouseMove();
        return onMousePressed();
    }

    void draw()
    {
        if (!mIsOpened) return;

        if (!mIsUpdated)
        {
            float maxSizeX = 0;
            float maxSizeY = 0;
            for (auto &b : mButtons)
            {
                Vector2 size = MeasureTextEx(mFont, b.c_str(), kCharacterSize, 1);
                if (size.x > maxSizeX) 
                    maxSizeX = size.x;
                if (size.y > maxSizeY) 
                    maxSizeY = size.y;
            }

            mButtonWidth = maxSizeX + kTextLeftIndent + kTextRightIndent;
            mButtonHeight = maxSizeY + kTextTopIndent + kTextBottomIndent;
            mIsUpdated = true;
        }

        DrawRectangle(mPosition.x, mPosition.y, mButtonWidth, mButtonHeight * mButtons.size(), kDefaultColor);

        if (mHoverPosition >= 0) 
            DrawRectangle(mPosition.x, mPosition.y + mHoverPosition * mButtonHeight, mButtonWidth, mButtonHeight, kHoverColor);

        for (int i = 0; i < mButtons.size(); i++)
            DrawTextEx(mFont, mButtons[i].c_str(), {mPosition.x + kTextLeftIndent, mPosition.y + i * mButtonHeight + kTextTopIndent}, kCharacterSize, 1, kTextColor);
    }
};

int main()
{
    InitWindow(800, 600, "Context Menu Test");
    SetTargetFPS(60);

    std::vector<std::string> contextMenuStrings {"Add Button", "Cut", "Copy", "Paste", "Select All"};

    ContextMenu contextMenu;

    for (auto &s : contextMenuStrings) 
        contextMenu.addButton(s);

    while (!WindowShouldClose())
    {
        int result = contextMenu.handleInput();

        if (result >= 0) 
            std::cout << contextMenuStrings[result] << std::endl;

        if (result == 0)
        {
            contextMenuStrings.push_back("New Button");
            contextMenu.addButton("New Button");
        }

        BeginDrawing();
        ClearBackground(BLACK);

        contextMenu.draw();

        EndDrawing();
    }

    CloseWindow();
}