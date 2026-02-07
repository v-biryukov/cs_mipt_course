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

    bool mIsDragged             {false};
    sf::Vector2f mOffset        {0.0f, 0.0f};

public:
    Object(sf::RenderWindow& window) : mRenderWindow(window) {}

    virtual void draw() const = 0;
    virtual ~Object() {}

    virtual void setPosition(sf::Vector2f position) 
    {
        mRect.left = position.x;
        mRect.top = position.y;
    }
    virtual sf::Vector2f getPosition() const {return mRect.getPosition();}

    virtual bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (mRect.contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - getPosition();
        }
        return mIsDragged;
    }

    virtual void onMouseReleased()
    {
        mIsDragged = false;
    }

    virtual void onMouseMoved(sf::Vector2f mousePosition, sf::FloatRect bounds)
    {
        if (mIsDragged)
        {
            sf::Vector2f result = mousePosition - mOffset;
            result.x = std::clamp(result.x, bounds.left, bounds.left + bounds.width - mRect.width);
            result.y = std::clamp(result.y, bounds.top, bounds.top + bounds.height - mRect.height);

            // std::cout << result.x << " " << result.y << std::endl;
            setPosition(result);
        }
    }

    bool handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            return onMousePressed(mousePosition);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMouseReleased();
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePosition, {0, 0, mRenderWindow.getView().getSize().x, mRenderWindow.getView().getSize().y});
        }

        return false;
    }
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
};



class Group : public Object
{
private:
    std::vector<Object*> mObjects;

    bool mIsInnerObjectDragged {false};
    size_t mDragIndex {0};

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

    virtual bool onMousePressed(sf::Vector2f mousePosition) override
    {
        for (size_t i = 0; i < mObjects.size(); ++i)
        {
            if (mObjects.at(i)->onMousePressed(mousePosition))
            {
                mIsInnerObjectDragged = true;
                mDragIndex = i;
                return true;
            }
        }
        return Object::onMousePressed(mousePosition);
    }

    virtual void onMouseReleased() override
    {
        mIsInnerObjectDragged = false;
        mObjects.at(mDragIndex)->onMouseReleased();
        Object::onMouseReleased();
    }

    virtual void onMouseMoved(sf::Vector2f mousePosition, sf::FloatRect bounds) override
    {
        if (mIsInnerObjectDragged)
            mObjects.at(mDragIndex)->onMouseMoved(mousePosition, mRect);
        
        Object::onMouseMoved(mousePosition, bounds);
    }


    ~Group()
    {
        for (auto* p : mObjects)
            delete p;
    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Composite");

    Group* pg = new Group{window, {100, 100, 300, 300}};
    pg->add(new Circle{window, 50, {100, 100}});
    pg->add(new Circle{window, 50, {100, 300}});
    pg->add(new Square{window, 30, {200, 200}});

    Group* pgin = new Group{window, {400, 100, 200, 200}};
    pgin->add(new Circle{window, 40, {400, 100}});
    pgin->add(new Square{window, 70, {500, 200}});

    Group* pgout = new Group{window, {400, 100, 400, 400}};
    pgout->add(pgin);
    pgout->add(new Square{window, 50, {500, 400}});

    std::vector<Object*> objects
    {
        new Circle{window, 50, {700, 700}},
        pg,
        pgout
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