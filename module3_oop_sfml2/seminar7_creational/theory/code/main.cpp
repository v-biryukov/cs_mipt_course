#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "draggable.hpp"
#include "slider.hpp"


class Scene
{
private:

    std::vector<RectangleButton> mButtons;
    std::vector<RectangleSlider> mSliders;
    std::vector<RectangleDraggable> mDraggables;

    sf::RenderWindow& mRenderWindow;
    sf::Font& mFont;

public:

    Scene(sf::RenderWindow& window, sf::Font& font) : mRenderWindow{window}, mFont{font} 
    {
        create();
    }

    void create()
    {
        mDraggables.push_back(RectangleDraggable{mRenderWindow, {100, 100}, {100, 200}, {200, 50, 10}});
        mDraggables.push_back(RectangleDraggable{mRenderWindow, {600, 100}, {100, 100}, {20, 50, 200}});
        mButtons.push_back({mRenderWindow, {350, 350}, {200, 120}, mFont, sf::String{"Cat"}});
        mButtons.push_back({mRenderWindow, {150, 550}, {100, 100}, mFont, sf::String{"Mouse"}});

        mSliders.push_back({mRenderWindow, {400, 600}, {150, 10}, {10, 40}});
        mSliders.push_back({mRenderWindow, {600, 700}, {250, 20}, {20, 60}});
    }

    void draw() const
    {

        for (auto x : mButtons)
            x.draw();
        for (auto x : mSliders)
            x.draw();
        for (auto x : mDraggables)
            x.draw();
    }


    void handleEvent(const sf::Event& event)
    {
        for (auto& x : mButtons)
            x.handleEvent(event);
        for (auto& x : mSliders)
            x.handleEvent(event);
        for (auto& x : mDraggables)
            x.handleEvent(event);
    }

};



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Scene", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("../../../fonts/sourceCodePro.ttf")) 
    {
        std::cout << "Can't load button font" << std::endl;
        return 1;
    }

    RectangleButton rbutton(window, {350, 350}, {300, 160}, font, sf::String{"Rectangle"});
    CircleButton cbutton(window, {100, 450}, 100, font, sf::String{"Circle"});
    SmoothButton sbutton(window, {200, 50}, {300, 200}, 0.5, font, sf::String{"Smooth"});


    Scene scene {window, font};


    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            scene.handleEvent(event);
        }

        window.clear(sf::Color::Black);
        scene.draw();
        window.display();
    }
}