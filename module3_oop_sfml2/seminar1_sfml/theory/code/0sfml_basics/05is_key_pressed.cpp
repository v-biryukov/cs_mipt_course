/* 
    Программа, которая рисует круг, движущийся когда нажата клавиша Пробел
*/

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Moving Circle when Space is pressed");
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
        
        if (window.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
            circle.move({2, 2});

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
}