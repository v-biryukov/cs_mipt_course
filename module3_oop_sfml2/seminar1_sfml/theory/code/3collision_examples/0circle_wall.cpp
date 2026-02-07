#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>


const int width = 800;
const int height = 600;

// Определяет насколько затухает скорость после соударения (1.0 = упругое отталкивание)
float collisionDecay = 0.97f;

// Включить выталкивание из стенки (если оно выключено, то шарик может начать застрявать в стенке)
bool enablePushingOut = false;

// Число кадров в секунду
int framelimit = 60;

// Печатать или нет информацию на экране
bool enableInfo = true;

class Ball 
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity; 
    float radius;
public:
    Ball(sf::Vector2f position, sf::Vector2f velocity, float radius)
    : position(position), velocity(velocity), radius(radius) {}


    void handleCollisions()
    {
        if (position.x > width - radius) 
        {
            if (enablePushingOut) 
                position.x = width - radius;
            velocity.x *= -1;
            velocity *= collisionDecay;
        }

        else if (position.x < radius)
        {
            if (enablePushingOut) 
                position.x = radius;
            velocity.x *= -1;
            velocity *= collisionDecay;
        }

        if (position.y > height - radius) 
        {
            if (enablePushingOut) 
                position.y = height - radius;
            velocity.y *= -1;
            velocity *= collisionDecay;
        }

        else if (position.y < radius) 
        {
            if (enablePushingOut) 
                position.y = radius;
            velocity.y *= -1;
            velocity *= collisionDecay;
        } 
    }

    void update(float dt)
    {
        position += velocity * dt;
        handleCollisions();
    }

    void handleEvent(sf::RenderWindow& window, const sf::Event& event)
    {
        if (event.type == sf::Event::MouseButtonPressed) 
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

            if (event.mouseButton.button == sf::Mouse::Left)
                velocity = (mousePosition - position) * 10.0f;

            if (event.mouseButton.button == sf::Mouse::Right) 
            {
                position = mousePosition;
                velocity = sf::Vector2f(0, 0);
            }
        }
    }


    void draw(sf::RenderWindow& window)
    {
        static sf::CircleShape ballShape;
        ballShape.setFillColor(sf::Color::White);
        ballShape.setRadius(radius);
        ballShape.setOrigin({radius, radius});    
        ballShape.setPosition(position);
        window.draw(ballShape);
    }

};

std::string getInfo(sf::RenderWindow& window) 
{
    return "Info:\n"
    "h           --  hide/show this info\n"
    "left click  --  set ball's velocity\n"
    "right click --  set ball's position\n"
    "Space       --  turn on/off pushing out (currently - " 
    + std::string(enablePushingOut ? "ON" : "OFF") + ")\n"
    "W/S         --  change framelimit (currently " + std::to_string(framelimit) + ")\n"
    "Q/A         --  change collision decay (currently " + std::to_string(collisionDecay) + ")\n";
}

void handleKeyPresses(sf::RenderWindow& window, const sf::Event& event)
{
    switch (event.key.code)
    {
    case sf::Keyboard::H:
        enableInfo = !enableInfo;
        break;

    case sf::Keyboard::Space:
        enablePushingOut = !enablePushingOut;
        break;

    case sf::Keyboard::W:
        framelimit += 1;
        window.setFramerateLimit(framelimit);
        break;
    
    case sf::Keyboard::S:
        framelimit -= 1;
        if (framelimit < 1)
            framelimit = 1;
        window.setFramerateLimit(framelimit);
        break;
    
    case sf::Keyboard::Q:
        collisionDecay += 0.01;
        if (collisionDecay > 1)
            collisionDecay = 1;
        break;
    
    case sf::Keyboard::A:
        collisionDecay -= 0.01;
        if (collisionDecay < 0)
            collisionDecay = 0;
        break;
    
    }
}


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(width, height), "Circle-wall collision detection", sf::Style::Default, settings);
    window.setFramerateLimit(framelimit);

    Ball ball = {{200, 300}, {700, 0}, 28};

    sf::Font font;
    if (!font.loadFromFile("../../../../fonts/sourceCodePro.ttf")) 
    { 
        std::cout << "Error, no font named consolas.ttf" << std::endl;
        std::exit(1);
    }

    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(20);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
                window.close();
                
            if (event.type == sf::Event::KeyPressed) 
                handleKeyPresses(window, event);

            ball.handleEvent(window, event);
        }
        
        window.clear(sf::Color::Black);

        ball.update(1.0f / framelimit);
        ball.draw(window);

        if (enableInfo)
        {
            info.setString(getInfo(window));
            window.draw(info);
        }

        window.display();
    }

    return 0;
}