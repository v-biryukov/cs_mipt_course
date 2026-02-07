#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Draggable
{
protected:
    
    sf::Vector2f mPosition;
    bool mIsDragged             {false};
    sf::Vector2f mOffset        {0.0f, 0.0f};
    sf::RenderWindow& mRenderWindow;

public:
    Draggable(sf::RenderWindow& window, sf::Vector2f position)
    : mRenderWindow(window), mPosition(position){}

    virtual bool checkIfContains(sf::Vector2f position) const = 0;
    virtual void draw() const = 0;

    bool handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            return onMousePressed(mousePosition);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMouseReleased();
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePosition);
        }

        return false;
    }

    void setPosition(sf::Vector2f p)    {mPosition = p;}
    sf::Vector2f getPosition() const    {return mPosition;}

private:
    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (checkIfContains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mPosition;
        }
        return mIsDragged;
    }

    void onMouseReleased()
    {
        mIsDragged = false;
    }

    void onMouseMoved(sf::Vector2f mousePosition)
    {
        if (mIsDragged)
            mPosition = mousePosition - mOffset;
    }
};



class RectangleDraggable : public Draggable
{
private:
    sf::Vector2f mSize;
    sf::Color mColor;

public:
    RectangleDraggable(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Color color)
    : Draggable(window, position), mSize(size), mColor(color) {}

    bool checkIfContains(sf::Vector2f position) const override
    {
        sf::FloatRect rect {mPosition.x, mPosition.y, mSize.x, mSize.y};
        return rect.contains(position);
    }

    void draw() const override
    {
        static sf::RectangleShape shape {};
        shape.setPosition(mPosition);
        shape.setSize(mSize);
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
    }
};


class CircleDraggable : public Draggable
{
private:
    float mRadius;
    sf::Color mColor;

public:
    CircleDraggable(sf::RenderWindow& window, sf::Vector2f position, float radius, sf::Color color)
    : Draggable(window, position), mRadius(radius), mColor(color) {}

    bool checkIfContains(sf::Vector2f position) const override
    {
        sf::Vector2f d = mPosition + sf::Vector2f{mRadius, mRadius} - position;
        float distancesq = d.x * d.x + d.y * d.y;
        return distancesq < mRadius * mRadius;
    }

    void draw() const override
    {
        static sf::CircleShape shape {};
        shape.setPosition(mPosition);
        shape.setRadius(mRadius);
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
    }
};


class SmoothDraggable : public Draggable
{
private:
    sf::Vector2f mSize {};
    float mSmoothness  {};
    sf::Color mColor   {};

    mutable sf::CircleShape mCornerCircle;
    mutable sf::RectangleShape mHorizontalRectangle;
    mutable sf::RectangleShape mVerticalRectangle;

public:
    SmoothDraggable(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, float smoothness, sf::Color color)
    : Draggable(window, position), mSize(size), mSmoothness(smoothness), mColor(color) 
    {
        float minSide = std::min(mSize.x, mSize.y);
        float cornerRadius = minSide / 2.f * mSmoothness;

        mCornerCircle.setRadius(cornerRadius);
        mHorizontalRectangle.setSize({mSize.x, mSize.y - 2.f * cornerRadius});
        mVerticalRectangle.setSize({mSize.x - 2.f * cornerRadius, mSize.y});

        updatePositions();

        mCornerCircle.setFillColor(mColor);
        mHorizontalRectangle.setFillColor(mColor);
        mVerticalRectangle.setFillColor(mColor);
    }

    bool checkIfContains(sf::Vector2f position) const override
    {
        updatePositions();
        bool result =   mHorizontalRectangle.getGlobalBounds().contains(position) 
                        || mVerticalRectangle.getGlobalBounds().contains(position)
                        || checkIfCircleContains(mCornerCircle, position);

        float cornerRadius = mCornerCircle.getRadius();

        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, 0});
        result |= checkIfCircleContains(mCornerCircle, position);

        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, mSize.y - 2.f * cornerRadius});
        result |= checkIfCircleContains(mCornerCircle, position);    

        mCornerCircle.setPosition(mPosition + sf::Vector2f{0, mSize.y - 2.f * cornerRadius});
        result |= checkIfCircleContains(mCornerCircle, position);

        mCornerCircle.setPosition(mPosition);
        return result;
    }

    void draw() const override
    {
        updatePositions();
        mRenderWindow.draw(mHorizontalRectangle);
        mRenderWindow.draw(mVerticalRectangle);

        float cornerRadius = mCornerCircle.getRadius();

        mRenderWindow.draw(mCornerCircle);
        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, 0});
        mRenderWindow.draw(mCornerCircle);
        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, mSize.y - 2.f * cornerRadius});
        mRenderWindow.draw(mCornerCircle);    
        mCornerCircle.setPosition(mPosition + sf::Vector2f{0, mSize.y - 2.f * cornerRadius});
        mRenderWindow.draw(mCornerCircle);
        mCornerCircle.setPosition(mPosition);
    }

private:

    void updatePositions() const
    {
        mCornerCircle.setPosition(mPosition);
        mHorizontalRectangle.setPosition(mPosition + sf::Vector2f{0, mCornerCircle.getRadius()});
        mVerticalRectangle.setPosition(mPosition + sf::Vector2f{mCornerCircle.getRadius(), 0});
    }


    static bool checkIfCircleContains(const sf::CircleShape& circle, sf::Vector2f position)
    {
        sf::Vector2f d = circle.getPosition() + sf::Vector2f{circle.getRadius(), circle.getRadius()} - position;
        float distancesq = d.x * d.x + d.y * d.y;
        return distancesq < circle.getRadius() * circle.getRadius();
    }
};


