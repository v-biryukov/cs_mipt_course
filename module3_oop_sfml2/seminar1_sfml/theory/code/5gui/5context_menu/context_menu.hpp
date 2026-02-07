#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


/*
    Класс ContextMenu - контекстное меню
    При нажатии правой кнопки мыши на экране появляется контекстное меню

    Публичные методы:
        ContextMenu(sf::RenderWindow&, const sf::Font&)
            Конструктор принимает окно для отрисовки и шрифт

        void addButton(const sf::String& name)
            Добавить новый элемент в контекстное меню по имени name

        void draw()
            Нарисовать контекстное меню в окне, которое было передано в конструктор

        int handleEvent(const sf::Event& event)
            Обрабатывает событие event и возвращает целое число
            Если это событие MousePressed и был выбран один из вариантов
            контекстного меню, то вернёт номер этого варианта
            Нумерация начинается с нуля
            В ином случае вернёт -1

*/


class ContextMenu
{
private:
    inline static const sf::Color kDefaultColor {sf::Color(190, 210, 190)};
    inline static const sf::Color kHoverColor {sf::Color(150, 170, 150)};
    inline static const sf::Color kTextColor {sf::Color::Black};
    inline static const int kButtonHeight = 20;
    inline static const int kCharacterSize = 16;
    inline static const float kMenuWidthMultiplier = 1.2;

    sf::RenderWindow& mRenderWindow;
    sf::RectangleShape mShape;
    sf::RectangleShape mHoverShape;
    sf::Text mText;
    std::vector<sf::String> mButtons;

    bool mIsOpened = false;
    bool mIsUpdated = false;
    int mHoverPosition = -1;

    int onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Right) 
        {
            mIsOpened = true;
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            mShape.setPosition(mousePosition);
        }
        if (event.mouseButton.button == sf::Mouse::Left && mIsOpened) 
        {
            mIsOpened = false;
            return mHoverPosition;
        }
        return -1;
    }

    void onMouseMove(const sf::Event& event)
    {
        if (!mIsOpened)
            return;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        if (mShape.getGlobalBounds().contains(mousePosition))
            mHoverPosition = (mousePosition.y - mShape.getPosition().y) / kButtonHeight;
        else
            mHoverPosition = -1;
    }

public:

    ContextMenu(sf::RenderWindow& window, const sf::Font& font) : mRenderWindow(window)
    {   
        mText.setFont(font);
        mText.setCharacterSize(kCharacterSize);
        mText.setFillColor(kTextColor);
        mShape.setFillColor(kDefaultColor);
        mHoverShape.setFillColor(kHoverColor);

        mIsOpened = false;
        mIsUpdated = false;
        mHoverPosition = -1;
    }

    void addButton(const sf::String& name)
    {
        mButtons.push_back(name);
        mIsUpdated = false;
    }

    void draw()
    {
        if (!mIsOpened)
            return;

        // Если добавили новый вариант, то её текст может быть длиннее
        // чем у других. Нужно расширить прямоугольники.
        if (!mIsUpdated) 
        {
            int maxSizeX = 0;
            for (int i = 0; i < mButtons.size(); i++) 
            {
                mText.setString(mButtons[i]);
                if (mText.getLocalBounds().width > maxSizeX)
                    maxSizeX = mText.getLocalBounds().width;
            }
            maxSizeX *= kMenuWidthMultiplier;
            mShape.setSize({(float)maxSizeX, (float)(kButtonHeight * mButtons.size())});
            mHoverShape.setSize({(float)maxSizeX, (float)(kButtonHeight)});
            mIsUpdated = true;
        }

        mRenderWindow.draw(mShape);
        if (mHoverPosition >= 0)
        {
            mHoverShape.setPosition(mShape.getPosition().x, mShape.getPosition().y + mHoverPosition * kButtonHeight);
            mRenderWindow.draw(mHoverShape);
        }
        for (int i = 0; i < mButtons.size(); i++) 
        {
            mText.setString(mButtons[i]);
            mText.setPosition(mShape.getPosition().x, mShape.getPosition().y + i * kButtonHeight);
            mRenderWindow.draw(mText);
        }
    }

    int handleEvent(const sf::Event& event) 
    {
        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            return onMousePressed(event);
        return -1;
    }

};