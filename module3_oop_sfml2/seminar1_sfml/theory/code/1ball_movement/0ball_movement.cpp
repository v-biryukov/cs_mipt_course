/*
    Программа рисует один шарик, двигающийся с постоянной скоростью.

    Шарик радиуса 30 начинает движение из точки (100, 100) (верхний левый угол окна)
    и двигается со скоростью, чей вектор задаётся значением (1, 1) 
    (то есть вектор скорости направлен по диагонали вниз вправо).

    Так как частота кадров в секунду ограничена значением 60, а скорость шарика равна (1, 1), то
    за 1 секунду реального времени шарик переместится из точки (100, 100) в точку (160, 160).

    После того, как шарик достигнет края окна, он продолжит движение дальше и уже не будет виден.
*/


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Moving Ball", sf::Style::Default);
    window.setFramerateLimit(60);
    
    sf::CircleShape ball(30);
    ball.setOrigin(sf::Vector2f{30, 30});
    ball.setPosition(sf::Vector2f{100, 100});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ball.move(sf::Vector2f{1, 1});

        window.clear(sf::Color::Black);
        window.draw(ball);

        window.display();
    }
}