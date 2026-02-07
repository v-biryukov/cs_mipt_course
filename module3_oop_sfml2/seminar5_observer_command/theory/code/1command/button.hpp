#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Класс кнопки (простейший)
class Button
{
private:
    // Цвета кнопки по умолчанию(default), при наведении(hover) и при нажатии(pressed)
    sf::Color mDefaultColor {179, 230, 255};
    sf::Color mHoverColor   {128, 212, 255};
    sf::Color mPressedColor {  0, 136, 204};


    // Объект кнопки содержит объект фигуры-прямоугольника
    // Внутри mShape хранятся координаты, размеры и текущий цвет прямоугольника, предствляющего нашу кнопку.
    sf::RectangleShape mShape {};

    // Также храним ссылку на окно SFML, на которое будем отрисовывать кнопку
    // Эту ссылку можно было не хранить, а просто передавать во все функции,
    // где окно понадобится, но тогда код был бы более громоздким
    sf::RenderWindow& mRenderWindow;
    
    // Когда кнопка находится в нажатом состоянии, 
    // то isPressed = true (Пользователь зажал кнопку и держит)
    bool mIsPressed;

public:

    // Конструктор: ссылки нужно обязательно инициализировать в списке инициализации
    Button(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size) 
            : mRenderWindow(window)
    {
        mShape.setPosition(position);
        mShape.setSize(size);
        mShape.setFillColor(mDefaultColor);
        mIsPressed = false;
    }

    // Метод, который рисует кнопку на холсте окна mRenderWindow
    void draw()
    {
        mRenderWindow.draw(mShape);
    }

    // Метод, который срабатывает каждый раз, когда двигается мышь
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

    // Метод, который срабатывает каждый раз, когда нажимется кнопка мыши
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

    // Метод, который срабатывает каждый раз, когда отпускается кнопка мыши
    // Возвращает true, если нажатие на кнопку произошло
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

    // Нужно вызвать лишь этот метод в цикле обработки событий
    // Возвращает true, если нажатие на кнопку произошло
    bool handleEvent(const sf::Event& event) 
    {
        if (event.type == sf::Event::MouseMoved) {
            onMouseMove(event);
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            onMousePressed(event);
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            return onMouseReleased(event);
        }
        return false;
    }
};