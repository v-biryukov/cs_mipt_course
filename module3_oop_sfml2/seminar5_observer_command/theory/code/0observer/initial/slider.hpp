#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Класс слайдера
class Slider
{
private:
    sf::RectangleShape mTrackShape {};
    sf::RectangleShape mThumbShape {};

    sf::Color mTrackColor           {200, 200, 220};
    sf::Color mThumbColor           {150, 150, 240};

    // Также храним ссылку на окно SFML, на которое будем отрисовывать слайдер
    // Эту ссылку можно было не хранить, а просто передавать во все функции,
    // где окно понадобится, но тогда код был бы более громоздким
    sf::RenderWindow& mSfmlWindow;

    // Когда слайдер находится в нажатом состоянии, 
    // то isPressed = true (Пользователь зажал thumb и держит)
    bool mIsPressed {false};

public:

    // Конструктор: ссылки нужно обязательно инициализировать в списке инициализации
    Slider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, sf::Vector2f thumbSize) 
            : mSfmlWindow(window)
    {
        mTrackShape.setSize(trackSize);
        mTrackShape.setOrigin(trackSize / 2.0f);
        mTrackShape.setPosition(centerPosition);
        mTrackShape.setFillColor(mTrackColor);

        mThumbShape.setSize(thumbSize);
        mThumbShape.setOrigin(thumbSize / 2.0f);
        mThumbShape.setPosition(centerPosition);
        mThumbShape.setFillColor(mThumbColor);
    }

    // Метод, который рисует кнопку на холсте окна mSfmlWindow
    void draw()
    {
        mSfmlWindow.draw(mTrackShape);
        mSfmlWindow.draw(mThumbShape);
    }

    // Метод, который срабатывает каждый раз, когда двигается мышь
    void onMouseMove(const sf::Event& event)
    {
        if (!mIsPressed)
            return;

        sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        float min = mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.0f;
        float max = mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.0f;

        mThumbShape.setPosition({std::clamp(mousePosition.x, min, max), mThumbShape.getPosition().y});
    }

    // Метод, который срабатывает каждый раз, когда нажимется кнопка мыши
    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mThumbShape.getGlobalBounds().contains(mousePosition) || mTrackShape.getGlobalBounds().contains(mousePosition)) 
            {
                mIsPressed = true;
                mThumbShape.setPosition({mousePosition.x, mThumbShape.getPosition().y});
            }
        }
    }

    // Метод, который срабатывает каждый раз, когда отпускается кнопка мыши
    void onMouseReleased(const sf::Event& event)
    { 
        mIsPressed = false;
    }

    // Нужно вызвать лишь этот метод в цикле обработки событий
    void handleEvent(const sf::Event& event) 
    {
        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        
        else if (event.type == sf::Event::MouseButtonPressed)
            onMousePressed(event);
        
        else if (event.type == sf::Event::MouseButtonReleased)
            onMouseReleased(event);
    }
};