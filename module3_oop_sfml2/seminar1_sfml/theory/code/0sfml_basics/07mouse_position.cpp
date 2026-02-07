/* 
    Программа, которая рисует круг.
    При зажатии левой кнопки мыши, круг будет рисоваться в том месте, где находится мышь.
*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Moving Circle when Left Mouse Button is pressed");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (window.hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i positionInPixels = sf::Mouse::getPosition(window);
            sf::Vector2f position = window.mapPixelToCoords(positionInPixels);
            circle.setPosition(position);
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}