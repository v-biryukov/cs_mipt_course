#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Button Class!", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("consolas.ttf")) 
    {
        std::cout << "Can't load button font" << std::endl;
        return 1;
    }

    RectangleButton rbutton(window, {350, 350}, {300, 160}, font, sf::String{"Rectangle"});
    CircleButton cbutton(window, {100, 450}, 100, font, sf::String{"Circle"});
    SmoothButton sbutton(window, {200, 50}, {300, 200}, 0.5, font, sf::String{"Smooth"});


    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (rbutton.handleEvent(event))
                std::cout << "Rectangle button clicked!" << std::endl;
            if (cbutton.handleEvent(event))
                std::cout << "Circle button clicked!" << std::endl;
            if (sbutton.handleEvent(event))
                std::cout << "Smooth button clicked!" << std::endl;
        }

        window.clear(sf::Color::Black);
        rbutton.draw();
        cbutton.draw();
        sbutton.draw();
        window.display();
    }
}