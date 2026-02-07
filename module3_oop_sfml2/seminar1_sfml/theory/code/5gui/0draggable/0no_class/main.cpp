#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Draggable");
    window.setFramerateLimit(60);

    sf::RectangleShape draggableShape {{200, 400}};
    draggableShape.setPosition({100, 100});
    draggableShape.setFillColor({80, 80, 120});

    bool isDragged = false;
    sf::Vector2f offset;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if (draggableShape.getGlobalBounds().contains(mousePosition))
                {
                    isDragged = true;
                    offset = mousePosition - draggableShape.getPosition();
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                isDragged = false;
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                if (isDragged)
                {
                    draggableShape.setPosition(mousePosition - offset);
                }
            }
        }
        
        window.clear(sf::Color::Black);
        window.draw(draggableShape);
        window.display();
    }
}