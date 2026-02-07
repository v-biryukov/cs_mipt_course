#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>


float operator*(const sf::Vector2f& first, const sf::Vector2f& second)
{
    return first.x*second.x + first.y*second.y;
}


struct Ball
{
    sf::Vector2f position;
    float radius;
    sf::Vector2f velocity;
};

struct Line
{
    sf::Vector2f start, finish; 

    Line(sf::Vector2f start, sf::Vector2f finish) : start{start}, finish{finish} {}
    Line(float x1, float y1, float x2, float y2) : start{x1, y1}, finish{x2, y2} {}

    void draw(sf::RenderWindow& window, sf::Color color = sf::Color::White)
    {
        sf::Vertex lineVertices[2] = {sf::Vertex(start, color), sf::Vertex(finish, color)};
        window.draw(lineVertices, 2, sf::Lines);
    }
};




class Frame
{
private:
    Ball ball;
    sf::CircleShape ballShape;
    std::vector<Line> lines;

    sf::RenderWindow* window;

    void checkCollision(const Line& line)
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


    float min(float a, float b) const
    {
        return (a < b) ? a : b; 
    }

    float max(float a, float b) const
    {
        return (a > b) ? a : b; 
    }

    bool isIntersecting(Line line1, Line line2, sf::Vector2f& intersectionPoint) const
    {
        float x1 = line1.start.x, x2 = line1.finish.x, x3 = line2.start.x, x4 = line2.finish.x;
        float y1 = line1.start.y, y2 = line1.finish.y, y3 = line2.start.y, y4 = line2.finish.y;
         
        float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (d == 0) 
            return false;
         
        float pre = (x1*y2 - y1*x2); 
        float post = (x3*y4 - y3*x4);
        float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
        float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;
         
        if (x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4) ) 
            return false;
        if ( y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4) ) 
            return false;
         
        intersectionPoint.x = x;
        intersectionPoint.y = y;
        return true;
    }

    void raycast(sf::Vector2f movement)
    {
        float min_sqdistance = movement * movement;
        int closest_line_id = -1;
        sf::Vector2f intersectionPoint;
        Line ray(ball.position, ball.position + movement);
        
        for (size_t i = 0; i < lines.size(); i++) 
        {
            if (isIntersecting(ray, lines[i], intersectionPoint))
            {
                float sqdistance = (ball.position - intersectionPoint)*(ball.position - intersectionPoint);
                if (sqdistance < min_sqdistance)
                {
                    min_sqdistance = sqdistance;
                    closest_line_id = i;
                }
            }
        }

        if (closest_line_id == -1)
        {
            ball.position += movement;
            for (size_t i = 0; i < lines.size(); i++)
                checkCollision(lines[i]);
            ray.draw(*window, sf::Color::Red);
        }
        else
        {
            sf::Vector2f oldPosition = ball.position;
            sf::Vector2f d = (intersectionPoint - ball.position);
            Line(ball.position, intersectionPoint).draw(*window, sf::Color::Red);
            ball.position += d/std::sqrt(d*d)*(std::sqrt(d*d) - ball.radius);
            checkCollision(lines[closest_line_id]);

            sf::Vector2f newMovement = std::sqrt((movement - (intersectionPoint - oldPosition))*(movement - (intersectionPoint - oldPosition)))
                                        / std::sqrt(ball.velocity*ball.velocity) * ball.velocity;
            raycast(newMovement);
        }


    }


public: 
    Frame(sf::RenderWindow* window, Ball ball, std::vector<Line> lines) : window(window), ball(ball), lines(lines) 
    {
        
        ballShape.setRadius(ball.radius);
        ballShape.setFillColor(sf::Color(220, 110, 110));
        ballShape.setOrigin(ball.radius, ball.radius);
        ballShape.setPosition(ball.position);
    }

    void step()
    {
        raycast(ball.velocity);
    }


    void draw()
    {
        ballShape.setPosition(ball.position);
        window->draw(ballShape);
        for (size_t i = 0; i < lines.size(); ++i)
            lines[i].draw(*window);
    }

    void run()
    {
        int step = 0;
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window->close();
            }
            window->clear(sf::Color::Black);
            step();
            draw();
            window->display();
            // window->capture().saveToFile("sc" + std::to_string(step) + ".png");
            step++;
        }
    }
};


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Raycast circle line collision detection", sf::Style::Default, settings);
    window.setFramerateLimit(10);

    Ball ball = {{200, 200}, 5, {50, 50}};
    std::vector<Line> lines = 
    {
        {{300, 600},    {700, 200}  },
        {{700, 200},    {10, 10}    },
        {{10, 10},      {100, 500}  },
        {{100, 500},    {300, 600}  },
        {{300, 260},    {301, 400}  }

    };

    Frame frame = {&window, ball, lines};
    frame.run();
    return 0;
}