#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "slider.hpp"
#include "draggable.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Widgets");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("sourceCodePro.ttf")) 
    {
        std::cout << "Error: Font file not found." << std::endl;
        std::exit(1);
    }

    std::vector<Button> buttons;
    buttons.push_back(Button{window, {350, 300, 200, 80}, font, "Cat"});
    buttons.push_back(Button{window, {200, 450, 100, 80}, font, "Dog"});
    buttons.push_back(Button{window, {600, 600, 150, 70}, font, "Mouse"});

    std::vector<Slider> sliders;
    sliders.push_back(Slider{window, {500, 500}, {200, 10}, {20, 40}});
    sliders.push_back(Slider{window, {300, 100}, {250, 20}, {30, 60}});

    std::vector<Draggable> draggables;
    draggables.push_back(Draggable{window, {550, 100}, {200, 120}, {20, 120, 50}});
    draggables.push_back(Draggable{window, {50, 550}, {200, 200}, {170, 20, 50}});
    draggables.push_back(Draggable{window, {50, 200}, {100, 100}, {100, 20, 150}});

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (auto& x : buttons)
                x.handleEvent(event);
            for (auto& x : sliders)
                x.handleEvent(event);
            for (auto& x : draggables)
                x.handleEvent(event);
        }

        window.clear(sf::Color::Black);
        for (auto& x : buttons)
            x.draw();
        for (auto& x : sliders)
            x.draw();
        for (auto& x : draggables)
            x.draw();

        window.display();
    }
}