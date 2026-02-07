#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>


const int windowWidth = 1024;
const int windowHeight = 768;


bool enableBallPushingOut = true;
bool enableInfo = true;

float collisionDecay = 0.99f;
int framelimit = 60;

// Перегрузим оператор, для удобного вычисления скалярного произведения
// Операторы + - = += -= уже перегружены в SFML по умолчанию
float operator*(const sf::Vector2f& first, const sf::Vector2f& second)
{
    return first.x*second.x + first.y*second.y;
}

struct Ball
{
    sf::Vector2f position;
    sf::Vector2f velocity; 
    float radius;
    float mass;

    Ball(sf::Vector2f position, sf::Vector2f velocity, float radius, float mass)
    : position(position), velocity(velocity), radius(radius), mass(mass) {}

    Ball(){}

    void draw(sf::RenderWindow& window)
    {
        static sf::CircleShape ballShape;
        ballShape.setFillColor(sf::Color::White);
        ballShape.setRadius(radius);
        ballShape.setOrigin(radius, radius);    
        ballShape.setPosition(position);
        int colorIntensity = 400 - static_cast<int>(mass);
        if (colorIntensity < 120) colorIntensity = 120;
        if (colorIntensity > 255) colorIntensity = 255;
        ballShape.setFillColor(sf::Color(255 - mass, 255 - mass/2, 255 - mass/2));
        window.draw(ballShape);
    }

    void update(float dt)
    {
        position += velocity * dt;
        if (position.x > windowWidth - radius)
        {
            // Выталкиваем из стенки
            position.x = windowWidth - radius;
            // Задаём скорость
            velocity.x *= -1;
            // Затухание скорости при соударении
            velocity *= collisionDecay;
        }
        else if (position.x < radius)
        {
            position.x = radius;
            velocity.x *= -1;
            velocity *= collisionDecay;
        } 
        if (position.y > windowHeight - radius)
        {
            position.y = windowHeight - radius;
            velocity.y *= -1;
            velocity *= collisionDecay;
        }
        else if (position.y < radius)
        {
            position.y = radius;
            velocity.y *= -1;
            velocity *= collisionDecay;
        } 
    }
};


void handleCollision(Ball& a, Ball& b)
{
    sf::Vector2f d = a.position - b.position;
    if (d * d < (a.radius + b.radius) * (a.radius + b.radius))
    {
        // Переходим в систему отсчёта, связанную с центром масс
        sf::Vector2f centerMassVelocity = (a.mass * a.velocity + b.mass * b.velocity) / (a.mass + b.mass);
        a.velocity -= centerMassVelocity;
        b.velocity -= centerMassVelocity;
        // В этой системе нужно просто обратить составляющую скорости, параллельную вектору d
        // (velocity*d)/(d*d)*d - это вектор проекции скорости на вектор d
        a.velocity -= 2 * (a.velocity * d) / (d * d) * d;
        b.velocity -= 2 * (b.velocity * d) / (d * d) * d;

        // Выталкивание (если его отключить, то шары могут слипаться)
        if (enableBallPushingOut)
        {
            float dnorm = std::sqrt(d * d);
            float av = std::abs(a.velocity * d);
            float bv = std::abs(b.velocity * d);
            float intersectDepth = (a.radius + b.radius - dnorm);
            a.position += av / (av + bv) * intersectDepth / dnorm * d;
            b.position -= bv / (av + bv) * intersectDepth / dnorm * d;
        }

        // Затухание скорости при соударении
        a.velocity *= collisionDecay;
        b.velocity *= collisionDecay;

        // Переходим обратно в глобальную систему отсчёта
        a.velocity += centerMassVelocity;
        b.velocity += centerMassVelocity;
    }
}

Ball createRandomBall(float x, float y, float max_speed)
{
    Ball randomBall;
    randomBall.radius = 10 + rand() % 40;
    randomBall.mass = 30 + rand() % 220;
    randomBall.position.x = x;
    randomBall.position.y = y;
    randomBall.velocity.x = (rand() % (2*(int)max_speed + 1)) - max_speed;
    randomBall.velocity.y = (rand() % (2*(int)max_speed + 1)) - max_speed;
    return randomBall;
}


std::string getInfo(sf::RenderWindow& window)
{
    return "Info:\n"
    "h           --  hide/show this info\n"
    "left click  --  create ball\n"
    "right click --  create high speed ball\n"
    "Space       --  turn on/off ball pushing out (currently - " 
        + std::string(enableBallPushingOut ? "ON" : "OFF") + ")\n"
    "W/S         --  change framelimit (currently " + std::to_string(framelimit) + ")\n"
    "Q/A         --  change collision decay (currently " + std::to_string(collisionDecay) + ")\n";
}


void handleKeyPresses(sf::RenderWindow& window, const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::H)
    {
        enableInfo = !enableInfo;
    }
    if (event.key.code == sf::Keyboard::Space)
    {
        enableBallPushingOut = !enableBallPushingOut;
    }
    if (event.key.code == sf::Keyboard::W)
    {
        framelimit += 1;
        window.setFramerateLimit(framelimit);
    }
    if (event.key.code == sf::Keyboard::S)
    {
        framelimit -= 1;
        if (framelimit < 1)
            framelimit = 1;
        window.setFramerateLimit(framelimit);
    }
    if (event.key.code == sf::Keyboard::Q)
    {
        collisionDecay += 0.01;
        if (collisionDecay > 1)
            collisionDecay = 1;
    }
    if (event.key.code == sf::Keyboard::A)
    {
        collisionDecay -= 0.01;
        if (collisionDecay < 0)
            collisionDecay = 0;
    }
}


int main()
{
    srand(time(0));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Circle circle elastic bounce", sf::Style::Default, settings);
    window.setFramerateLimit(framelimit);

    sf::Font font;
    if (!font.loadFromFile("../../../../fonts/sourceCodePro.ttf"))
    {
        std::cout << "Error: Font file not found." << std::endl;
        std::exit(1);
    }
    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(20);



    std::vector<Ball> balls;
    balls.push_back({{200, 300}, {300, 0}, 20, 70});
    balls.push_back({{600, 340}, {-300, 0}, 50, 5000});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                handleKeyPresses(window, event);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    balls.push_back(createRandomBall(event.mouseButton.x, event.mouseButton.y, 300));
                if (event.mouseButton.button == sf::Mouse::Right)
                    balls.push_back(createRandomBall(event.mouseButton.x, event.mouseButton.y, 1500));
            }
        }
        

        // Перемещаем все шарики
        for (int i = 0; i < balls.size(); ++i)
            balls[i].update(1.0f / framelimit);

        // Обрабатываем столкновения
        for (int i = 0; i < balls.size(); ++i)
        {
            for (int j = i+1; j < balls.size(); ++j)
                handleCollision(balls[i], balls[j]);
        }
        

        window.clear(sf::Color::Black);
        for (int i = 0; i < balls.size(); ++i)
            balls[i].draw(window);

        info.setString(getInfo(window));
        if (enableInfo)
            window.draw(info);

        window.display();
    }
}