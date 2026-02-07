/* 
    Программа, которая рисует круг, движущийся когда нажата левая кнопка мыши
*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Moving Circle when Left Mouse Button is pressed");
    window.setFramerateLimit(60);

    sf::CircleShape circle(20);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (window.hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            circle.move({2, 2});

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}