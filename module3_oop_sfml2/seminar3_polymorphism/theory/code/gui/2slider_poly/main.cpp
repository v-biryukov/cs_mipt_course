#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "slider.hpp"

int main()
{
    sf::ContextSettings contextSettngs;
    contextSettngs.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Slider Class!", sf::Style::Default, contextSettngs);
    window.setFramerateLimit(60);

    RectangleSlider rslider(window, {400, 400}, {500, 20}, {25, 90});
    CircleSlider cslider(window, {400, 200}, {500, 20}, 40);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            rslider.handleEvent(event);
            cslider.handleEvent(event);

            if (event.type == sf::Event::MouseMoved && (rslider.isPressed() || cslider.isPressed()))
                std::cout << rslider.getValue() << " " << cslider.getValue() << std::endl;
        }

        window.clear(sf::Color::Black);
        rslider.draw();
        cslider.draw();
        window.display();
    }

    return 0;
}