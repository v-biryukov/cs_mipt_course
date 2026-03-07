#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


class Button
{
protected:
    sf::RenderWindow& mRenderWindow; 

    sf::Color mDefaultColor {179, 230, 255};
    sf::Color mHoverColor   {128, 212, 255};
    sf::Color mPressedColor {  0, 136, 204};

    sf::Vector2f mPosition {};
    sf::Color mColor {};

    sf::Text mText {};
    bool mIsPressed {false};


public:
    Button(sf::RenderWindow& window, sf::Vector2f position, sf::Font& font, const sf::String& textData) 
            : mRenderWindow(window), mPosition(position)
    {
        mColor = mDefaultColor;
        mText.setFont(font);
        mText.setString(textData);
        mText.setFillColor(sf::Color::Black);
    }

    virtual bool checkIfContains(sf::Vector2f position) const = 0;
    virtual void draw() const = 0;
    virtual sf::FloatRect getBounds() const = 0;


    void setFontSize(unsigned int fontSize)
    {
        mText.setCharacterSize(fontSize);
        centerText();
    }

    void setOptimalFontSize()
    {
        mText.setCharacterSize(30);

        float widthFraction = 0.75;
        float heightFraction = 0.5;

        sf::FloatRect textBounds = mText.getLocalBounds();
        float widthRatio = getBounds().width / textBounds.width * widthFraction;
        float heightRatio = getBounds().height / textBounds.height * heightFraction;
        float minRatio = std::min(widthRatio, heightRatio);

        std::cout << minRatio << std::endl;
        unsigned int newSize = static_cast<unsigned int>(mText.getCharacterSize() * minRatio);
        std::cout << newSize << std::endl;
        mText.setCharacterSize(newSize);
    }

    bool handleEvent(const sf::Event& event) 
    {
        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            onMousePressed(event);
        else if (event.type == sf::Event::MouseButtonReleased)
            return onMouseReleased(event);
        return false;
    }

protected:

    // Центрируем текст в центре прямоугольника
    void centerText()
    {
        sf::FloatRect textBounds = mText.getLocalBounds();
        mText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);

        sf::FloatRect bounds = getBounds();
        sf::Vector2f rectCenter = {bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f};

        mText.setPosition(rectCenter);
    }

    void onMousePressed(const sf::Event& event)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (checkIfContains(mousePosition)) 
            {
                mIsPressed = true;
                mColor = mPressedColor;
            }
        }
    }

    void onMouseMove(const sf::Event& event)
    {
        if (mIsPressed)
            return;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        if (checkIfContains(mousePosition))
            mColor = mHoverColor;
        else
            mColor = mDefaultColor;
    }

    bool onMouseReleased(const sf::Event& event)
    { 
        if (!mIsPressed)
            return false;

        mIsPressed = false;

        sf::Vector2f mousePosition = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (checkIfContains(mousePosition)) 
        {
            mColor = mHoverColor;
            return true;
        }
        else 
        {
            mColor = mDefaultColor;
            return false;
        }
    }
};



class RectangleButton : public Button
{
private:
    sf::Vector2f mSize;

public:

    RectangleButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, sf::Font& font, const sf::String& textData)
    : Button(window, position, font, textData), mSize(size)
    {
        setOptimalFontSize();
        centerText();
    }

    void draw() const override
    {
        static sf::RectangleShape shape;
        shape.setPosition(mPosition);
        shape.setSize(mSize);
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
        mRenderWindow.draw(mText);
    }

    bool checkIfContains(sf::Vector2f position) const override
    {
        sf::FloatRect rect {mPosition.x, mPosition.y, mSize.x, mSize.y};
        return rect.contains(position);
    }

    sf::FloatRect getBounds() const override
    {
        return {mPosition.x, mPosition.y, mSize.x, mSize.y};
    }
};




class CircleButton : public Button
{
private:
    float mRadius;

public:

    CircleButton(sf::RenderWindow& window, sf::Vector2f position, float radius, sf::Font& font, const sf::String& textData)
    : Button(window, position, font, textData), mRadius(radius)
    {
        setOptimalFontSize();
        centerText();
    }

    void draw() const override
    {
        static sf::CircleShape shape(1, 60);
        shape.setPosition(mPosition);
        shape.setRadius(mRadius);
        shape.setFillColor(mColor);
        mRenderWindow.draw(shape);
        mRenderWindow.draw(mText);
    }

