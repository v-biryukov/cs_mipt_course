/* 
    Программа, которая обрабатывает нажатия и отпускания клавиш.
    При нажатии на левую кнопку мыши кружок меняет свой цвет на красный.
    При отпускании левой кнопки мыши кружок меняет свой цвет на белый.
*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Mouse Button Pressed or Relesed");
    window.setFramerateLimit(60);
    sf::CircleShape circle(200);
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
                    circle.setFillColor(sf::Color::Red);
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    circle.setFillColor(sf::Color::White);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}