/*
    Программа рисует один шарик, двигающийся в поле гравитации, 
    но если шарик достигает границ окна, то он НЕупруго отскакивает от границ окна.

    Попытаемся реализовать неупругие столкновения шарика со стенками как можно проще.
    Введём переменную:

        float ballDecay = 0.95;

    и будем умножать скорость шарика, на эту величину при каждом столкновении.
    Таким образом, после каждого столкновения шарик будет двигаться всё медленнее и медленнее.

    Сначала всё работает хорошо, но затем шарик "прилипает" к стенке или полу и "просачивается" через границу.
    Если увеличить скорость шарика, то он начнёт "прилипать" к стенке гораздо раньше.
    Почему это происходит и как это исправить?
*/


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Collisions, Gravity and Decay", sf::Style::Default);
    window.setFramerateLimit(60);
 
    sf::CircleShape ball(30);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition(sf::Vector2f{100, 100});

    sf::Vector2f ballVelocity {1200, 0};
    sf::Vector2f ballAcceleration {0, 1000};
    float dt = 1.0f / 60;
    float ballDecay = 0.95;

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
        if (ball.getPosition().x + ball.getRadius() > max.x)
        {
            ballVelocity.x *= -1;
            ballVelocity *= ballDecay;
        }
        if (ball.getPosition().x - ball.getRadius() < 0)
        {
            ballVelocity.x *= -1;
            ballVelocity *= ballDecay;
        }
        if (ball.getPosition().y + ball.getRadius() > max.y)
        {
            ballVelocity.y *= -1;
            ballVelocity *= ballDecay;
        }
        if (ball.getPosition().y - ball.getRadius() < 0)
        {
            ballVelocity.y *= -1;
            ballVelocity *= ballDecay;
        }

        window.clear(sf::Color::Black);
        window.draw(ball);

        window.display();
    }
}