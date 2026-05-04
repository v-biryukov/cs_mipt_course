#include "raylib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

class Observer
{
public:
    virtual void update(float value) = 0;
    virtual ~Observer() = default;
};

class Drawable
{
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Slider : public Drawable
{
private:
    Rectangle mTrack;
    Rectangle mThumb;
    Color mTrackColor {200, 200, 220, 255};
    Color mThumbColor {150, 150, 240, 255};
    bool mIsPressed {false};
    std::set<Observer*> mObservers;

public:
    Slider(Vector2 center, Vector2 trackSize, Vector2 thumbSize)
    {
        mTrack = {center.x - trackSize.x / 2, center.y - trackSize.y / 2, trackSize.x, trackSize.y};
        mThumb = {center.x - thumbSize.x / 2, center.y - thumbSize.y / 2, thumbSize.x, thumbSize.y};
    }

    void draw() const override
    {
        DrawRectangleRec(mTrack, mTrackColor);
        DrawRectangleRec(mThumb, mThumbColor);
    }

    void updateInput()
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, mThumb) || CheckCollisionPointRec(mouse, mTrack))
            {
                mIsPressed = true;
                mThumb.x = mouse.x - mThumb.width / 2;
                notifyObservers();
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            mIsPressed = false;
        }

        if (mIsPressed)
        {
            float min = mTrack.x;
            float max = mTrack.x + mTrack.width;
            float clampedX = std::clamp(mouse.x, min, max);
            mThumb.x = clampedX - mThumb.width / 2;
            notifyObservers();
        }
    }

    float getValue() const
    {
        float part = (mThumb.x + mThumb.width / 2) - mTrack.x;
        return (part / mTrack.width) * 100.0f;
    }

    void addObserver(Observer* p)
    {
        mObservers.insert(p);
    }

    void notifyObservers()
    {
        for (auto p : mObservers)
        {
            p->update(getValue());
        }
    }
};

class Circle : public Observer, public Drawable
{
protected:
    Vector2 mPosition;
    float mRadius;
    float mScale {1.0f};
    Color mColor {0, 255, 0, 255};

public:
    Circle(Vector2 position, float radius)
        : mPosition(position), mRadius(radius)
    {
    }

    void draw() const override
    {
        DrawCircleV(mPosition, mRadius * mScale, mColor);
    }

    void update(float value) override
    {
        std::cout << value << std::endl;
        mScale = value / 50.0f;
    }
};

class CircleColorChange : public Circle
{
public:
    CircleColorChange(Vector2 position, float radius)
        : Circle(position, radius)
    {
        mColor = {0, 0, 100, 255};
    }

    void update(float value) override
    {
        mColor = {0, 0, (unsigned char)(value * 2), 255};
    }
};

class Square : public Observer, public Drawable
{
private:
    Vector2 mPosition;
    float mSize;
    float mRotation {0.0f};

public:
    Square(Vector2 position, float size)
        : mPosition(position), mSize(size)
    {
    }

    void draw() const override
    {
        DrawRectanglePro({mPosition.x, mPosition.y, mSize, mSize}, {mSize / 2, mSize / 2}, mRotation, RED);
    }

    void update(float value) override
    {
        mRotation = 3 * value;
    }
};

int main()
{
    InitWindow(800, 800, "Multiple Observers (raylib)");
    SetTargetFPS(60);

    Slider slider({400, 500}, {500, 20}, {25, 90});

    std::vector<Observer*> observers
    {
        new Circle({100, 300}, 50),
        new Square({400, 300}, 100),
        new CircleColorChange({700, 300}, 50),
    };

    for (auto p : observers)
    {
        slider.addObserver(p);
    }

    while (!WindowShouldClose())
    {
        slider.updateInput();

        BeginDrawing();
        ClearBackground(BLACK);

        slider.draw();

        for (auto p : observers)
        {
            dynamic_cast<Drawable*>(p)->draw();
        }

        EndDrawing();
    }

    for (auto p : observers)
    {
        delete p;
    }

    CloseWindow();
    return 0;
}