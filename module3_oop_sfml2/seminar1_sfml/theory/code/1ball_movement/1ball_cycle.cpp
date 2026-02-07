/*
    Программа рисует один шарик, двигающийся с постоянной скоростью, но если шарик выходит 
    за границы окна, он появляется с другой стороны.

    Для того, чтобы добиться такого поведения шарика, мы будем просто проверять координаты шарика
    каждый кадр, и если, например, x-координата шарика будет больше ширины экрана, то мы
    просто будем вычитать из x-координата шарика значение ширины экрана.

    Для того, чтобы получить координаты шарика используем метод:

        ball.getPosition()

    возвращающий объект sf::Vector2f.

    Для того, чтобы получить размеры окна шарика используем один из следующих методов:

        window.getSize()            - размеры окна в координатах пикселей
        window.getView().getSize()  - размеры окна в координатах мира
*/


#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Moving Ball Cycle", sf::Style::Default);
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
        
        ball.move(sf::Vector2f{10, 5});

        sf::Vector2f max = window.getView().getSize();
        if (ball.getPosition().x > max.x)
            ball.move({-max.x, 0});
        if (ball.getPosition().y > max.y)
            ball.move({0, -max.y});

        window.clear(sf::Color::Black);
        window.draw(ball);

        window.display();
    }
}