/*
    Программа рисует один шарик, двигающийся в поле гравитации, 
    но если шарик достигает границ окна, то он НЕупруго отскакивает от границ окна.

    "Прилипание" к границам в прошлой программе происходило из-за того, что шарик после столкновения
    со стенкой перемещался медленнее, чем до столкновения.
    Так как мы проверяем положение шарика только каждые dt секунд, то может случиться такая ситуация,
    что в один кадр шарик не прикосался ко стенке, а уже в следующий кадр вышел за границы на величину:

        dx = ballVelocity.x * dt

    Если во время столкновения, x-компонента скорости умножится на -ballDecay, то в следующий кадр после
    столкновения, шарик сместится по оси Ox на величину, меньшую, чем dx. Таким образом, шарик продолжит
    накладываться на стенку и наше программа будет считаться что шарик ещё раз столкнулся со стенкой и
    ещё раз умножит скорость на -ballDecay. В следующий кадр повториться то же самое и шарик как бы
    "прилипнет" к стенке.


    Чтобы избежать такого поведения шарика, при каждом столкновении, помимо обращения компонент скорости шарика, 
    будем "выталкивать" шарить из стенок. Для этого будем вычислять расстояние на которое шарик выходит за границы
    для каждой стенки. Например, для правой стенки такое расстояние будет равно:

        float dx = ball.getPosition().x + ball.getRadius() - max.x;

    Столкновение со стенкой будет происходить если dx > 0.
    После столкновение со стенкой будем "выталкивать" шарик из стенки:

        ball.move({-dx, 0});

    Таким образом шарик никогда не прилипнет к стенке.

    Это не совсем корректное решение с точки зрения физики. Более корректно было бы высчитывать будущее положение
    шарика (например, в каждом кадре считать в каком положении окажется шарик в следующем кадре) и, основываясь
    на этой информации, вычислять корректное положение шарика после столкновения.
    Однако, реализация этого способа сильно бы усложнило код программы, но не сильно изменило бы видимое
    поведение шарика.
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
        if (float dx = ball.getPosition().x + ball.getRadius() - max.x; dx > 0)
        {
            ballVelocity.x *= -1;
            ballVelocity *= ballDecay;
            ball.move({-dx, 0});
        }
        if (float dx = -ball.getPosition().x + ball.getRadius(); dx > 0)
        {
            ballVelocity.x *= -1;
            ballVelocity *= ballDecay;
            ball.move({dx, 0});
        }
        if (float dy = ball.getPosition().y + ball.getRadius() - max.y; dy > 0)
        {
            ballVelocity.y *= -1;
            ballVelocity *= ballDecay;
            ball.move({0, -dy});
        }
        if (float dy = -ball.getPosition().y + ball.getRadius(); dy > 0)
        {
            ballVelocity.y *= -1;
            ballVelocity *= ballDecay;
            ball.move({0, dy});
        }

        window.clear(sf::Color::Black);
        window.draw(ball);

        window.display();
    }
}