#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "context_menu.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Context Menu Test");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../sourceCodePro.ttf")) 
    {
        std::cout << "Error: Font file not found." << std::endl;
        std::exit(1);
    }

    std::vector<sf::String> contextMenuStrings {"Add Button", "Cut", "Copy", "Paste", "Select All"};
    ContextMenu contextMenu(window, font);
    for (const auto& el : contextMenuStrings)
        contextMenu.addButton(el);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            int result = contextMenu.handleEvent(event);
            if (result >= 0) 
                std::cout << (std::string)contextMenuStrings[result] << std::endl;

            if (result == 0) 
            {
                contextMenuStrings.push_back("New Button");
                contextMenu.addButton("New Button");
            }
        }
        window.clear(sf::Color::Black);

        contextMenu.draw();
        window.display();
    }
    return 0;
}