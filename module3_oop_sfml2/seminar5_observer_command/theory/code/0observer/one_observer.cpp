#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <set>


class Observer
{
public:
    virtual void update(float value) = 0;
    virtual ~Observer() {}
};


class Subject
{
public:

    virtual void addObserver(Observer* p) = 0;
    virtual void removeObserver(Observer* p) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() {}
};


class Circle : public Observer
{
private:

    sf::CircleShape mShape;
    sf::RenderWindow& mSfmlWindow;

public:

    Circle(sf::RenderWindow& window, sf::Vector2f position, float radius) 
    : mSfmlWindow(window), mShape(radius)
    {
        mShape.setOrigin({radius, radius});
        mShape.setPosition(position);
        mShape.setFillColor(sf::Color::Green);
    }

    void draw() const
    {
        mSfmlWindow.draw(mShape);
    }

    void update(float value) override
    {
        std::cout << value << std::endl;
        mShape.setScale({value / 50, value / 50});
    }
};


class Slider
{
private:
    sf::RectangleShape mTrackShape {};
    sf::RectangleShape mThumbShape {};

    sf::Color mTrackColor           {200, 200, 220};
    sf::Color mThumbColor           {150, 150, 240};

    sf::RenderWindow& mSfmlWindow;
    bool mIsPressed {false};


    std::set<Observer*> mObservers;

public:

    Slider(sf::RenderWindow& window, sf::Vector2f centerPosition, sf::Vector2f trackSize, sf::Vector2f thumbSize) 
            : mSfmlWindow(window)
    {
        mTrackShape.setSize(trackSize);
        mTrackShape.setOrigin(trackSize / 2.0f);
        mTrackShape.setPosition(centerPosition);
        mTrackShape.setFillColor(mTrackColor);

        mThumbShape.setSize(thumbSize);
        mThumbShape.setOrigin(thumbSize / 2.0f);
        mThumbShape.setPosition(centerPosition);
        mThumbShape.setFillColor(mThumbColor);
    }

    void draw()
    {
        mSfmlWindow.draw(mTrackShape);
        mSfmlWindow.draw(mThumbShape);
    }

    void onMouseMove(const sf::Event& event)
    {
        if (!mIsPressed)
            return;

        sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        float min = mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.0f;
        float max = mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.0f;

        mThumbShape.setPosition({std::clamp(mousePosition.x, min, max), mThumbShape.getPosition().y});
        notifyObservers();
    }

    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            sf::Vector2f mousePosition = mSfmlWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mThumbShape.getGlobalBounds().contains(mousePosition) || mTrackShape.getGlobalBounds().contains(mousePosition)) 
            {
                mIsPressed = true;
                mThumbShape.setPosition({mousePosition.x, mThumbShape.getPosition().y});
                notifyObservers();
            }
        }
    }

    void onMouseReleased(const sf::Event& event)
    { 
        mIsPressed = false;
    }

    void handleEvent(const sf::Event& event) 
    {
        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        
        else if (event.type == sf::Event::MouseButtonPressed)
            onMousePressed(event);
        
        else if (event.type == sf::Event::MouseButtonReleased)
            onMouseReleased(event);
    }

    float getValue() const
    {
        float part = mThumbShape.getPosition().x - mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.0f;
        return part / mTrackShape.getSize().x * 100.0f;
    }


    void addObserver(Observer* p) 
    {
        mObservers.insert(p);
    }

    void removeObserver(Observer* p)
    {
        mObservers.erase(p);
    }

    void notifyObservers()
    {
        for (auto p : mObservers)
            p->update(getValue());
    }
};




int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Observer");
    window.setFramerateLimit(60);

    Slider slider(window, {400, 500}, {500, 20}, {25, 90});
    Circle circle(window, {400, 300}, 50);
    slider.addObserver(&circle);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            slider.handleEvent(event);
        }

        window.clear(sf::Color::Black);
        slider.draw();
        circle.draw();
        window.display();
    }
}