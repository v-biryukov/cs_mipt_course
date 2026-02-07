#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Moving Circle", sf::Style::Default);
    window.setFramerateLimit(60);
    
    sf::CircleShape circle(30);
    circle.setPosition(sf::Vector2f{100, 100});

    while (window.isOpen())
    {
        std::optional<sf::Event> event;
        while (event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        circle.move(sf::Vector2f{1, 1});

        window.clear(sf::Color::Black);
        window.draw(circle);

        window.display();
    }
}