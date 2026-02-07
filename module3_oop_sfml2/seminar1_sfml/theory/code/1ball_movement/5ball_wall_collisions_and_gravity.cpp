/*
    Программа рисует один шарик, двигающийся в поле гравитации, 
    но если шарик достигает границ окна, то он упруго отскакивает от границ окна.

    Для того чтобы добавить гравитацию, нужно просто добавить шарику постоянное ускорение,
    направеленное вниз: 
    
        sf::Vector2f ballAcceleration {0, 1000};
*/


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Collisions and Gravity", sf::Style::Default);
    window.setFramerateLimit(60);
 
    sf::CircleShape ball(30);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition(sf::Vector2f{100, 100});

    sf::Vector2f ballVelocity {300, 0};
    sf::Vector2f ballAcceleration {0, 1000};
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