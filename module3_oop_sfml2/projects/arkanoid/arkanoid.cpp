#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <cmath>
#include <cstdlib>
#include <ctime>

const double pi = 3.14159265358979323846;


// Вспомагательные функции для работы с векторами типа sf::Vector2f
float operator*(const sf::Vector2f& first, const sf::Vector2f& second)
{
    return first.x * second.x + first.y * second.y;
}

float norm(sf::Vector2f a)
{
    return std::sqrt(a.x * a.x + a.y * a.y);
}

float sqnorm(sf::Vector2f a)
{
    return a.x * a.x + a.y * a.y;
}

// Описываем все классы, которые мы будем использовать в программе
// Это нужно сделать так как даже определение одного класса может зависеть от другого
// Например, класс Bonus зависит от класса Arkanoid и наоборот
struct Ball;
struct Brick;
struct Paddle;
class Bonus;
class BrickGrid;
class Arkanoid;

class Bonus
{
private:
    inline static const float speed = 120;
    inline static const float radius = 15;

    sf::Vector2f m_position;
    float m_time;

public:
    Bonus(sf::Vector2f position);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    void activate(Arkanoid& game);

    bool isColiding(const Paddle& paddle) const;
    // Класс Arkanoid должен быть дружественным, так как он может менять внутреннее объекта-бонуса
    friend class Arkanoid;
};


struct Brick
{
    bool isActive;
};

class BrickGrid
{
private:
    inline static const sf::Color color {100, 200, 250};

    sf::FloatRect m_border;
    int m_numBrickColumns;
    int m_numBrickRows;

    std::vector<Brick> m_bricks;
    sf::RectangleShape m_brickShape;

    int m_numActiveBricks;

public:
    BrickGrid() {}
    BrickGrid(sf::FloatRect borders, int numBrickColumns, int numBrickRows) : 
        m_border(borders), 
        m_numBrickColumns(numBrickColumns), 
        m_numBrickRows(numBrickRows),
        m_numActiveBricks(numBrickColumns * numBrickRows)
    {
        m_bricks.resize(m_numBrickColumns * m_numBrickRows, Brick{true});
        m_brickShape.setSize(getBrickSizes());
        m_brickShape.setOutlineColor(sf::Color::Black);
        m_brickShape.setOutlineThickness(0.5);
        m_brickShape.setFillColor(color);
    }

    sf::FloatRect getBorder() const 
    {
        return m_border;
    }

    sf::Vector2i getGridSizes() const 
    {
        return {m_numBrickColumns, m_numBrickRows};
    }

    sf::Vector2f getBrickSizes() const 
    {
        return {m_border.width / m_numBrickColumns, m_border.height / m_numBrickRows};
    }

    bool isBrickActive(std::pair<int, int> indexes) const
    {
        return m_bricks[indexes.first + indexes.second * m_numBrickColumns].isActive;
    }

    void deactivateBrick(std::pair<int, int> indexes)
    {
        m_bricks[indexes.first + indexes.second * m_numBrickColumns].isActive = false;
        m_numActiveBricks--;
    }

    int getNumActiveBricks() const
    {
        return m_numActiveBricks;
    }

    void draw(sf::RenderWindow& window)
    {
        auto [brickWidth, brickHeight] = getBrickSizes();

        for (int j = 0; j < m_numBrickRows; ++j) 
        {
            for (int i = 0; i < m_numBrickColumns; ++i) 
            {
                if (!isBrickActive({i, j}))
                    continue;
                m_brickShape.setPosition({m_border.left + i * brickWidth, m_border.top + j * brickHeight});
                window.draw(m_brickShape);
            }
        }
    }
};

struct Paddle
{   
    inline static const sf::Color color {sf::Color::White};
    sf::Vector2f position;
    sf::Vector2f size;

    Paddle() {}
    Paddle(sf::Vector2f position, sf::Vector2f size) : position(position), size(size) {}

    sf::FloatRect getBorder() const 
    {
        return {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
    }

    void draw(sf::RenderWindow& window)
    {
        static sf::RectangleShape shape{};
        shape.setPosition(position - size / 2.0f);
        shape.setSize(size);
        shape.setFillColor(color);
        window.draw(shape);
    }
};




struct Ball
{
    inline static const float initialVelocity = 700;
    inline static const sf::Color color {246, 213, 92};
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;

