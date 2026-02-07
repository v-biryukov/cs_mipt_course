#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "slider.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Slider Class!");
    window.setFramerateLimit(60);

    Slider slider(window, {400, 400}, {500, 20}, {25, 90});

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            slider.handleEvent(event);

            if (event.type == sf::Event::MouseMoved && slider.isPressed())
                std::cout << slider.getValue() << std::endl;
        }

        window.clear(sf::Color::Black);
        slider.draw();
        window.display();
    }

    return 0;
}