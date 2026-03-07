#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "draggable.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Draggable + inheritance", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    RectangleDraggable d {window, {300, 300}, {200, 400}, {80, 120, 60}};
    CircleDraggable c {window, {500, 500}, 100, {80, 80, 120}};


    SmoothDraggable s {window, {500, 100}, {300, 200}, 0.6, {150, 120, 60}};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            d.handleEvent(event);
            c.handleEvent(event);
            s.handleEvent(event);

        }
        
        window.clear(sf::Color::Black);
        d.draw();
        c.draw();
        s.draw();
        window.display();
    }
}