    Ball(float radius, sf::Vector2f position, sf::Vector2f velocity) : 
        radius(radius), position(position), velocity(velocity) {}

    void update(float dt) 
    {
        position += velocity * dt;
    }

    void draw(sf::RenderWindow& window) 
    {
        static sf::CircleShape shape {};
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setFillColor(color);
        shape.setPosition(position);
        window.draw(shape);
    }

    std::pair<sf::Vector2f, bool> findClosestPoint(const sf::FloatRect& rect) const 
    {
        float left   = rect.left;
        float right  = rect.left + rect.width;
        float bottom = rect.top + rect.height;
        float top    = rect.top;

        sf::Vector2f d;
        if (position.x < left)
            d.x = left;
        else if (position.x > right)
            d.x = right;
        else
            d.x = position.x;

        if (position.y > bottom)
            d.y = bottom;
        else if (position.y < top)
            d.y = top;
        else
            d.y = position.y;

        d -= position;
        bool isColiding = sqnorm(d) < radius * radius;
        return {d, isColiding};
    }

    bool handleRectCollision(const sf::FloatRect& rect)
    {
        auto [d, isColiding] = findClosestPoint(rect);
        if (!isColiding)
            return false;

        float closestPointNorm = norm(d);
        // Если расстояние == 0, то это значит, что шарик за 1 фрейм зашёл центром внутрь блока
        // Отражаем шарик от блока
        if (closestPointNorm < 1e-4)
        {
            if (std::fabs(velocity.x) > std::fabs(velocity.y))
                velocity.x *= -1;
            else
                velocity.y *= -1;
        }
        // Если расстояние != 0, но шарик касается блока, то мы можем просчитать отражение более точно
        // Отражение от углов и по касательной.
        else if (closestPointNorm < radius)
        {
            position -= d * ((radius - closestPointNorm) / closestPointNorm);
            velocity -= 2.0f * d * (d * velocity) / (closestPointNorm * closestPointNorm);       
        }
        return true;
    }

    void handleWallsCollision(sf::FloatRect boundary)
    {
        if (position.x < boundary.left + radius)
        {
            position.x = boundary.left + radius;
            velocity.x *= -1;
        }
        if (position.x > boundary.left + boundary.width - radius)
        {
            position.x = boundary.left + boundary.width - radius;
            velocity.x *= -1;
        }
        if (position.y < boundary.top + radius)
        {
            position.y = boundary.top + radius;
            velocity.y *= -1;
        }
    }


    std::pair<int, int> handleBrickGridCollision(const BrickGrid& brickGrid)
    {
        auto [gridColumns, gridRows] = brickGrid.getGridSizes();
        auto [brickWidth, brickHeight] = brickGrid.getBrickSizes();
        auto [left, top, width, height] = brickGrid.getBorder();
        
        // Определяем координаты блоков с которыми шарик может пересечься
        int brickColumnStart  = std::clamp(static_cast<int>((position.x - left - radius) / brickWidth),      0, gridColumns);
        int brickColumnFinish = std::clamp(static_cast<int>((position.x - left + radius) / brickWidth) + 1,  0, gridColumns);
        int brickRowStart     = std::clamp(static_cast<int>((position.y - top  - radius) / brickHeight),     0, gridRows);
        int brickRowFinish    = std::clamp(static_cast<int>((position.y - top  + radius) / brickHeight) + 1, 0, gridRows);

        // Если шарик находится вне сетки блоков, то выходим
        if (brickColumnStart == brickColumnFinish || brickRowStart == brickRowFinish)
            return {-1, -1};

        // Находим ближайший к центру шарика активный пересекаемый шариком блок
        float closestSqNorm = width * width + height * height;
        std::pair<int, int> closestBrickIndexes = {-1, -1};
        for (int i = brickColumnStart; i < brickColumnFinish; ++i)
        {
            for (int j = brickRowStart; j < brickRowFinish; ++j)
            {
                if (!brickGrid.isBrickActive({i, j}))
                    continue;

                sf::FloatRect rect {left + i * brickWidth, top + j * brickHeight, brickWidth, brickHeight};
                auto [d, isColiding] = findClosestPoint(rect);
                if (!isColiding)
                    continue;

                if (sqnorm(d) < closestSqNorm)
                {
                    closestSqNorm = sqnorm(d);
                    closestBrickIndexes = {i, j};
                }
            }
        }

        // Если такого не нашли, то возвращаем {-1, -1}
        if (closestBrickIndexes.first == -1)
            return closestBrickIndexes;

        // Упруго сталкиваем шарик с найденым блоком
        sf::FloatRect rect {left + closestBrickIndexes.first * brickWidth, top + closestBrickIndexes.second * brickHeight, brickWidth, brickHeight};
        handleRectCollision(rect);

        // Возвращаем координаты блока в сетки блоков
        return closestBrickIndexes;
    }

