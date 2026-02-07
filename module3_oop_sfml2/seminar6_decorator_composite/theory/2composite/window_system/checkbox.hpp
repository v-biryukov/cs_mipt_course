#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Checkbox
{
public:
    inline static const float squareSize            {16};
    inline static const float squareBorderThickness {3};
    inline static const float squareToTextDistance  {8};
    inline static const int characterSize           {20};

    inline static const sf::Color checkedColor {sf::Color{2, 116, 189}};
    inline static const sf::Color uncheckedColor {sf::Color::White};
    inline static const sf::Color borderColor {sf::Color::Black};
    inline static const sf::Color textColor  {sf::Color::Black};

private:
    sf::RenderWindow& mRenderWindow;
    sf::RectangleShape mShape {};
    sf::Text mText            {};
    bool mIsChecked           {false};
    sf::FloatRect mBoundary   {};

public:
    Checkbox(sf::RenderWindow& window, sf::Font& font, sf::Vector2f position, const sf::String& textData)
    : mRenderWindow(window)
    {
        mShape.setPosition(position);
        mShape.setSize({squareSize, squareSize});
        mShape.setFillColor(uncheckedColor);
        mShape.setOutlineThickness(squareBorderThickness);
        mShape.setOutlineColor(borderColor);

        mText.setFont(font);
        mText.setString(textData);
        mText.setCharacterSize(characterSize);
        mText.setFillColor(textColor);
        sf::FloatRect textRect = mText.getLocalBounds();
        mText.setPosition(position.x + squareSize + squareToTextDistance, 
                          position.y + squareSize / 2.f - textRect.top - textRect.height / 2.f);

        auto combineFloatRects = [](const sf::FloatRect& rect1, const sf::FloatRect& rect2) 
        {
            float left = std::min(rect1.left, rect2.left);
            float top = std::min(rect1.top, rect2.top);
            float right = std::max(rect1.left + rect1.width, rect2.left + rect2.width);
            float bottom = std::max(rect1.top + rect1.height, rect2.top + rect2.height);
            return sf::FloatRect(left, top, right - left, bottom - top);
        };
        mBoundary = combineFloatRects(mShape.getGlobalBounds(), mText.getGlobalBounds());
    }

    bool isChecked() const
    {
        return mIsChecked;
    }

    sf::String getString() const
    {
        return mText.getString();
    }

    void draw() const
    {
        mRenderWindow.draw(mShape);
        mRenderWindow.draw(mText);
    }

    bool onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mBoundary.contains(mousePosition))
            {
                mIsChecked = !mIsChecked;

                if (mIsChecked)
                    mShape.setFillColor(checkedColor);
                else
                    mShape.setFillColor(uncheckedColor);

                return true;
            }
        }
        return false;
    }

    bool handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed)
            return onMousePressed(event);
        return false;
    }

};
