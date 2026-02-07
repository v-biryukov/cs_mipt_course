/* 
    Программа, которая обрабатывает нажатия клавиш пробел (Space).
    При нажатии на Пробел передвигается на 50 пикселей вправо.
*/

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Key Pressed Event");
    window.setFramerateLimit(60);

    sf::CircleShape circle(50);
    circle.setOrigin({circle.getRadius(), circle.getRadius()});
    circle.setPosition({100, 400});

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    std::cout << "Space is pressed" << std::endl;
                    circle.move({50, 0});
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}
