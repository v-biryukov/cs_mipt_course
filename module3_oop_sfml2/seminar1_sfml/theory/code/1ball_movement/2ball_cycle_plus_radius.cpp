/*
    Программа рисует один шарик, двигающийся с постоянной скоростью, но если шарик выходит 
    за границы окна, он появляется с другой стороны.

    В предыдущей программе было видно перемещение шарика к другой стороне окна, так как мы 
    перемещали шарик, когда координаты центры шарика превышали размеры экрана.
    При этом половинка шарика была ещё видна.
    Нужно перемещать шарик только тогда, когда он полностью скроется из вида.
    Для этого нужно учесть размеры щарика, то есть его радиус.
*/


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Moving Ball Cycle", sf::Style::Default);
    window.setFramerateLimit(60);
    
    sf::CircleShape ball(30);
    ball.setOrigin(sf::Vector2f{ball.getRadius(), ball.getRadius()});
    ball.setPosition(sf::Vector2f{100, 100});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        ball.move(sf::Vector2f{10, 5});

        sf::Vector2f max = window.getView().getSize();
        if (ball.getPosition().x - ball.getRadius() > max.x)
            ball.move({-max.x - 2 * ball.getRadius(), 0});
        if (ball.getPosition().y - ball.getRadius() > max.y)
            ball.move({0, -max.y - 2 * ball.getRadius()});

        window.clear(sf::Color::Black);
        window.draw(ball);

        window.display();
    }
}