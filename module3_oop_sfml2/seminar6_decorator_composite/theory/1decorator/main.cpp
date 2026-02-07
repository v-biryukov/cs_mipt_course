#include <iostream>
#include <vector>
#include <cmath>
#include "SFML/Graphics.hpp"


class Object
{
protected:
    sf::RenderWindow& mRenderWindow;
    sf::Vector2f mPosition {};
    sf::Color mColor {sf::Color::White};

public:
    Object(sf::RenderWindow& window)
    : mRenderWindow(window) {}

    virtual sf::FloatRect getBounds() const = 0;
    virtual void draw() = 0;
    virtual void handleEvent(sf::Event event) = 0;
    virtual ~Object() {}

    virtual void setPosition(sf::Vector2f position) {mPosition = position;}
    virtual sf::Vector2f getPosition() const {return mPosition;}
};


class Circle : public Object
{
protected:
    float mRadius;

public:
    Circle(sf::RenderWindow& window, float radius, sf::Vector2f position)
    : Object(window), mRadius(radius) 
    {
        setPosition(position);
    }

    sf::FloatRect getBounds() const override
    {
        return sf::FloatRect{mPosition.x - mRadius, mPosition.y - mRadius, 2 * mRadius, 2 * mRadius};

    }

    void draw() override
    {
        static sf::CircleShape shape;
        shape.setRadius(mRadius);
        shape.setOrigin({mRadius, mRadius});
        shape.setPosition(mPosition);
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
        setPosition(position);
    }

    sf::FloatRect getBounds() const override
    {
        return sf::FloatRect{mPosition.x - mSize/2, mPosition.y - mSize/2, mSize, mSize};
    }

    void draw() override
    {
        static sf::RectangleShape shape;
        shape.setSize({mSize, mSize});
        shape.setOrigin({mSize/2, mSize/2});
        shape.setPosition(mPosition);
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
    }

    void handleEvent(sf::Event event) override {}
};



class SelectionDecorator : public Object
{
protected:
    Object* mpObject;

public:

    SelectionDecorator(sf::RenderWindow& window, Object* pObject) : Object{window}, mpObject{pObject} {}

    sf::FloatRect getBounds() const override
    {
        sf::FloatRect rect = mpObject->getBounds();
        sf::Vector2f position = rect.getPosition() + rect.getSize() / 2.0f;
        sf::Vector2f halfSize = rect.getSize() / 2.0f * sSizeMultiplicator;
        return {position.x - halfSize.x, position.y - halfSize.y, 2 * halfSize.x, 2 * halfSize.y};
    }

    void draw() override
    {
        mpObject->draw();
        drawCorners(mpObject->getBounds());
    }

    void handleEvent(sf::Event event) override 
    {
        mpObject->handleEvent(event);
    }

    void setPosition(sf::Vector2f position) override
    {
        mpObject->setPosition(position);
    }

    sf::Vector2f getPosition() const override
    {
        return mpObject->getPosition();
    }

    ~SelectionDecorator()
    {
        delete mpObject;
    }

private:

    static constexpr float sFraction = 0.7;
    static constexpr float sSizeMultiplicator = 1.2;

    void drawCorners(sf::FloatRect rect)
    {
        sf::Vector2f position = rect.getPosition() + rect.getSize() / 2.0f;
        sf::Vector2f halfSize = rect.getSize() / 2.0f * sSizeMultiplicator;
        drawLine({position.x - halfSize.x, position.y + halfSize.y}, {position.x - halfSize.x, position.y + halfSize.y * sFraction});
        drawLine({position.x - halfSize.x, position.y + halfSize.y}, {position.x - sFraction*halfSize.x, position.y + halfSize.y});
        drawLine({position.x + halfSize.x, position.y + halfSize.y}, {position.x + halfSize.x, position.y + halfSize.y*sFraction});
        drawLine({position.x + halfSize.x, position.y + halfSize.y}, {position.x + halfSize.x*sFraction, position.y + halfSize.y});
        drawLine({position.x + halfSize.x, position.y - halfSize.y}, {position.x + halfSize.x*sFraction, position.y - halfSize.y});
        drawLine({position.x + halfSize.x, position.y - halfSize.y}, {position.x + halfSize.x, position.y - halfSize.y*sFraction});
        drawLine({position.x - halfSize.x, position.y - halfSize.y}, {position.x - halfSize.x*sFraction, position.y - halfSize.y});
        drawLine({position.x - halfSize.x, position.y - halfSize.y}, {position.x - halfSize.x, position.y - halfSize.y*sFraction});
    }

    void drawLine(sf::Vector2f start, sf::Vector2f finish)
    {
        sf::Vertex lineVertices[2] = {sf::Vertex(start, sf::Color::White), sf::Vertex(finish, sf::Color::White)};
        mRenderWindow.draw(lineVertices, 2, sf::Lines);
    }
};


class DragDecorator : public Object
{
protected:
    Object* mpObject;
    bool mIsDragged             {false};
    sf::Vector2f mOffset        {0.0f, 0.0f};

public:

    DragDecorator(sf::RenderWindow& window, Object* pObject) : Object{window}, mpObject{pObject} 
    {}

    sf::FloatRect getBounds() const override
    {
        return mpObject->getBounds();
    }

    void draw() override
    {
        mpObject->draw();
    }

    bool onMousePressed(sf::Vector2f mousePosition)
    {
        if (getBounds().contains(mousePosition))
        {
            mIsDragged = true;
            mOffset = mousePosition - mpObject->getPosition();
        }
        return mIsDragged;
    }

    void onMouseReleased()
    {
        mIsDragged = false;
    }

    void onMouseMoved(sf::Vector2f mousePosition)
    {
        if (mIsDragged)
        {
            std::cout << "123" << std::endl;
            setPosition(mousePosition - mOffset);
        }
    }

    void handleEvent(sf::Event event)override
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMousePressed(mousePosition);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            onMouseReleased();
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePosition);
        }
    }

    void setPosition(sf::Vector2f position) override
    {
        std::cout << "Drg set pos" << std::endl;
        mpObject->setPosition(position);
    }

    sf::Vector2f getPosition() const override
    {
        return mpObject->getPosition();
    }

    ~DragDecorator()
    {
        delete mpObject;
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Decorator");

    std::vector<Object*> objects
    {
        new Circle{window, 50.0f,  {100.0f, 100.0f}},
        new SelectionDecorator{window, new Square{window, 100.0f, {600.0f, 600.0f}}},
        new DragDecorator{window, new Square{window, 100.0f, {200.0f, 600.0f}}},
        new SelectionDecorator{window, new DragDecorator{window, new Circle{window, 50.0f, {600.0f, 200.0f}}}},
        new DragDecorator{window, new SelectionDecorator{window, new Circle{window, 60.0f, {400.0f, 400.0f}}}}
    };

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