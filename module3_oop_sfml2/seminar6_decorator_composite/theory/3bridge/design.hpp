#pragma once
#include <SFML/Graphics.hpp>

class Design
{
public:
    virtual void draw(sf::RenderWindow& window, sf::Vector2f position, sf::Color color) const = 0;
    virtual bool checkIfContains(sf::Vector2f objectPosition, sf::Vector2f pointPosition) const = 0;
    virtual sf::FloatRect getBounds(sf::Vector2f objectPosition) const = 0;
    virtual ~Design() {}
};


class RectangleDesign : public Design
{
private:
    sf::Vector2f mSize {};

public:

    RectangleDesign(sf::Vector2f size) : mSize(size) {}

    void draw(sf::RenderWindow& window, sf::Vector2f position, sf::Color color) const override
    {
        static sf::RectangleShape shape;
        shape.setSize(mSize);
        shape.setPosition(position);
        shape.setFillColor(color);
        window.draw(shape);
    }

    bool checkIfContains(sf::Vector2f objectPosition, sf::Vector2f pointPosition) const override
    {
        sf::FloatRect rect {objectPosition.x, objectPosition.y, mSize.x, mSize.y};
        return rect.contains(pointPosition);
    }

    sf::FloatRect getBounds(sf::Vector2f objectPosition) const override
    {
        return {objectPosition.x, objectPosition.y, mSize.x, mSize.y};
    }
};


class SmoothDesign : public Design
{
private:
    sf::Vector2f mSize {};
    float mSmoothness  {};

    mutable sf::CircleShape mCornerCircle;
    mutable sf::RectangleShape mHorizontalRectangle;
    mutable sf::RectangleShape mVerticalRectangle;

public:

    SmoothDesign(sf::Vector2f size, float smoothness)
    : mSize(size), mSmoothness(smoothness)
    {
        float minSide = std::min(mSize.x, mSize.y);
        float cornerRadius = minSide / 2.f * mSmoothness;

        mCornerCircle.setRadius(cornerRadius);
        mHorizontalRectangle.setSize({mSize.x, mSize.y - 2.f * cornerRadius});
        mVerticalRectangle.setSize({mSize.x - 2.f * cornerRadius, mSize.y});
    }

    bool checkIfContains(sf::Vector2f objectPosition, sf::Vector2f pointPosition) const override
    {
        setPositions(objectPosition);

        bool result =   mHorizontalRectangle.getGlobalBounds().contains(pointPosition) 
                        || mVerticalRectangle.getGlobalBounds().contains(pointPosition)
                        || checkIfCircleContains(mCornerCircle, pointPosition);

        float cornerRadius = mCornerCircle.getRadius();

        mCornerCircle.setPosition(objectPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, 0});
        result |= checkIfCircleContains(mCornerCircle, pointPosition);

        mCornerCircle.setPosition(objectPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, mSize.y - 2.f * cornerRadius});
        result |= checkIfCircleContains(mCornerCircle, pointPosition);    

        mCornerCircle.setPosition(objectPosition + sf::Vector2f{0, mSize.y - 2.f * cornerRadius});
        result |= checkIfCircleContains(mCornerCircle, pointPosition);

        mCornerCircle.setPosition(objectPosition);
        return result;
    }



    void draw(sf::RenderWindow& window, sf::Vector2f position, sf::Color color) const override
    {
        setPositions(position);
        setColors(color);

        window.draw(mHorizontalRectangle);
        window.draw(mVerticalRectangle);

        float cornerRadius = mCornerCircle.getRadius();
        window.draw(mCornerCircle);
        mCornerCircle.setPosition(position + sf::Vector2f{mSize.x - 2.f * cornerRadius, 0});
        window.draw(mCornerCircle);
        mCornerCircle.setPosition(position + sf::Vector2f{mSize.x - 2.f * cornerRadius, mSize.y - 2.f * cornerRadius});
        window.draw(mCornerCircle);    
        mCornerCircle.setPosition(position + sf::Vector2f{0, mSize.y - 2.f * cornerRadius});
        window.draw(mCornerCircle);
        mCornerCircle.setPosition(position);
    }

    sf::FloatRect getBounds(sf::Vector2f objectPosition) const override
    {
        return {objectPosition.x, objectPosition.y, mSize.x, mSize.y};
    }

private:

    void setColors(sf::Color color) const
    {
        mCornerCircle.setFillColor(color);
        mHorizontalRectangle.setFillColor(color);
        mVerticalRectangle.setFillColor(color);
    }

    void setPositions(sf::Vector2f position) const
    {
        mCornerCircle.setPosition(position);
        mHorizontalRectangle.setPosition(position + sf::Vector2f{0, mCornerCircle.getRadius()});
        mVerticalRectangle.setPosition(position + sf::Vector2f{mCornerCircle.getRadius(), 0});
    }

    static bool checkIfCircleContains(const sf::CircleShape& circle, sf::Vector2f position)
    {
        sf::Vector2f d = circle.getPosition() + sf::Vector2f{circle.getRadius(), circle.getRadius()} - position;
        float distancesq = d.x * d.x + d.y * d.y;
        return distancesq < circle.getRadius() * circle.getRadius();
    }
};