    // Обрабатываем столкновения шарика с ракеткой
    void handlePaddleCollision(const Paddle& paddle)
    {
        auto [d, isColiding] = findClosestPoint(paddle.getBorder());
        if (!isColiding)
            return;

        // Столкновение не упругое
        // Угол отражения зависит от места на ракетке, куда стукнулся шарик
        // Если шарик стукнулся в левую часть ракетки, то он должен полететь влево.
        // Если в правую часть ракетки, то вправо.
        const float pi = 3.14159265;
        float velocityAngle = (position.x - paddle.position.x) / (paddle.size.x + 2 * radius) * (0.8 * pi) + pi / 2;
        float velocityNorm = norm(velocity);
        velocity.x = - velocityNorm * std::cos(velocityAngle);
        velocity.y = - velocityNorm * std::sin(velocityAngle);
    }
};




class Arkanoid
{
private:
    // Константы:
    // Цвет задника
    const sf::Color kBackgroundColor {12, 31, 47};
    // Максимально возможное количество шариков в один момент времени
    const unsigned kMaxNumBalls {250};
    // Максимально возможное количество бонусов в один момент времени
    const unsigned kMaxNumBonuses {10};

    // Поля:

    // Время, которое прошло с начала игры в секундах
    double m_time;
    // Границы игрового поля
    sf::FloatRect m_border;
    // Связный список всех шариков
    std::list<Ball> m_balls;
    // Объект, задающий состояние сетки блоков
    BrickGrid m_brickGrid;
    // Ракетка
    Paddle m_paddle;
    // Состояние игры
    enum class GameState {stuck, running, endLose, endWin};
    GameState m_gameState;

    // Текущее число жизней
    int m_numLives;

    // Связный список указателей на бонусы
    // Почему указатели - для реализации полиформизма
    // Так как в будущем мы хотим сделать несколько вариантов бонусов
    std::list<Bonus*> m_bonuses;

    // Вероятность того, что при разрушении блока выпадет бонус
    float m_bonusProbability;

    // Макет шарика, используемый для рисова
    Ball m_initialBall {6, {0, 0}, {0, 0}};

    // Текст, который рисуется в конце игры
    sf::Text m_endText;


    void addRandomBonus(sf::Vector2f position)
    {
        if (m_bonuses.size() > kMaxNumBonuses)
            return;
        int max_rand = 10000;
        if ((rand() % max_rand) * 1.0f / max_rand < m_bonusProbability) 
        {
            m_bonuses.push_back(new Bonus(position));
        }
    }

    // Функция, которая обрабатывает все столкновения шарика 
    void handleBallCollisions(Ball& ball) 
    {
        ball.handleWallsCollision(m_border);
        ball.handlePaddleCollision(m_paddle);

        auto indexes = ball.handleBrickGridCollision(m_brickGrid);
        if (indexes.first == -1)
            return;
        m_brickGrid.deactivateBrick(indexes);
        addRandomBonus(ball.position);
    }



public:
    Arkanoid(sf::FloatRect border, sf::Font& font) :
        m_time{0.0},
        m_border{border},
        m_paddle{{m_border.left + m_border.width / 2, m_border.top + m_border.height - 100}, {120, 20}},
        m_gameState{GameState::stuck},
        m_numLives{7}
    {
        float gap = border.width / 10;
        m_brickGrid = BrickGrid({border.left + gap, border.top + gap, border.width - 2 * gap, border.height / 2}, 50, 30);
        m_bonusProbability = 0.1;

        m_endText.setFont(font);
        m_endText.setString("You Win!");
        m_endText.setCharacterSize(100);
        m_endText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = m_endText.getLocalBounds();
        m_endText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
        m_endText.setPosition({border.left + border.width / 2, border.top + border.height / 2});
    }

