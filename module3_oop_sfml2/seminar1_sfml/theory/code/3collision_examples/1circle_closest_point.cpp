#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Перегрузим оператор, для удобного вычисления скалярного произведения
// Операторы + - = += -= уже перегружены в SFML по умолчанию
float operator*(const sf::Vector2f& first, const sf::Vector2f& second)
{
    return first.x*second.x + first.y*second.y;
}

const int windowWidth = 800;
const int windowHeight = 600;
int framelimit = 60;

struct Ball
{
    sf::Vector2f position;
    sf::Vector2f velocity; 
    float radius;

    Ball(sf::Vector2f position, sf::Vector2f velocity, float radius):
            position(position), velocity(velocity), radius(radius)
    {
    }

    void draw(sf::RenderWindow& window)
    {
        sf::CircleShape ball_shape; // тут можно написать поэффективней и не создавать экземпляр каждый раз
        ball_shape.setFillColor(sf::Color::White);
        ball_shape.setRadius(radius);
        ball_shape.setOrigin(radius, radius);    
        ball_shape.setPosition(position);
        window.draw(ball_shape);
    }
};

struct LineSegemnt
{
    sf::Vector2f start;
    sf::Vector2f finish;

    sf::Color color;

    LineSegemnt(sf::Vector2f start, sf::Vector2f finish, sf::Color color = sf::Color::White) : 
        start(start), finish(finish), color(color)
    {}

    void draw(sf::RenderWindow& window)
    {
        sf::Vertex line_vertices[2] = {sf::Vertex(start, color), sf::Vertex(finish, color)};
        window.draw(line_vertices, 2, sf::Lines);
    }
};

struct Rectangle
{
    float left, right;
    float bottom, top;
    sf::Color color;

    Rectangle(float left, float right, float bottom, float top, sf::Color color = sf::Color::White) :
        left(left), right(right), bottom(bottom), top(top), color(color)
    {}

    void draw(sf::RenderWindow& window)
    {
        sf::RectangleShape rect({right - left, top - bottom});
        rect.setPosition(left, bottom);
        rect.setFillColor(color);
        window.draw(rect);
    }
};


// Находим вектор для кратчайшего расстояния между шариком и прямоугольником
sf::Vector2f getClosest(const Ball& ball, const Rectangle& rect)
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
    return d;
}

// Находим вектор для кратчайшего расстояния между шариком и отрезком
sf::Vector2f getClosest(const Ball& ball, const LineSegemnt& line)
{
    sf::Vector2f a = line.start - ball.position;
    sf::Vector2f b = line.start - line.finish;
    float ab_projection = (a*b) / std::sqrt(b*b);
    sf::Vector2f d;
    if (ab_projection < 0)
        d = line.start - ball.position;
    else if (ab_projection > std::sqrt(b*b))
        d = line.finish - ball.position;
    else
        d = a - b*(a*b)/(b*b);
    return d;
}

// Рисуем отрезок кратчайшего расстояния с красным кружочком на конце
void drawClosestVector(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f finish)
{
    LineSegemnt(start, finish).draw(window);

    sf::CircleShape contact_circle(5.0f);
    contact_circle.setOrigin(5.0f, 5.0f);
    contact_circle.setPosition(start);
    contact_circle.setFillColor(sf::Color::Red);
    window.draw(contact_circle);

    contact_circle.setPosition(finish);
    window.draw(contact_circle);
}




int main()
{
    std::srand(std::time(0));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Circle closest point detection", sf::Style::Default, settings);
    window.setFramerateLimit(framelimit);

    Ball ball = {{200, 300}, {0, 0}, 28};
    LineSegemnt line = {{100, 200}, {400, 500}};
    Rectangle rect = {500, 600, 100, 300};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
                ball.position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
        }
        

        window.clear(sf::Color::Black);

        line.draw(window);
        rect.draw(window);
        drawClosestVector(window, ball.position, ball.position + getClosest(ball, line));
        drawClosestVector(window, ball.position, ball.position + getClosest(ball, rect));
        ball.draw(window);

        window.display();
    }

    return 0;
}