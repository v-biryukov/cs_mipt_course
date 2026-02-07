#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "design.hpp"



class Button
{
protected:
    sf::RenderWindow& mRenderWindow; 

    sf::Color mDefaultColor {179, 230, 255};
    sf::Color mHoverColor   {128, 212, 255};
    sf::Color mPressedColor {  0, 136, 204};

    sf::Vector2f mPosition {};
    sf::Color mColor {};

    sf::Text mText {};
    bool mIsPressed {false};

    Design* mpDesign {};


public:
    Button(sf::RenderWindow& window, sf::Vector2f position, Design* pDesign, sf::Font& font, const sf::String& textData) 
            : mRenderWindow(window), mPosition(position), mpDesign(pDesign)
    {
        mColor = mDefaultColor;
        mText.setFont(font);
        mText.setString(textData);
        mText.setFillColor(sf::Color::Black);

        setOptimalFontSize();
        centerText();
    }

    bool checkIfContains(sf::Vector2f position) const
    {
        return mpDesign->checkIfContains(mPosition, position);
    }

    void draw() const
    {
        mpDesign->draw(mRenderWindow, mPosition, mColor);
        mRenderWindow.draw(mText);
    }

    sf::FloatRect getBounds() const
    {
        return mpDesign->getBounds(mPosition);
    }


    void setFontSize(unsigned int fontSize)
    {
        mText.setCharacterSize(fontSize);
        centerText();
    }

    void setOptimalFontSize()
    {
        mText.setCharacterSize(30);

        float widthFraction = 0.75;
        float heightFraction = 0.5;

        sf::FloatRect textBounds = mText.getLocalBounds();
        float widthRatio = getBounds().width / textBounds.width * widthFraction;
        float heightRatio = getBounds().height / textBounds.height * heightFraction;
        float minRatio = std::min(widthRatio, heightRatio);

        std::cout << minRatio << std::endl;
        unsigned int newSize = static_cast<unsigned int>(mText.getCharacterSize() * minRatio);
        std::cout << newSize << std::endl;
        mText.setCharacterSize(newSize);
    }

    bool handleEvent(const sf::Event& event) 
    {
        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            onMousePressed(event);
        else if (event.type == sf::Event::MouseButtonReleased)
            return onMouseReleased(event);
        return false;
    }

protected:

    // Центрируем текст в центре прямоугольника
    void centerText()
    {
        sf::FloatRect textBounds = mText.getLocalBounds();
        mText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);

        sf::FloatRect bounds = getBounds();
        sf::Vector2f rectCenter = {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};

        mText.setPosition(rectCenter);
    }

    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (checkIfContains(mousePosition)) 
            {
                mIsPressed = true;
                mColor = mPressedColor;
            }
        }
    }

    void onMouseMove(const sf::Event& event)
    {
        if (mIsPressed)
            return;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        if (checkIfContains(mousePosition))
            mColor = mHoverColor;
        else
            mColor = mDefaultColor;
    }

    bool onMouseReleased(const sf::Event& event)
    { 
        if (!mIsPressed)
            return false;

        mIsPressed = false;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (checkIfContains(mousePosition)) 
        {
            mColor = mHoverColor;
            return true;
        }
        else 
        {
            mColor = mDefaultColor;
            return false;
        }
    }
};