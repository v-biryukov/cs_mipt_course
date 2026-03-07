#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Draggable
{
protected:
    sf::RectangleShape mShape   {};
    bool mIsDragged             {false};
    sf::Vector2f mOffset        {0.0f, 0.0f};
    sf::RenderWindow& mRenderWindow;

public:
    Draggable(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Color color)
    : mRenderWindow(window)
    {
        mShape.setPosition(position);
        mShape.setSize(size);
        mShape.setFillColor(color);
    }

    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mShape.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mShape.getPosition();
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
            mShape.setPosition(mousePosition - mOffset);
    }

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

    void setColor(sf::Color c)          {mShape.setFillColor(c);}
    void setSize(sf::Vector2f sz)       {mShape.setSize(sz);}
    void setPosition(sf::Vector2f p)    {mShape.setPosition(p);}

    void draw() const
    {
        mRenderWindow.draw(mShape);
    }
};