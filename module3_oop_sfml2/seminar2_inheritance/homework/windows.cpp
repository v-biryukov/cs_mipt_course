#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class BaseWindow
{
private:

    static constexpr float dragAreaHeight = 30.0f;

    sf::RenderWindow& mSfmlWindow;
    sf::RectangleShape mBaseRect {};
    sf::RectangleShape mDragRect {};

    bool mIsDragged {false};

    sf::Vector2f mDragBaseDistance {};
    sf::Vector2f mOffset {};

public:

    BaseWindow(sf::RenderWindow& window, sf::FloatRect borders)
        : mSfmlWindow(window)
    {
        mDragRect.setPosition({borders.left, borders.top});
        mDragRect.setSize({borders.width, dragAreaHeight});

        mBaseRect.setPosition({borders.left, borders.top + dragAreaHeight});
        mBaseRect.setSize({borders.width, borders.height - dragAreaHeight});

        mDragRect.setFillColor({200, 200, 200});
        mBaseRect.setFillColor({255, 255, 255});

        mDragBaseDistance = mDragRect.getPosition() - mBaseRect.getPosition();
    }

    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mDragRect.getGlobalBounds().contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mDragRect.getPosition();
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
        {
            mDragRect.setPosition(mousePosition - mOffset);
            mBaseRect.setPosition(mDragRect.getPosition() - mDragBaseDistance);
        }
    }

    void handleEvents(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMousePressed(mousePosition);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMouseReleased();
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePosition);
        }
    }

    void setBaseColor(sf::Color c)      {mBaseRect.setFillColor(c);}
    void setBaseSize(sf::Vector2f sz)   {mBaseRect.setSize(sz);}
    void setDragColor(sf::Color c)      {mDragRect.setFillColor(c);}
    void setDragSize(sf::Vector2f sz)   {mDragRect.setSize(sz);}

    void setPosition(sf::Vector2f p)
    {
        mBaseRect.setPosition(p);
        mDragRect.setPosition(mBaseRect.getPosition() + mDragBaseDistance);
    }

    void draw() const
    {
        mSfmlWindow.draw(mBaseRect);
        mSfmlWindow.draw(mDragRect);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Windows");
    window.setFramerateLimit(60);

    BaseWindow bw1(window, {100, 200, 300, 200});
    bw1.setBaseColor({100, 50, 90});
    bw1.setDragColor({200, 200, 150});

    BaseWindow bw2(window, {500, 100, 200, 400});
    bw2.setBaseColor({240, 240, 240});
    bw2.setDragColor({150, 150, 150});


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            bw1.handleEvents(event);
            bw2.handleEvents(event);
        }
        
        window.clear(sf::Color::Black);
        bw1.draw();
        bw2.draw();
        window.display();
    }
}