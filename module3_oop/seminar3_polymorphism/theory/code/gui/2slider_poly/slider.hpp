#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Класс слайдера
class Slider
{
protected:
    sf::Vector2f mTrackPosition {};
    sf::Vector2f mThumbPosition {};

    sf::Vector2f mTrackSize {};
    sf::Vector2f mThumbSize {};

    sf::Color mTrackColor {};
    sf::Color mThumbColor {};

    // Когда слайдер находится в нажатом состоянии, 
    // то isPressed = true (Пользователь зажал thumb и держит)
    bool mIsPressed {false};

    // Также храним ссылку на окно SFML, на которое будем отрисовывать слайдер
    // Эту ссылку можно было не хранить, а просто передавать во все функции,
    // где окно понадобится, но тогда код был бы более громоздким
    sf::RenderWindow& mRenderWindow;

public:

    // Конструктор: ссылки нужно обязательно инициализировать в списке инициализации
    Slider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, sf::Vector2f thumbSize) 
            : mRenderWindow(window)
    {
        mTrackSize = trackSize;
        mTrackPosition = centerPosition;
        mTrackColor = sf::Color{200, 200, 220};


        mThumbSize = thumbSize;
        mThumbPosition = centerPosition;
        mThumbColor = sf::Color{150, 150, 240};
    }

    // Метод, который рисует кнопку на холсте окна mRenderWindow
    virtual void draw() const = 0;

    void setRestrictedThumbPosition(sf::Vector2f position)
    {
        float min = mTrackPosition.x - mTrackSize.x / 2.0f;
        float max = mTrackPosition.x + mTrackSize.x / 2.0f;
        mThumbPosition = sf::Vector2f{std::clamp(position.x, min, max), mThumbPosition.y};
    }

    virtual bool isTrackContains(sf::Vector2f position) const = 0;
    virtual bool isThumbContains(sf::Vector2f position) const = 0;


    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (isTrackContains(mousePosition) || isThumbContains(mousePosition)) 
            {
                mIsPressed = true;
                setRestrictedThumbPosition({mousePosition.x, mThumbPosition.y});
            }
        }
    }

    void onMouseMove(const sf::Event& event)
    {
        if (!mIsPressed)
            return;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        setRestrictedThumbPosition(mousePosition);
    }

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

    bool isPressed() const
    {
        return mIsPressed;
    }

    float getValue() const
    {
        float start = mTrackPosition.x - mTrackSize.x / 2.0f;
        float finish = mTrackPosition.x + mTrackSize.x / 2.0f;
        float position = mThumbPosition.x;
        return 100.0f * (position - start) / (finish - start);
    }

};




class RectangleSlider : public Slider
{
public:

    RectangleSlider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, sf::Vector2f thumbSize)
    : Slider(window, centerPosition, trackSize, thumbSize) {}

    void draw() const override
    {
        static sf::RectangleShape mTrackShape {};
        static sf::RectangleShape mThumbShape {};

        mTrackShape.setSize(mTrackSize);
        mTrackShape.setOrigin(mTrackSize / 2.0f);
        mTrackShape.setPosition(mTrackPosition);
        mTrackShape.setFillColor(mTrackColor);

        mThumbShape.setSize(mThumbSize);
        mThumbShape.setOrigin(mThumbSize / 2.0f);
        mThumbShape.setPosition(mThumbPosition);
        mThumbShape.setFillColor(mThumbColor);

        mRenderWindow.draw(mTrackShape);
        mRenderWindow.draw(mThumbShape);
    }


    virtual bool isTrackContains(sf::Vector2f position) const override
    {
        sf::FloatRect rect {mTrackPosition.x - mTrackSize.x / 2.f, mTrackPosition.y - mTrackSize.y / 2.f, mTrackSize.x, mTrackSize.y};
        return rect.contains(position);
    }

    virtual bool isThumbContains(sf::Vector2f position) const override
    {
        sf::FloatRect rect {mThumbPosition.x - mThumbSize.x / 2.f, mThumbPosition.y - mThumbSize.y / 2.f, mThumbSize.x, mThumbSize.y};
        return rect.contains(position);
    }
};


class CircleSlider : public Slider
{
public:

    CircleSlider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, float thumbRadius)
    : Slider(window, centerPosition, trackSize, {2 * thumbRadius, 2 * thumbRadius}) {}

    void draw() const override
    {
        static sf::RectangleShape mTrackShape {};
        mTrackShape.setSize(mTrackSize);
        mTrackShape.setOrigin(mTrackSize / 2.f);
        mTrackShape.setPosition(mTrackPosition);
        mTrackShape.setFillColor(mTrackColor);
        mRenderWindow.draw(mTrackShape);

        float thumbRadius = mThumbSize.x / 2.f;
        static sf::CircleShape mThumbShape {};
        mThumbShape.setRadius(thumbRadius);
        mThumbShape.setOrigin({thumbRadius, thumbRadius});
        mThumbShape.setPosition(mThumbPosition);
        mThumbShape.setFillColor(mThumbColor);
        mRenderWindow.draw(mThumbShape);
    }


    virtual bool isTrackContains(sf::Vector2f position) const override
    {
        sf::FloatRect rect {mTrackPosition.x, mTrackPosition.y, mTrackSize.x, mTrackSize.y};
        return rect.contains(position);
    }

    virtual bool isThumbContains(sf::Vector2f position) const override
    {
        float squaredDistance = (mThumbPosition.x - position.x) * (mThumbPosition.x - position.x) +  (mThumbPosition.y - position.y) * (mThumbPosition.y - position.y);
        float thumbRadius = mThumbSize.x / 2.f;
        return squaredDistance < thumbRadius * thumbRadius;
    }
};