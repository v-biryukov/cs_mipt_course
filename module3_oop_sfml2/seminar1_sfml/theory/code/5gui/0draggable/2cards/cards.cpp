#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "draggable.hpp"

float getRandomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> d(min, max);
    return d(gen);
}

sf::Color getRandomColor()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> d(0, 255);
    return sf::Color{d(gen), d(gen), d(gen)};
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Cards");
    window.setFramerateLimit(60);

    std::vector<Draggable> draggables;
    for (int i = 0; i < 20; ++i)
    {
        float sceneWidth = window.getView().getSize().x;
        float sceneHeight = window.getView().getSize().y;
        float randomWidth = getRandomFloat(20, sceneWidth / 3);
        float randomHeight = getRandomFloat(20, sceneHeight / 3);
        float randomX = getRandomFloat(0, sceneWidth - randomWidth);
        float randomY = getRandomFloat(0, sceneHeight - randomHeight);
        draggables.push_back({window, {randomX, randomY}, {randomWidth, randomHeight}, getRandomColor()});
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (auto& d : draggables)
            {
                if (d.handleEvent(event))
                    break;
            }
        }
        
        window.clear(sf::Color::Black);
        for (auto it = draggables.crbegin(); it != draggables.crend(); ++it)
        {
            it->draw();
        }
        
        window.display();
    }
}