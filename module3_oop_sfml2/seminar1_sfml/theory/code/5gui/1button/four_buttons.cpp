#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Buttons to move a circle!");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50);
    circle.setOrigin({30, 30});
    circle.setPosition({400, 400});
    circle.setFillColor(sf::Color::Green);

    std::vector buttons
    {
        Button{window, {200, 600}, {100, 70}},
        Button{window, {500, 600}, {100, 70}},
        Button{window, {350, 500}, {100, 70}},
        Button{window, {350, 700}, {100, 70}}
    };

    float step = 100;
    std::vector directions
    {
        sf::Vector2f{-step, 0.0f},
        sf::Vector2f{+step, 0.0f},
        sf::Vector2f{0.0f, -step},
        sf::Vector2f{0.0f, +step},
    };

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            for (int i = 0; i < 4; ++i) 
            {
                if (buttons[i].handleEvent(event))
                    circle.move(directions[i]);
            }
        }

        window.clear(sf::Color::Black);

        for (auto& button : buttons)
            button.draw();

        window.draw(circle);
        window.display();
    }
}