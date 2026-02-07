#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Moving Circle", sf::Style::Default);
    window.setFramerateLimit(60);
    
    sf::CircleShape circle(30);
    circle.setPosition(sf::Vector2f{100, 100});
    float velocity = 100;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::sleep(sf::seconds(1));

        // Правильный способ:
        float dt = clock.restart().asSeconds();
        circle.move(sf::Vector2f{velocity * dt, velocity * dt});

        // Неправильный способ:
        // Шарик будет двигаться медленней, если кадр будет считаться дольше, чем 1/60 секунды.
        // float dt = 1.0 / 60;
        // circle.move(sf::Vector2f{velocity * dt, velocity * dt});

        window.clear(sf::Color::Black);
        window.draw(circle);

        window.display();
    }
}