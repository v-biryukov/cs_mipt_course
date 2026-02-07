#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "draggable.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Draggable");
    window.setFramerateLimit(60);

    Draggable d {window, {100, 100}, {200, 400}, {80, 80, 120}};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            d.handleEvent(event);
        }
        
        window.clear(sf::Color::Black);
        d.draw();
        window.display();
    }
}