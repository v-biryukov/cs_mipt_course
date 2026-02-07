#include <SFML/Graphics.hpp>
#include <iostream>
#include "checkbox.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Checkbox Class!");
    window.setFramerateLimit(20);

    sf::Font font;
    if (!font.loadFromFile("../sourceCodePro.ttf")) 
    {
        std::cout << "Error: Font file not found." << std::endl;
        std::exit(1);
    }

    std::vector<Checkbox> checkboxes = 
    { 
        {window, font, {400, 100}, "Moscow"},
        {window, font, {400, 150}, "New York"},
        {window, font, {400, 200}, "Paris"},
        {window, font, {400, 250}, "Lagos"},
        {window, font, {400, 300}, "Tokyo"},
        {window, font, {400, 350}, "Lima"}
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            for (auto& x : checkboxes)
            {
                bool result = x.handleEvent(event);
                if (result)
                    std::cout << "Checkboxes activated: " << x.getString().toAnsiString() << std::endl;
            }
        }

        window.clear(sf::Color{233, 230, 221});

        for (const auto& x : checkboxes)
            x.draw();
        window.display();
    }
}