    sf::FloatRect getBorder() const
    {
        return m_border;
    }

    const Paddle& getPaddle() const
    {
        return m_paddle;
    }

    const BrickGrid& getBrickGrid() const
    {
        return m_brickGrid;
    }

    void addBall(const Ball& ball)
    {
        if (m_balls.size() < kMaxNumBalls)
            m_balls.push_back(ball);
    }

    // Эта функция вызывается каждый кадр
    void update(const sf::RenderWindow& window, float dt)
    {
        m_time += dt;

        // Устанавливаем положение ракетки
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        m_paddle.position.x = mousePosition.x;

        // Обрабатываем шарики
        for (std::list<Ball>::iterator it = m_balls.begin(); it != m_balls.end();)
        {
            (*it).update(dt);
            handleBallCollisions(*it);
            if ((*it).position.y > m_border.top + m_border.height)
            {
                it = m_balls.erase(it);
            }
            else
            {
                it++;
            }
        }

        // Если шариков нет, то переходи в режим начала игры и уменьшаем кол-во жизней
        if (m_gameState == GameState::running && m_balls.size() == 0)
        {
            m_gameState = GameState::stuck;
            m_numLives--;
        }

        // Если жизни кончились, то переходим в состояние конца игры (проигрыш)
        if (m_numLives < 0)
        {
            m_gameState = GameState::endLose;
        }

        // Если блоки кончились, то переходим в состояние конца игры (победа)
        if (m_brickGrid.getNumActiveBricks() == 0)
        {
            m_gameState = GameState::endWin;
        }
        
        // Обрабатываем бонусы
        for (auto it = m_bonuses.begin(); it != m_bonuses.end();)
        {
            (*it)->update(dt);
            if ((*it)->isColiding(m_paddle))
            {
                (*it)->activate(*this);
                delete *it;
                it = m_bonuses.erase(it);
            }
            else if ((*it)->m_position.y > m_border.top + m_border.height)
            { 
                delete (*it);
                it = m_bonuses.erase(it);
            }
            else
            {
                it++;
            }
            
        }
    }

    void draw(sf::RenderWindow& window)
    {
        // Рисуем задний прямоугольник
        static sf::RectangleShape background {{m_border.width, m_border.height}};
        background.setPosition({m_border.left, m_border.top});
        background.setFillColor(kBackgroundColor);
        window.draw(background);

        // Рисуем блоки
        m_brickGrid.draw(window);

        // Рисуем шарики
        for (Ball& ball : m_balls)
        {
            ball.draw(window);
        }

        // Рисуем ракетку
        m_paddle.draw(window);

        // Если мы в режиме начала игры, то рисуем шарик на ракетке
        if (m_gameState == GameState::stuck)
        {
            m_initialBall.position = {m_paddle.position.x, m_paddle.position.y - m_paddle.size.y / 2 - m_initialBall.radius};
            m_initialBall.position = {m_paddle.position.x, m_paddle.position.y - m_paddle.size.y / 2 - m_initialBall.radius};
            m_initialBall.draw(window);
        }

        // Рисуем кол-во жизней вверху слева
        for (int i = 0; i < m_numLives; i++)
        {
            m_initialBall.position = {m_initialBall.radius * (3 * i + 2), 2 * m_initialBall.radius};
            m_initialBall.draw(window);
        }

        // Рисуем бонусы
        for (Bonus* pbonus : m_bonuses)
        {
            pbonus->draw(window);
        }

        // При завершении игры рисуем надпись
        if (m_gameState == GameState::endWin)
        {
            m_endText.setString("You Win!");
            window.draw(m_endText);
        }

        // При завершении игры рисуем надпись
        if (m_gameState == GameState::endLose)
        {
            m_endText.setString("You Lose!");
            window.draw(m_endText);
        }
    }

