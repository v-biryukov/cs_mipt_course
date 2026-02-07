#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Button Class!");
    window.setFramerateLimit(60);

    Button button(window, {300, 450}, {200, 100});
    sf::CircleShape circle(50);
    circle.setPosition({100, 200});
    circle.setFillColor(sf::Color::Green);
    float circleDirection = 1.0f;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            bool isButtonActivated = button.handleEvent(event);
            if (isButtonActivated)
            {
                std::cout << "Button pressed!" << std::endl;
                circle.move({100 * circleDirection, 0});
                if (circle.getPosition().x >= 700 || circle.getPosition().x <= 0)
                    circleDirection *= -1;
            }
        }

        window.clear(sf::Color::Black);
        button.draw();
        window.draw(circle);

        window.display();
    }
}