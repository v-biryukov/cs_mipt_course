#include "SFML/Graphics.hpp"
#include <random>
#include <concepts>
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
    std::uniform_int_distribution<sf::Uint8> d;
    return sf::Color(d(gen), d(gen), d(gen));
}


class ShapePool
{
private:

    sf::RectangleShape mField;
    std::vector<sf::Shape*> mShapes;
    sf::RenderWindow& mSfmlWindow;

public:

    ShapePool(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size)
    : mSfmlWindow(window)
    {
        mField.setPosition(position);
        mField.setSize(size);
        mField.setFillColor(sf::Color(0, 100, 200, 40));
    }

    template<typename Shape>
    void addShape(Shape* p)
    {
        sf::Vector2f max = mField.getSize() - p->getGlobalBounds().getSize();
        p->setPosition(mField.getPosition() + sf::Vector2f(getRandomFloat(0.0f, max.x), getRandomFloat(0.0f, max.y)));
        p->setFillColor(getRandomColor());
        mShapes.push_back(p);
    }

    void draw()
    {
        for (auto p : mShapes)
            mSfmlWindow.draw(*p);
        mSfmlWindow.draw(mField);        
    }

    ~ShapePool()
    {
        for (auto* p : mShapes)
            delete p;
    }

};




int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Shapes and Command", sf::Style::Default, settings);

    ShapePool fp(window, {300, 50}, {450, 700});
    fp.addShape(new sf::CircleShape(getRandomFloat(30, 100)));
    fp.addShape(new sf::CircleShape(getRandomFloat(30, 100)));
    fp.addShape(new sf::CircleShape(getRandomFloat(30, 100)));
    fp.addShape(new sf::CircleShape(getRandomFloat(30, 100), 3));
    fp.addShape(new sf::CircleShape(getRandomFloat(30, 100), 3));
    fp.addShape(new sf::RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    fp.addShape(new sf::RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    fp.addShape(new sf::RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));


    std::vector<Button*> buttons
    {
        new Button(window, {100, 100}, {100, 50}),
        new Button(window, {100, 200}, {100, 50}),
        new Button(window, {100, 300}, {100, 50}),
        new Button(window, {100, 400}, {100, 50}),
        new Button(window, {100, 500}, {100, 50}),
        new Button(window, {100, 600}, {100, 50}),
    };


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            for (auto p : buttons)
                p->handleEvent(event);
        }

        window.clear(sf::Color::Black);
        fp.draw();
        for (auto p : buttons)
            p->draw();
        window.display();
    }

    for (auto p : buttons)
        delete p;
}