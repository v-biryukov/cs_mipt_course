/* 
    Программа, которая обрабатывает нажатия комбинаций клавиш.
    При нажатии на Alt + A кружок меняет свой цвет на красный.
    При нажатии на Ctrl + B кружок меняет свой цвет на зелёный.
    При нажатии на Shift + C кружок меняет свой цвет на синий.
*/

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "Key Combination Pressed");
    window.setFramerateLimit(60);

    sf::CircleShape circle(100);
    circle.setPosition({200, 200});

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A && event.key.alt)
                {
                    std::cout << "Alt + A is pressed" << std::endl;
                    circle.setFillColor(sf::Color::Red);
                }

                if (event.key.code == sf::Keyboard::B && event.key.control)
                {
                    std::cout << "Ctrl + B is pressed" << std::endl;
                    circle.setFillColor(sf::Color::Green);
                }

                if (event.key.code == sf::Keyboard::C && event.key.shift)
                {
                    std::cout << "Shift + C is pressed" << std::endl;
                    circle.setFillColor(sf::Color::Blue);
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}