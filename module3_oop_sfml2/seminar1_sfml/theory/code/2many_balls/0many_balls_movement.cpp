/*
    Данная программа рисует 10 шариков движущихся с постоянной скоростью,
    но если какой-либо шарик выходит за границы окна, он появляется с другой стороны.

    Для рисования одного шарика мы использовали один объект типа sf::CircleShape.
    Внутри этого объекта хранятся положения шарика, радиус, цвет, а так же много чего другого, нужного
    для рисования фигуры шарика на экране.

    Чтобы работать с несколькими шариками положим несколько объектов типа sf::CircleShape
    в контейнер, например в std::vector. Обрабатывать движение всех шариков будем просто проходя
    циклом по контейнеру. Отрисовать все шарики можно также пройдя циклом по контейнеру.
    Объект sf::CircleShape не хранит скорость объектов, поэтому будем хранить скорость
    в отдельной переменной ballVelocity (скорость всех шариков в данной программе будет одинаковой).
    

    Несмотря на то, что программа работает, решение с хранением объекта sf::CircleShape
    для каждого шарика может быть не самым лучшим по следующим причинам:

        1)  Объект sf::CircleShape хранит внутри себя множество полей, которые нам не нужны, такие как
            цвет объекта, указатель на текстуру, координаты каждой вершины круга (да, круг в SFML на
            самом деле является не кругом, а правильным многоугольником).
            Мы бы не хотели хранить все эти поля для каждого шарика.

        2)  Объект sf::CircleShape не хранит внутри себя скорость шарика. Если нам понадобится задать
            разные скорости для разных шариков, то придётся создавать новый отдельный массив.

        3)  Объект sf::CircleShape нужен именно для отрисовки фигуры круга, а не для управления
            движения шариком. То есть, тут мы используем класс не по назначению.

    Чтобы лучше решить эту же задачу, нужно создать новый класс для описания движения шариков.
    Это будет сделано в следующих примерах программ.
*/



#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Many Balls");
    window.setFramerateLimit(60);
    
    std::vector<sf::CircleShape> balls;
    for (int i = 0; i < 10; ++i)
    {
        sf::CircleShape ball(10);
        ball.setOrigin({ball.getRadius(), ball.getRadius()});
        ball.setFillColor(sf::Color::White);
        ball.setPosition({200.0f + 50.0f * i, 600.0f - 50.0f * i});
        balls.push_back(ball);
    }
    
    sf::Vector2f ballVelocity {5, 5};
    
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
            ball.move(ballVelocity);

            sf::Vector2f max = window.getView().getSize();
            if (ball.getPosition().x - ball.getRadius() > max.x)
                ball.move({-max.x - 2 * ball.getRadius(), 0});
            if (ball.getPosition().y - ball.getRadius() > max.y)
                ball.move({0, -max.y - 2 * ball.getRadius()});
        }
        
        window.clear(sf::Color::Black);   
             
        for (auto& ball : balls)
        {
            window.draw(ball);
        }
        window.display();
    }
}
