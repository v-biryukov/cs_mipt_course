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

    Button button(window, {350, 350}, new SmoothDesign{{300, 160}, 0.5}, font, sf::String{"Rectangle"});
    //CircleButton cbutton(window, {100, 450}, 100, font, sf::String{"Circle"});
    //SmoothButton sbutton(window, {200, 50}, {300, 200}, 0.5, font, sf::String{"Smooth"});


    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (button.handleEvent(event))
                std::cout << "Rectangle button clicked!" << std::endl;
        }

        window.clear(sf::Color::Black);
        button.draw();
        window.display();
    }
}