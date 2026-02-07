#include <iostream>
#include <random>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "button.hpp"


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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Random Buttons");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../sourceCodePro.ttf")) 
    {
        std::cout << "Error: Font file not found." << std::endl;
        std::exit(1);
    }

    std::vector<Button> buttons;

    for (int i = 0; i < 8; ++i)
    {
        float sceneWidth = window.getView().getSize().x;
        float sceneHeight = window.getView().getSize().y;
        float randomWidth = getRandomFloat(10, sceneWidth / 3);
        float randomHeight = getRandomFloat(10, sceneHeight / 3);
        float randomX = getRandomFloat(0, sceneWidth - randomWidth);
        float randomY = getRandomFloat(0, sceneHeight - randomHeight);

        buttons.push_back(Button{window, {randomX, randomY, randomWidth, randomHeight}, font, "Hello!"});
    }

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (size_t i = 0; i < buttons.size(); ++i)
            {   
                bool isButtonActivated = buttons[i].handleEvent(event);
                if (isButtonActivated)
                {
                    std::cout << "Button " << i << " is clicked!" << std::endl;
                }

            }
        }

        window.clear(sf::Color::Black);

        for (auto& b : buttons)
            b.draw();
        window.display();
    }
}