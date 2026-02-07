/*
    Для компиляции:
         g++ main.cpp player.cpp player_states.cpp -lsfml-window -lsfml-system -lsfml-graphics

    Графика взята отсюда:
        https://rvros.itch.io/animated-pixel-hero
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "world.hpp"

int main() 
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Player states", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    double time = 0;
    double dt = 1.0 / 60;

    World world;
    world.addBlock({-500, 770, 20000, 400});
    world.addBlock({-400, 100, 700, 300});
    world.addBlock({600, 500, 300, 120});
    world.addBlock({800, 0, 400, 200});
    world.addBlock({-100, -700, 400, 100});
    world.addBlock({700, -700, 400, 100});
    world.addBlock({1500, -700, 400, 100});
    world.addBlock({1100, -300, 400, 100});
    world.addBlock({1100, 400, 400, 400});
    world.addBlock({1900, -100, 200, 800});
    world.addBlock({3000, 500, 1000, 200});

    while (window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
                window.close();

            world.handleEvents(event);
        }
        window.clear(sf::Color::Black);
        world.update(dt);
        world.draw(window);

        window.display();

        time += dt;
    }
}
