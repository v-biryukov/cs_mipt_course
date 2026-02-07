/*
    Программа рисует один шарик, двигающийся с постоянным ускорением, 
    но если шарик выходит за границы окна, он появляется с другой стороны.

    Для того, чтобы добиться ускоренного движения шарика будем хранить его скорость и ускорение
    в отдельных переменных ballVelocity и ballAcceleration. Положение шарика уже хранится внутри 
    объекта sf::CircleShape, поэтому отдельно его хранить необязательно.

    Также, для удобства, заведём переменную dt - время между итерациями в секундах.
    Так как fps=60, то dt будет иметь значение 1/60 секунды.
    Теперь значение скорости будет иметь понятный смысл. Например, скорость 100 в этой программе будет означать, 
    что шарик преодолеет 100 пикселей за 1 секунду реального времени.

    После этого применяем формулы движения:

        v += a * dt
        r += v * dt

    В коде это будет выглядеть вот так:

        ballVelocity += ballAcceleration * dt;
        ball.move(ballVelocity * dt);
*/


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Moving Ball Cycle Accelerated ", sf::Style::Default);
    window.setFramerateLimit(60);
    
    sf::CircleShape ball(30);
    ball.setOrigin(sf::Vector2f{30, 30});
    ball.setPosition(sf::Vector2f{100, 100});

    sf::Vector2f ballVelocity {0, 0};
    sf::Vector2f ballAcceleration {10, 3};
    float dt = 1.0f / 60;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        ballVelocity += ballAcceleration * dt;
        ball.move(ballVelocity * dt);

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