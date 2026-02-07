#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


class Button
{
private:
    // Цвета кнопки по умолчанию(default), при наведении(hover) и при нажатии(pressed)
    sf::Color mDefaultColor {179, 230, 255};
    sf::Color mHoverColor   {128, 212, 255};
    sf::Color mPressedColor {  0, 136, 204};

    // Объект кнопки содержит объект фигуры-прямоугольника
    // Внутри mShape хранятся координаты, размеры и текущий цвет прямоугольника (у кнопки они будут такими же)
    sf::RectangleShape mShape {};

    // Объкт текста, который хранит всё информаци о тексте на кнопке
    sf::Text mText {};

    // Когда кнопка находится в нажатом состоянии, 
    // то isPressed = true (Пользователь зажал кнопку и держит)
    bool mIsPressed {false};

    // Также храним ссылку на окно SFML, на которое будем отрисовывать кнопку
    // Эту ссылку можно было не хранить, а просто передавать во все функции,
    // где окно понадобится, но тогда код был бы более громоздким
    sf::RenderWindow& mRenderWindow;

public:

    Button(sf::RenderWindow& window, sf::FloatRect rect, sf::Font& font, const sf::String& textData) 
            : mRenderWindow{window}
    {
        mShape.setPosition({rect.left, rect.top});
        mShape.setSize({rect.width, rect.height});
        mShape.setFillColor(mDefaultColor);

        mText.setFont(font);
        mText.setString(textData);
        mText.setFillColor(sf::Color::Black);
        
        // Вычисляем оптимальный размер шрифта
        mText.setCharacterSize(30);
        auto calculateOptimalFontSize = [this]() 
        {
            float widthFraction = 0.85;
            float heightFraction = 0.7;

            sf::FloatRect textBounds = mText.getLocalBounds();
            float widthRatio = mShape.getSize().x / textBounds.width * widthFraction;
            float heightRatio = mShape.getSize().y / textBounds.height * heightFraction;
            float minRatio = std::min(widthRatio, heightRatio);

            unsigned int newSize = static_cast<unsigned int>(mText.getCharacterSize() * minRatio);
            return newSize;
        };
        mText.setCharacterSize(calculateOptimalFontSize());
        centerText();
    }

    void setFontSize(unsigned int fontSize)
    {
        mText.setCharacterSize(fontSize);
        centerText();
    }

    void draw() const
    {
        mRenderWindow.draw(mShape);
        mRenderWindow.draw(mText);
    }

    // Нужно вызвать лишь этот метод в цикле обработки событий
    // Возвращает true, если нажатие на кнопку произошло
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

private:

    // Центрируем текст в центре прямоугольника
    void centerText()
    {
        sf::FloatRect textBounds = mText.getLocalBounds();
        mText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        sf::Vector2f rectCenter = mShape.getPosition() + mShape.getSize() / 2.0f;
        mText.setPosition(rectCenter);
    }

    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mShape.getGlobalBounds().contains(mousePosition)) 
            {
                mIsPressed = true;
                mShape.setFillColor(mPressedColor);
            }
        }
    }

    void onMouseMove(const sf::Event& event)
    {
        if (mIsPressed)
            return;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        if (mShape.getGlobalBounds().contains(mousePosition))
            mShape.setFillColor(mHoverColor);
        else
            mShape.setFillColor(mDefaultColor);
    }

    bool onMouseReleased(const sf::Event& event)
    { 
        if (!mIsPressed)
            return false;

        mIsPressed = false;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (mShape.getGlobalBounds().contains(mousePosition)) 
        {
            mShape.setFillColor(mHoverColor);
            return true;
        }
        else 
        {
            mShape.setFillColor(mDefaultColor);
            return false;
        }
    }
};