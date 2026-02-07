#include <SFML/Graphics.hpp>
#include <cmath>

struct Ball
{
    sf::Vector2f position;
    float radius;
    sf::Vector2f velocity;
};

struct Line
{
    sf::Vector2f start, finish;  
};

float operator*(const sf::Vector2f& first, const sf::Vector2f& second)
{
    return first.x*second.x + first.y*second.y;
}

void checkCollision(Ball& ball, const Line& line)
{
    sf::Vector2f a = line.start - ball.position;
    sf::Vector2f b = line.start - line.finish;
    float ab_projection = (a*b) / sqrtf(b*b);
    sf::Vector2f d;
    if (ab_projection < 0)
        d = line.start - ball.position;
    else if (ab_projection > sqrtf(b*b))
        d = line.finish - ball.position;
    else
        d = a - b*(a*b)/(b*b);
    
    if (d*d < ball.radius*ball.radius)
    {
        ball.position -= d*((ball.radius - sqrtf(d*d))/sqrtf(d*d));
        ball.velocity -= 2.0f*d*(d*ball.velocity)/(d*d);
    }
}

void drawLine(sf::RenderWindow& window, const Line& line, sf::Color color = sf::Color::White)
{
    sf::Vertex line_vertices[2] = {sf::Vertex(line.start, color), sf::Vertex(line.finish, color)};
    window.draw(line_vertices, 2, sf::Lines);
}



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle line collision detection", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Ball ball = {{200, 200}, 10, {5, 2}};
    std::vector<Line> lines = {{{300, 600}, {700, 200}},
                     {{700, 200}, {10, 10}},
                     {{10, 10}, {100, 500}},
                     {{100, 500}, {300, 600}},
                     {{300, 260}, {300, 400}}};

    sf::CircleShape ball_shape(ball.radius);
    ball_shape.setFillColor(sf::Color(220, 110, 110));
    ball_shape.setOrigin(ball.radius, ball.radius);
    ball_shape.setPosition(ball.position);

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
                ball.velocity /= 1.1f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                ball.velocity *= 1.1f;

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

        ball.position += ball.velocity;
        for (int i = 0; i < 5; ++i)
            checkCollision(ball, lines[i]);
        
        window.clear(sf::Color::Black);
        ball_shape.setPosition(ball.position);
        window.draw(ball_shape);
        for (int i = 0; i < 5; ++i)
            drawLine(window, lines[i]);

        window.display();
    }
}