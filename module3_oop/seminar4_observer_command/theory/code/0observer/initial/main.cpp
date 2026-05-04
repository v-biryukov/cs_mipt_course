#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "slider.hpp"

class Circle
{
private:

    sf::CircleShape mShape;
    sf::RenderWindow& mSfmlWindow;

public:

    Circle(sf::RenderWindow& window, sf::Vector2f position, float radius) 
    : mSfmlWindow(window), mShape(radius)
    {
        mShape.setOrigin({radius, radius});
        mShape.setPosition(position);
        mShape.setFillColor(sf::Color::Green);
    }

    void draw() const
    {
        mSfmlWindow.draw(mShape);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Slider Class!");
    window.setFramerateLimit(60);

    Slider slider(window, {400, 500}, {500, 20}, {25, 90});
    Circle circle(window, {400, 300}, 50);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            slider.handleEvent(event);
        }

        window.clear(sf::Color::Black);
        slider.draw();
        circle.draw();
        window.display();
    }

    return 0;
}