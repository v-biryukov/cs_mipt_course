/*
    Данная программа рисует 10 шариков движущихся в гравитационном поле, но если 
    какой-либо шарик  достигает границ окна, то он неупруго отскакивает от границ окна.
    При каждом столкновении со стенкой скорость шарика умножается на ballDecay = 0.95.

    По сравнению с предыдущим примером, нужно просто поменять методы update и handleCollisions.
*/

#include <SFML/Graphics.hpp>
#include <vector>

class Ball
{
private:
    sf::RenderWindow& mRenderWindow;
    sf::Vector2f mPosition {};
    sf::Vector2f mVelocity {};
    float mRadius          {};

public:

    Ball(sf::RenderWindow& window) : mRenderWindow{window} {}

    void update(float dt)
    {
        sf::Vector2f acceleration {0, 1000};
        mVelocity += acceleration * dt;
        mPosition += mVelocity * dt;
        handleCollisions();
    }

    void handleCollisions()
    {
        sf::Vector2f max = mRenderWindow.getView().getSize();
        float ballDecay = 0.95;
        if (float dx = mPosition.x + mRadius - max.x; dx > 0)
        {
            mVelocity.x *= -1;
            mVelocity *= ballDecay;
            mPosition.x += -dx;
        }
        if (float dx = -mPosition.x + mRadius; dx > 0)
        {
            mVelocity.x *= -1;
            mVelocity *= ballDecay;
            mPosition.x += dx;
        }
        if (float dy = mPosition.y + mRadius - max.y; dy > 0)
        {
            mVelocity.y *= -1;
            mVelocity *= ballDecay;
            mPosition.y += -dy;
        }
        if (float dy = -mPosition.y + mRadius; dy > 0)
        {
            mVelocity.y *= -1;
            mVelocity *= ballDecay;
            mPosition.y += dy;
        }
    }

    void draw() const
    {
        static sf::CircleShape circle;
        circle.setFillColor(sf::Color::White);
        circle.setRadius(mRadius);
        circle.setOrigin({mRadius, mRadius});
        circle.setPosition(mPosition);
        mRenderWindow.draw(circle);
    }

    void setPosition(sf::Vector2f position) {mPosition = position;}
    void setVelocity(sf::Vector2f velocity) {mVelocity = velocity;}
    void setRadius(float radius)            {mRadius = radius;}
    sf::Vector2f getPosition() const {return mPosition;}
    sf::Vector2f getVelocity() const {return mVelocity;}
    float        getRadius()   const {return mRadius;}

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Many Balls + Collisions + Gravity + Decay");
    window.setFramerateLimit(60);
    float dt = 1.0f / 60;
    
    std::vector<Ball> balls;
    for (int i = 0; i < 10; ++i)
    {
        Ball ball{window};
        ball.setRadius(10);
        ball.setPosition({200.0f + 50.0f * i, 600.0f - 50.0f * i});
        ball.setVelocity({500, 500});
        balls.push_back(ball);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto& ball : balls)
            ball.update(dt);
        
        window.clear(sf::Color::Black);   
             
        for (auto& ball : balls)
            ball.draw();

        window.display();
    }
}