    bool checkIfContains(sf::Vector2f position) const override
    {
        sf::Vector2f d = mPosition + sf::Vector2f{mRadius, mRadius} - position;
        float distancesq = d.x * d.x + d.y * d.y;
        return distancesq < mRadius * mRadius;
    }

    sf::FloatRect getBounds() const override
    {
        return {mPosition.x, mPosition.y, 2.f * mRadius, 2.f * mRadius};
    }
};





class SmoothButton : public Button
{
private:
    sf::Vector2f mSize {};
    float mSmoothness  {};

    mutable sf::CircleShape mCornerCircle;
    mutable sf::RectangleShape mHorizontalRectangle;
    mutable sf::RectangleShape mVerticalRectangle;

public:
    SmoothButton(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, float smoothness, sf::Font& font, const sf::String& textData)
    : Button(window, position, font, textData), mSize(size), mSmoothness(smoothness)
    {
        setOptimalFontSize();
        centerText();

        float minSide = std::min(mSize.x, mSize.y);
        float cornerRadius = minSide / 2.f * mSmoothness;

        mCornerCircle.setRadius(cornerRadius);
        mHorizontalRectangle.setSize({mSize.x, mSize.y - 2.f * cornerRadius});
        mVerticalRectangle.setSize({mSize.x - 2.f * cornerRadius, mSize.y});

        mCornerCircle.setFillColor(mColor);
        mHorizontalRectangle.setFillColor(mColor);
        mVerticalRectangle.setFillColor(mColor);

        mCornerCircle.setPosition(mPosition);
        mHorizontalRectangle.setPosition(mPosition + sf::Vector2f{0, mCornerCircle.getRadius()});
        mVerticalRectangle.setPosition(mPosition + sf::Vector2f{mCornerCircle.getRadius(), 0});
    }

    bool checkIfContains(sf::Vector2f position) const override
    {
        bool result =   mHorizontalRectangle.getGlobalBounds().contains(position) 
                        || mVerticalRectangle.getGlobalBounds().contains(position)
                        || checkIfCircleContains(mCornerCircle, position);

        float cornerRadius = mCornerCircle.getRadius();

        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, 0});
        result |= checkIfCircleContains(mCornerCircle, position);

        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, mSize.y - 2.f * cornerRadius});
        result |= checkIfCircleContains(mCornerCircle, position);    

        mCornerCircle.setPosition(mPosition + sf::Vector2f{0, mSize.y - 2.f * cornerRadius});
        result |= checkIfCircleContains(mCornerCircle, position);

        mCornerCircle.setPosition(mPosition);
        return result;
    }



    void draw() const override
    {
        updateColors();
        mRenderWindow.draw(mHorizontalRectangle);
        mRenderWindow.draw(mVerticalRectangle);

        float cornerRadius = mCornerCircle.getRadius();
        mRenderWindow.draw(mCornerCircle);
        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, 0});
        mRenderWindow.draw(mCornerCircle);
        mCornerCircle.setPosition(mPosition + sf::Vector2f{mSize.x - 2.f * cornerRadius, mSize.y - 2.f * cornerRadius});
        mRenderWindow.draw(mCornerCircle);    
        mCornerCircle.setPosition(mPosition + sf::Vector2f{0, mSize.y - 2.f * cornerRadius});
        mRenderWindow.draw(mCornerCircle);
        mCornerCircle.setPosition(mPosition);

        mRenderWindow.draw(mText);
    }

    sf::FloatRect getBounds() const override
    {
        return {mPosition.x, mPosition.y, mSize.x, mSize.y};
    }

private:

    void updateColors() const
    {
        mCornerCircle.setFillColor(mColor);
        mHorizontalRectangle.setFillColor(mColor);
        mVerticalRectangle.setFillColor(mColor);
    }

    static bool checkIfCircleContains(const sf::CircleShape& circle, sf::Vector2f position)
    {
        sf::Vector2f d = circle.getPosition() + sf::Vector2f{circle.getRadius(), circle.getRadius()} - position;
        float distancesq = d.x * d.x + d.y * d.y;
        return distancesq < circle.getRadius() * circle.getRadius();
    }
};


