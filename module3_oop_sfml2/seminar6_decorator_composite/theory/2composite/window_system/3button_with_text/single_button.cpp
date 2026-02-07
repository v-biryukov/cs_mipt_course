#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Button Class!");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../sourceCodePro.ttf")) 
    {
        std::cout << "Error: Font file not found." << std::endl;
        std::exit(1);
    }

    Button button(window, {300, 250, 360, 60}, font, "Hello world!");

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            bool isButtonActivated = button.handleEvent(event);
            if (isButtonActivated)
                std::cout << "Button clicked!" << std::endl;
        }

        window.clear(sf::Color::Black);
        button.draw();
        window.display();
    }
}