    void onMousePressed(sf::Event& event)
    {
        switch (m_gameState)
        {
            case GameState::stuck:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_gameState = GameState::running;
                    float velocityAngle = (rand() % 100 + 40) * pi / 180;
                    float velocityNorm = Ball::initialVelocity;
                    sf::Vector2f newPosition = {m_paddle.position.x, m_paddle.position.y - m_paddle.size.y / 2.0f - m_initialBall.radius};
                    sf::Vector2f newVelocity = {-velocityNorm * cosf(velocityAngle), -velocityNorm * sinf(velocityAngle)};
                    addBall({m_initialBall.radius, newPosition, newVelocity});
                }
                break;

            case GameState::running:
                break;
            case GameState::endLose:
                break;
            case GameState::endWin:
                break;
        }
    }

    // Класс бонус должен быть дружественным, так как он может менять внутреннее состояние игры
    friend class Bonus;
};


Bonus::Bonus(sf::Vector2f position): m_position(position)
{
    m_time = 0;
}

// Двигаем бонус
void Bonus::update(float dt)
{
    m_time += dt;
    m_position.y += speed * dt;
}

// Рисуем бонус
void Bonus::draw(sf::RenderWindow& window) const
{
    // Рисуем белый круг
    static sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(sf::Color{100, 200, 100});
    shape.setPosition(m_position);
    window.draw(shape);

    float angle = 0;
    // Рисуем 3 шарика на этом круге
    static Ball ball {5, {0, 0}, {0, 0}};
    float ballRotationRadius = 7;
    ball.position = m_position + ballRotationRadius * sf::Vector2f(std::cos(angle), std::sin(angle));
    ball.draw(window);
    angle += 2.0 * pi / 3.0;
    ball.position = m_position + ballRotationRadius * sf::Vector2f(std::cos(angle), std::sin(angle));
    ball.draw(window);
    angle += 2.0 * pi / 3.0;
    ball.position = m_position + ballRotationRadius * sf::Vector2f(std::cos(angle), std::sin(angle));
    ball.draw(window);
}


/*
    Функция Bonus::activate

    Применяем эффект бонуса (в данном случае - утроение шариков)
    numBalls - Количество шариков до утроения
    Шарики хранятся в связном списке m_balls
    Так как мы работаем со связным списком, то придётся использовать итератор it

    Проходим итератором по изначальным элементам списка и добавляем новые шарики в список
    В данном случае простой цикл через итераторы не сработает, так как массив game.m_balls увеличивается в процессе выполнения цикла.

    Внутри цикла выбираем случайный вектор скорости и добавляем шарик в список game.m_balls
    Делаем то же самое для ещё одного шарика
    В конце цикла переходим ко следующему шарику в списке, т.е. увеличивем итератор it

*/
void Bonus::activate(Arkanoid& game)
{
    int numBalls = game.m_balls.size();
    std::list<Ball>::iterator it = game.m_balls.begin();

    for (int i = 0; i < numBalls; i++)
    {
        float angle = rand() % 1000 * (2 * pi / 1000);
        float vx = Ball::initialVelocity * sin(angle);
        float vy = Ball::initialVelocity * cos(angle);
        game.addBall({game.m_initialBall.radius, (*it).position, {vx, vy}});

        angle = rand() % 1000 * (2 * pi / 1000);
        vx = Ball::initialVelocity * sin(angle);
        vy = Ball::initialVelocity * cos(angle);
        game.addBall({game.m_initialBall.radius, (*it).position, {vx, vy}});

        it++;
    }
}

bool Bonus::isColiding(const Paddle& paddle) const
{
    bool result = paddle.getBorder().intersects({m_position.x - radius, m_position.y - radius, 2 * radius, 2 * radius});
    return result;
}


int main () 
{
    srand(time(0));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 800, 32), "Arkanoid", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    sf::Clock clock;
        
    sf::Font font;
    if (!font.loadFromFile("consola.ttf"))
    {
        std::cout << "Can't load font consola.ttf" << std::endl;
        std::exit(1);
    }
    Arkanoid game({0, 0, 1000, 800}, font);
        

    while (window.isOpen()) 
    {
        float dt = clock.restart().asSeconds();
        std::cout << "FPS=" << static_cast<int>(1.0 / dt) << "\n"; 

        // Обработка событий
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                game.onMousePressed(event);
            }
        }
        window.clear(sf::Color(0, 0, 0));
        // Расчитываем новые координаты и новую скорость шарика
        game.update(window, dt);
        game.draw(window);

        // Отображам всё нарисованное на временном "холсте" на экран
        window.display();
    }
    return EXIT_SUCCESS;
}
