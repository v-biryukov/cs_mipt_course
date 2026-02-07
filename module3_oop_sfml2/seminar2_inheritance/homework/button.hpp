#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Класс кнопки
class Button
{
private:
    // Статические поля класса, это поля общие для всех экземпляров класса
    inline static const sf::Color sDefaultColor {220, 220, 220};
    inline static const sf::Color sHoverColor   {180, 200, 180};
    inline static const sf::Color sPressedColor {140, 160, 140};
    inline static sf::RectangleShape sShape {};

    // Тонкий момент: мы храним ссылку на шрифт sf::Font
    // Шрифт может занимать много памяти
    // Чтобы не копировать его для каждой кнопки, мы храним ссылку
    sf::Font& mFont;

    // Также храним ссылку на окно SFML, на которое будем отрисовывать кнопку
    // Эту ссылку можно было не хранить, а просто передавать во все функции,
    // где окно понадобится, но тогда код был бы более громоздким
    sf::RenderWindow& mSfmlWindow;

    // Текст, границы прямоугольника и текущий цвет кнопки
    sf::Text mText;
    sf::FloatRect mRect;
    sf::Color mCurrentColor;
    
    // Когда кнопка находится в нажатом состоянии, 
    // то isPressed = true (Пользователь зажал кнопку и держит)
    bool mIsPressed;

public:

    // Конструктор: ссылки нужно обязательно инициализировать в списке инициализации
    Button(sf::RenderWindow& window, sf::FloatRect rect, sf::Font& font, int fontSize, const sf::String& textData) 
            : mFont(font), mSfmlWindow(window), mRect(rect)
    {
        mText.setFont(mFont);
        mText.setString(textData);
        mText.setCharacterSize(fontSize);
        mText.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = mText.getLocalBounds();

        mText.setPosition(mRect.left + (mRect.width - textRect.width) / 2, 
                         mRect.top  + (mRect.height - textRect.height) / 2);

        mCurrentColor = sDefaultColor;
        mIsPressed = false;
    }

    // Метод, который рисует кнопку на холсте окна mSfmlWindow
    void draw()
    {
        sShape.setPosition({mRect.left, mRect.top});
        sShape.setSize({mRect.width, mRect.height});
        sShape.setFillColor(mCurrentColor);
        mSfmlWindow.draw(sShape);
        mSfmlWindow.draw(mText);
    }

    // Метод, который срабатывает каждый раз, когда двигается мышь
    void onMouseMove(const sf::Event& event)
    {
        if (mIsPressed) {
            return;
        }
        sf::Vector2f mouseCoords = mSfmlWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        if (mRect.contains(mouseCoords)) {
            mCurrentColor = sHoverColor;
        }
        else {
            mCurrentColor = sDefaultColor;
        }
    }

    // Метод, который срабатывает каждый раз, когда нажимется кнопка мыши
    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mouseCoords = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mRect.contains(mouseCoords)) {
                mIsPressed = true;
                mCurrentColor = sPressedColor;
            }
        }
    }

    // Метод, который срабатывает каждый раз, когда отпускается кнопка мыши
    // Возвращает true, если нажатие на кнопку произошло
    bool onMouseReleased(const sf::Event& event)
    { 
        if (!mIsPressed) {
            return false;
        }
        mIsPressed = false;

        sf::Vector2f mouseCoords = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (mRect.contains(mouseCoords)) {
            mCurrentColor = sHoverColor;
            return true;
        }
        else {
            mCurrentColor = sDefaultColor;
            return false;
        }
    }

    // Нужно вызвать лишь этот метод в цикле обработки событий
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