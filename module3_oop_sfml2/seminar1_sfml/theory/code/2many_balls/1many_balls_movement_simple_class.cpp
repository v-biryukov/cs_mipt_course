/*
    Данная программа рисует 10 шариков движущихся с постоянной скоростью,
    но если какой-либо шарик выходит за границы окна, он появляется с другой стороны.

    Исправим предыдущую программу. Создадим простой агрегатный класс Ball, который будет просто
    хранить положение, скорость и радиус каждого шарика.
    В контейнере будем хранить не большие объекты типа sf::CircleShape, а маленькие объекты типа Ball.

    Создадим только один объект sf::CircleShape для рисования сразу всех шариков.
    Перед рисованием, только будем менять необходимые поля sf::CircleShape, чтобы рисовать шарики
    в разных местах.

    Данное решение уже лучше, чем то, что было в предыдущем файле, но тоже имеет недостаток.
    А именно, поведение шариков описывается не внутри класса Ball, а по всей программе.
    Чтобы код стал лучше необходимо инкапсулировать всё поведение шариков в один класс.
    Это будет сделано в следующем примере.
*/

#include <SFML/Graphics.hpp>
#include <vector>

struct Ball
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Many Balls");
    window.setFramerateLimit(60);
    
    std::vector<Ball> balls;
    for (int i = 0; i < 10; ++i)
    {
        Ball ball;
        ball.radius = 10;
        ball.position = sf::Vector2f{200.0f + 50.0f * i, 600.0f - 50.0f * i};
        ball.velocity = sf::Vector2f{5, 5};
        balls.push_back(ball);
    }

    sf::CircleShape circle;
    circle.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Vector2f max = window.getView().getSize();
        for (auto& ball : balls)
        {
            ball.position += ball.velocity;

            sf::Vector2f max = window.getView().getSize();
            if (ball.position.x - ball.radius > max.x)
                ball.position += sf::Vector2f{-max.x - 2 * ball.radius, 0};
            if (ball.position.y - ball.radius > max.y)
                ball.position += sf::Vector2f{0, -max.y - 2 * ball.radius};
        }
        
        window.clear(sf::Color::Black);   
             
        for (auto& ball : balls)
        {
            circle.setRadius(ball.radius);
            circle.setOrigin({ball.radius, ball.radius});
            circle.setPosition(ball.position);
            window.draw(circle);
        }
        window.display();
    }
}
