#include <iostream>
#include <vector>
#include <cmath>
#include "SFML/Graphics.hpp"


class Object
{
protected:
    sf::RenderWindow& mRenderWindow;
    sf::FloatRect mRect {};
    sf::Color mColor {sf::Color::White};

public:
    Object(sf::RenderWindow& window) : mRenderWindow(window) {}

    virtual void draw() const = 0;
    virtual void handleEvent(sf::Event event) = 0;
    virtual ~Object() {}

    virtual void setPosition(sf::Vector2f position) 
    {
        mRect.left = position.x;
        mRect.top = position.y;
    }
    virtual sf::Vector2f getPosition() const {return mRect.getPosition();}
};


class Circle : public Object
{
protected:
    float mRadius;

public:
    Circle(sf::RenderWindow& window, float radius, sf::Vector2f position)
    : Object{window}, mRadius{radius} 
    {
        mRect = sf::FloatRect{position.x, position.y, 2 * radius, 2 * radius};
    }

    void draw() const override
    {
        static sf::CircleShape shape;
        shape.setRadius(mRadius);
        shape.setPosition({mRect.left, mRect.top});
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
    }

    void handleEvent(sf::Event event) override {}
};


class Square : public Object
{
protected:
    float mSize;

public:
    Square(sf::RenderWindow& window, float size, sf::Vector2f position)
    : Object{window}, mSize{size} 
    {
        mRect = sf::FloatRect{position.x, position.y, size, size};
    }

    void draw() const override
    {
        static sf::RectangleShape shape;
        shape.setSize({mSize, mSize});
        shape.setPosition({mRect.left, mRect.top});
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
    }

    void handleEvent(sf::Event event) override {}
};



class Group : public Object
{
private:
    std::vector<Object*> mObjects;

public:
    Group(sf::RenderWindow& window, sf::FloatRect rect) : Object{window}
    {
        mRect = rect;
        mColor = sf::Color(0, 100, 200, 40);
    }

    void add(Object* p)
    {
        mObjects.push_back(p);
    }

    size_t getNumbeorOfObjects() const {return mObjects.size();}
    Object& getObject(int index)
    {
        return *mObjects.at(index);
    }

    void draw() const override
    {
        for (auto p : mObjects)
            p->draw();
        
        static sf::RectangleShape shape;
        shape.setSize(mRect.getSize());
        shape.setPosition(mRect.getPosition());
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
    }

    void setPosition(sf::Vector2f position) override
    {
        sf::Vector2f offset = position - mRect.getPosition();
        for (auto p : mObjects)
        {
            p->setPosition(p->getPosition() + offset);
        }
        Object::setPosition(position); 
    }

    void handleEvent(sf::Event event) override {}

    ~Group()
    {
        for (auto* p : mObjects)
            delete p;
    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Decorator");

    Group* pg = new Group{window, {200, 200, 400, 400}};
    pg->add(new Circle{window, 50, {300, 300}});
    pg->add(new Circle{window, 50, {500, 400}});

    std::vector<Object*> objects
    {
        new Circle{window, 50, {700, 700}},
        pg
    };

    pg->setPosition({0, 0});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (auto p : objects)
                p->handleEvent(event);
        }

        window.clear(sf::Color::Black);
        for (auto p : objects)
                p->draw();
        window.display();
    }


    for (auto p : objects)
        delete p;
}