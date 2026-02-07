#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


// Программа, которая создаёт бегающего героя

class Animation
{
private:
    sf::IntRect m_textureRect;
    int m_numberOfFrames;
    float m_animationSpeed;
    float m_time;

public:
    Animation() 
    {
    }
    Animation(sf::IntRect textureRect, int numberOfFrames, float animationSpeed) :
              m_numberOfFrames(numberOfFrames), m_animationSpeed(animationSpeed), m_textureRect(textureRect)
    {   
    }

    void update(float dt)
    {
        m_time += dt;
        if (m_time > m_numberOfFrames / m_animationSpeed)
            m_time -= m_numberOfFrames / m_animationSpeed;
    }

    // Функция, которая устанавливает координаты спрайта на текстуре
    // в соответствии с этой анимацией
    void setSprite(sf::Sprite& sprite, bool isFacedRight)
    {
        int currentFrame = static_cast<int>(m_animationSpeed * m_time) % m_numberOfFrames;
        if (isFacedRight)
        {
            m_textureRect.left = currentFrame * m_textureRect.width;
            sprite.setTextureRect(m_textureRect);
        }
        else
        {
            m_textureRect.left = (currentFrame + 1) * m_textureRect.width;
            m_textureRect.width *= -1;
            sprite.setTextureRect(m_textureRect);
            m_textureRect.width *= -1;
        }
    }
};


// Используем паттерн: машина состояний (fsm)
class Player;
class PlayerState
{
protected:
    Animation animation;
public:
    PlayerState()
    {
    }
    virtual void startRunning(Player* sm) = 0;
    virtual void stop(Player* sm) = 0;
    void update(float dt)
    {
        animation.update(dt);
    }
    void setSprite(sf::Sprite& sprite, int direction)
    {
        animation.setSprite(sprite, direction);
    }
    virtual ~PlayerState() {};
};

class Idle : public PlayerState
{
public:
    Idle()
    {
        animation = Animation({0, 0, 19, 34}, 12, 12);
        cout << "Creating Idle state" << endl;
    }
    void startRunning(Player* player);
    void stop(Player* player);
};

class Running : public PlayerState
{
public:
    Running()
    {
        animation = Animation({0, 64, 21, 34}, 8, 12);
        cout << "Creating Running state" << endl;
    }
    void startRunning(Player* player);
    void stop(Player* player);
};


// Класс машина состояний будет объедина с классом Player
class Player
{
private:
    PlayerState* state;
    sf::Texture texture;
    sf::Sprite sprite;
    bool isFacedRight;
    sf::Vector2f velocity;
    float speed;

    void setState(PlayerState* newState)
    {
        delete state;
        state = newState;
    }

public:
    Player(sf::Vector2f position = {0, 0})
    {
        if (!texture.loadFromFile("./hero.png"))
        {
            std::cout << "Can't load image ./hero.png for Player class" << std::endl;
            std::exit(1);
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(5, 5);
        state = new Idle();
        speed = 500.0;
    }

    void update(float dt)
    {
        state->update(dt);
        velocity = {0, 0};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocity.x -= speed;
            isFacedRight = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocity.x += speed;
            isFacedRight = true;
        }
        sprite.setPosition(sprite.getPosition() + velocity * dt);
    }

    void draw(sf::RenderWindow& window)
    {
        state->setSprite(sprite, isFacedRight);
        window.draw(sprite);
    }


    void handleEvents(const sf::Event& event) 
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                state->startRunning(this);
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Left && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                state->stop(this);
            if (event.key.code == sf::Keyboard::Right && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                state->stop(this);
        }
    }

    ~Player()
    {
        delete state;
    }

    friend class PlayerState;
    friend class Idle;
    friend class Running;
};


void Idle::startRunning(Player* player)
{
    player->setState(new Running());
}

void Idle::stop(Player* player)
{
}

void Running::startRunning(Player* player)
{
}

void Running::stop(Player* player)
{
    player->setState(new Idle());
}


// Благодаря полиморфизму, код выглядит просто и в класс Player и в основном цикле
// код состояний описывается внутри каждого состояния
// Более того этот код гораздо более расширяем
// Можно очень просто добавить новое состояние

int main () 
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Player states");
    window.setFramerateLimit(60);
    float time = 0;
    float dt = 1.0 / 60;
    Player player({400, 400});

    while (window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
                window.close();
            player.handleEvents(event);
        }
        window.clear(sf::Color::Black);

        player.update(dt);
        player.draw(window);

        window.display();
        time += 1.0 / 60;
    }

    return 0;
}



/*
    Задания:
        1) Добавить остальные состояния. Они должны правильно отрисововаться.
           При этом понадобится внести изменения и в класс Player.
           Например, для состояния Falling нужно будет добавить гравитацию

        2) Нарисовать на экране прямоугольнике, по которым герой может
           бегать и цепляться за углы
           Это проще всего сделать введя новый класс World или Game, который будет содержать
           экземпляр Player, а так же остальные параметры мира, такие как положение и размеры
           всех прямоугольников.
    
        3) Добавить background.png на экран. 
           Персонаж должен правильно взаимодействовать с окружением.
           Это проще всего сделать введя новый класс World или Game, который будет содержать
                            экземпляр Player, а так же остальные параметры мира.
*/