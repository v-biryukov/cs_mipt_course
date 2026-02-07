/*
    Данная программа рисует 10 шариков движущихся с постоянной скоростью,
    но если какой-либо шарик выходит за границы окна, он появляется с другой стороны.

    Исправим предыдущую программу. Создадим класс Ball, который хранить положение, скорость и радиус 
    шарика, а также описывать всё поведение шарика.


    В классе Ball будем также хранить ссылку на окно RenderWindow:

        sf::RenderWindow& mRenderWindow;

    Это позволит проще написать методы draw и handleCollisions. Как вариант, можно не хранить ссылку 
    на окно в каждом шарике, а просто передавать ссылку на окно как параметр в методы draw и handleCollisions.

    Также в классе Ball были написаны геттеры и сеттеры для полей класса.
    В методе draw рисуем кружок, используя sf::CircleShape. Чтобы объект sf::CircleShape не создавался
    заново каждый раз при входе в функцию draw, сделаем его статическим.
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
        mPosition += mVelocity * dt;
        handleCollisions();
    }

    void handleCollisions()
    {
        sf::Vector2f max = mRenderWindow.getView().getSize();
        if (mPosition.x - mRadius > max.x)
            mPosition += sf::Vector2f{-max.x - 2 * mRadius, 0};
        if (mPosition.y - mRadius > max.y)
            mPosition += sf::Vector2f{0, -max.y - 2 * mRadius};
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
    sf::RenderWindow window(sf::VideoMode(800, 800), "Many Balls");
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
