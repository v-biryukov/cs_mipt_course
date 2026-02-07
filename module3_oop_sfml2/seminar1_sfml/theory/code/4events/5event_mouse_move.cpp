/* 
    Программа, которая обрабатывает перемещение курсора мыши.
    При нажатии на левую кнопку мыши кружок меняет положение на то в котором находится курсор.

    Также, при перемещении курсора мыши на экране печатаются координаты пикселя (mousePixel) и 
    координаты мира (mousePosition).


    Обратите внимание, что координаты курсора мыши в данном событии хранятся в других полях класса event.

    В случаи событий sf::Event::MouseButtonPressed и sf::Event::MouseButtonReleased координаты хранились
    в полях event.mouseButton.x и event.mouseButton.y.

    В случаи события sf::Event::MouseMoved координаты хранятся в полях event.mouseMove.x и event.mouseMove.y.
*/

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Mouse Button Move Coordinates");
    window.setFramerateLimit(60);

    sf::CircleShape circle(30);
    circle.setOrigin({circle.getRadius(), circle.getRadius()});
    circle.setPosition({400, 400});

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePixel {event.mouseMove.x, event.mouseMove.y};
                sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixel);

                std::cout << "Left Mouse Button is pressed" << std::endl;
                std::cout << "Mouse Pixel   : " << mousePixel.x << " " << mousePixel.y << std::endl;
                std::cout << "Mouse Position: " << mousePosition.x << " " << mousePosition.y << std::endl;

                circle.setPosition(mousePosition);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}