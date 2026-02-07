/* 
    Программа, которая обрабатывает нажатие левой клавиши мыши.
    При нажатии на левую кнопку мыши кружок меняет положение на то в котором находится курсор.

    Также, при нажатии на левую кнопку на экране печатаются координаты пикселя (mousePixel) и 
    координаты мира (mousePosition).
*/

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mouse Button Pressed or Relesed");
    window.setFramerateLimit(60);

    sf::CircleShape circle(30);
    circle.setOrigin({30, 30});
    circle.setPosition({200, 200});

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePixel {event.mouseButton.x, event.mouseButton.y};
                    sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixel);

                    std::cout << "Left Mouse Button is pressed" << std::endl;
                    std::cout << "Mouse Pixel   : " << mousePixel.x << " " << mousePixel.y << std::endl;
                    std::cout << "Mouse Position: " << mousePosition.x << " " << mousePosition.y << std::endl;

                    circle.setPosition(mousePosition);
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}