#include <SFML/Graphics.hpp>

int main()
{
    float k = 0.5;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800 * k, 800 * k), "Figures", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    
    sf::CircleShape a(100 * k, 3);
    a.setPosition(sf::Vector2f(150 * k, 150 * k));
    a.setFillColor(sf::Color::Red);
    
    sf::CircleShape b(90 * k, 500);
    b.setPosition(sf::Vector2f(500 * k, 300 * k));
    b.setFillColor(sf::Color::Blue);
    
    sf::RectangleShape c({180 * k, 130 * k});
    c.setPosition(sf::Vector2f(250 * k, 500 * k));
    c.setFillColor(sf::Color::Green);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            a.move(sf::Vector2f{1, 1});
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            b.move(sf::Vector2f{1, 1});
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            c.move(sf::Vector2f{1, 1});

        window.clear(sf::Color::Black);
        window.draw(a);
        window.draw(b);
        window.draw(c);

        window.display();
    }
}
