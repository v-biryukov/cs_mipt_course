#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

int main () 
{
    const int windowWidth = 1200;
    const int windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Textures");
    window.setFramerateLimit(60);

    std::vector<sf::CircleShape> circles;
    for (int i = 0; i < 100; ++i) {
        circles.push_back(sf::CircleShape(5 + rand() % 70));
        circles.back().setPosition({rand() % windowWidth, rand() % windowHeight});
        circles.back().setFillColor({rand(), rand(), rand()});
    }

    // sf::View -- это 2d камера, которая позволяет видеть только часть мира
    sf::View view;
    view.reset(sf::FloatRect(100, 100, 400, 300));
    // view.rotate(45);
    // view.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));

    float time = 0;
    while (window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move({-2, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move({2, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move({0, 2});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move({0, -2});

        window.clear();
        window.setView(view);
        for (auto& circle : circles)
            window.draw(circle);
        window.display();
        time += 1.0 / 60;
    }

    return 0;
}


// Задание 1: 
// Сделайте так, чтобы 2d камеру можно было поворачивать при нажатии на 
// клавиши Z и X
