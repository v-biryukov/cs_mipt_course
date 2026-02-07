#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


class Slider
{
protected:
    sf::RectangleShape mTrackShape {};
    sf::RectangleShape mThumbShape {};

    // Когда слайдер находится в нажатом состоянии, 
    // то isPressed = true (Пользователь зажал thumb и держит)
    bool mIsPressed {false};

    // Также храним ссылку на окно SFML, на которое будем отрисовывать слайдер
    // Эту ссылку можно было не хранить, а просто передавать во все функции,
    // где окно понадобится, но тогда код был бы более громоздким
    sf::RenderWindow& mRenderWindow;

public:
    Slider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, sf::Vector2f thumbSize) 
            : mRenderWindow(window)
    {
        mTrackShape.setSize(trackSize);
        mTrackShape.setOrigin(trackSize / 2.0f);
        mTrackShape.setPosition(centerPosition);
        mTrackShape.setFillColor({200, 200, 220});

        mThumbShape.setSize(thumbSize);
        mThumbShape.setOrigin(thumbSize / 2.0f);
        mThumbShape.setPosition(centerPosition);
        mThumbShape.setFillColor({150, 150, 240});
    }

    void draw()
    {
        mRenderWindow.draw(mTrackShape);
        mRenderWindow.draw(mThumbShape);
    }

    void setRestrictedThumbPosition(sf::Vector2f position)
    {
        float min = mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.0f;
        float max = mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.0f;
        mThumbShape.setPosition({std::clamp(position.x, min, max), mThumbShape.getPosition().y});
    }

    bool onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mThumbShape.getGlobalBounds().contains(mousePosition) || mTrackShape.getGlobalBounds().contains(mousePosition)) 
            {
                mIsPressed = true;
                setRestrictedThumbPosition({mousePosition.x, mThumbShape.getPosition().y});
            }
        }
        return mIsPressed;
    }

    void onMouseMove(const sf::Event& event)
    {
        if (!mIsPressed)
            return;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        setRestrictedThumbPosition(mousePosition);
    }

    void onMouseReleased()
    { 
        mIsPressed = false;
    }

    // Нужно вызвать лишь этот метод в цикле обработки событий.
    // Возвращает true, если за время последнего кадра произошло нажатие на ползунок.
    bool handleEvent(const sf::Event& event) 
    {
        bool result = false;

        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            result = onMousePressed(event);
        else if (event.type == sf::Event::MouseButtonReleased)
            onMouseReleased();

        return result;
    }

    bool isPressed() const
    {
        return mIsPressed;
    }

    float getValue() const
    {
        float start = mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.0f;
        float finish = mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.0f;
        float position = mThumbShape.getPosition().x;
        return 100.0f * (position - start) / (finish - start);
    }

};