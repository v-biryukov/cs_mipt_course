#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

const int window_width = 800;
const int window_height = 800;


struct Ball
{
    sf::Vector2f position;
    float radius;
    sf::Vector2f velocity;
};

struct Rectangle
{
    float left, right;
    float bottom, top;  
};

float operator*(const sf::Vector2f& first, const sf::Vector2f& second)
{
    return first.x*second.x + first.y*second.y;
}

void check_collision(Ball& ball, const Rectangle& rect)
{
    sf::Vector2f d;
    if (ball.position.x < rect.left)
        d.x = rect.left;
    else if (ball.position.x > rect.right)
        d.x = rect.right;
    else
        d.x = ball.position.x;

    if (ball.position.y < rect.bottom)
        d.y = rect.bottom;
    else if (ball.position.y > rect.top)
        d.y = rect.top;
    else
        d.y = ball.position.y;

    d -= ball.position;

    if (d*d < ball.radius*ball.radius && d*d != 0)
    {
        ball.position -= d*((ball.radius - sqrtf(d*d))/sqrtf(d*d));
        ball.velocity -= 2.0f*d*(d*ball.velocity)/(d*d);
    }
}



void update_ball(Ball& ball)
{
    ball.position += ball.velocity;
    if (ball.position.x > window_width - ball.radius)
    {
        // Выталкиваем из стенки
        //ball.position.x -= 2*(ball.position.x - window_width + ball.radius);
        ball.position.x = window_width - ball.radius;

        // Задаём скорость
        ball.velocity.x *= -1;
    }
    else if (ball.position.x < ball.radius)
    {
        //ball.position.x -= 2*(ball.position.x - ball.radius);
        ball.position.x = ball.radius;
        ball.velocity.x *= -1;
    } 
    if (ball.position.y > window_height - ball.radius)
    {
        //ball.position.y -= 2*(ball.position.y - window_height + ball.radius);
        ball.position.y = window_height - ball.radius;
        ball.velocity.y *= -1;
    }
    else if (ball.position.y < ball.radius)
    {
        //ball.position.y -= 2*(ball.position.y - ball.radius);
        ball.position.y = ball.radius;
        ball.velocity.y *= -1;
    } 
}



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Circle rectangle collision detection", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Ball ball = {{200, 200}, 20, {5, 2}};
    std::vector<Rectangle> rectangles = {{300, 350, 200, 260},
                                         {530, 630, 330, 450},
                                         {400, 410, 500, 640},
                                         {600, 700, 400, 520},
                                         {100, 200, 400, 700}
                                         };

    sf::CircleShape ball_shape(ball.radius);
    sf::RectangleShape rect_shape;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    ball.position.x = event.mouseButton.x;
                    ball.position.y = event.mouseButton.y;
                    ball_shape.setPosition(ball.position);

                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                ball.velocity /= 1.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                ball.velocity *= 1.1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                ball.radius *= 1.1f;
                ball_shape.setRadius(ball.radius);
                ball_shape.setOrigin(ball.radius, ball.radius);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                ball.radius /= 1.1f;
                ball_shape.setRadius(ball.radius);
                ball_shape.setOrigin(ball.radius, ball.radius);
            }

        }

        update_ball(ball);
        for (size_t i = 0; i < rectangles.size(); ++i)
            check_collision(ball, rectangles[i]);
        

        window.clear(sf::Color::Black);

        
        ball_shape.setFillColor(sf::Color(255, 100, 100));
        ball_shape.setOrigin(ball.radius, ball.radius);
        ball_shape.setPosition(ball.position);
        window.draw(ball_shape);
        for (size_t i = 0; i < rectangles.size(); ++i)
        {
            rect_shape.setPosition(rectangles[i].left, rectangles[i].bottom);
            sf::Vector2f size = {rectangles[i].right - rectangles[i].left, rectangles[i].top - rectangles[i].bottom};
            rect_shape.setSize(size);
            window.draw(rect_shape);
        }
        

        window.display();
    }

    return 0;
}