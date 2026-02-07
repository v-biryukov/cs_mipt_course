/*
    Программа рисует один шарик, двигающийся с постоянной скоростью, но если шарик 
    достигает границ окна, то он упруго отскакивает от границ окна.

    Для того чтобы добиться такого поведения шарика, просто проверяем каждый кадр, достиг ли шарик
    края окна, и если это произошло, то просто умножаем соответствующую компоненту скорости на -1.
*/


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Moving Ball with Wall Collisions", sf::Style::Default);
    window.setFramerateLimit(60);
 
    sf::CircleShape ball(30);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition(sf::Vector2f{100, 100});

    sf::Vector2f ballVelocity {1000, 500};
    float dt = 1.0f / 60;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        ball.move(ballVelocity * dt);

        sf::Vector2f max = window.getView().getSize();
        if (ball.getPosition().x + ball.getRadius() > max.x)
        {
            ballVelocity.x *= -1;
        }
        if (ball.getPosition().x - ball.getRadius() < 0)
        {
            ballVelocity.x *= -1;
        }
        if (ball.getPosition().y + ball.getRadius() > max.y)
        {
            ballVelocity.y *= -1;
        }
        if (ball.getPosition().y - ball.getRadius() < 0)
        {
            ballVelocity.y *= -1;
        }

        window.clear(sf::Color::Black);
        window.draw(ball);

        window.display();
    }
}