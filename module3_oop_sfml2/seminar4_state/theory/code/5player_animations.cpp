#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


// Напишем класс, для простого создания анимации в библиотеке SFML
// И используем его для создания анимаций

class Animation
{
private:
    sf::IntRect m_textureRect;
    int m_numberOfFrames;
    float m_animationSpeed;
    float m_time;

public:
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


int main() 
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Player states");
    window.setFramerateLimit(60);

    // Создаём и открываем текстуру для героя игры (hero.png)
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("./hero.png")) 
    {
        std::cout << "Can't load image ./hero.png" << std::endl;
        exit(1);
    }

    // Создаём и открываем текстуру для взрыва (explosion.png)
    sf::Texture explosion_texture;
    if (!explosion_texture.loadFromFile("./explosion.png")) 
    {
        std::cout << "Can't load image ./explosion.png" << std::endl;
        exit(1);
    }

    // Создаём соответствующие спрайты
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(4, 4);

    sf::Sprite explosionSprite;
    explosionSprite.setTexture(explosion_texture);
    explosionSprite.setScale(2, 2);


    // Создаём анимации
    // Координаты на текстуре и количество кадров задаём вручную
    // в соответствии с файлами hero.png и explosion.png
    Animation animationRunning({0, 64, 21, 34}, 8, 12);
    Animation animationHooked({0, 118, 20, 50}, 6, 12);
    Animation animationIdle({0, 0, 19, 34}, 12, 12);
    Animation animationExplode({0, 0, 96, 96}, 12, 10);

    float m_time = 0;
    float dt = 1.0f / 60;
    while (window.isOpen()) 
    {
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
                window.close();

        }
        window.clear(sf::Color::Black);
        
        animationRunning.update(dt);
        animationIdle.update(dt);
        animationHooked.update(dt);
        animationExplode.update(dt);
        
        playerSprite.setPosition({450, 300});
        animationRunning.setSprite(playerSprite, true);
        window.draw(playerSprite);

        playerSprite.setPosition({200, 100});
        animationRunning.setSprite(playerSprite, false);
        window.draw(playerSprite);

        playerSprite.setPosition({100, 300});
        animationIdle.setSprite(playerSprite, true);
        window.draw(playerSprite);

        playerSprite.setPosition({200, 300});
        animationIdle.setSprite(playerSprite, false);
        window.draw(playerSprite);

        playerSprite.setPosition({100, 500});
        animationHooked.setSprite(playerSprite, true);
        window.draw(playerSprite);

        playerSprite.setPosition({200, 500});
        animationHooked.setSprite(playerSprite, false);
        window.draw(playerSprite);

        explosionSprite.setPosition({400, 300});
        animationExplode.setSprite(explosionSprite, true);
        window.draw(explosionSprite);

        window.display();
        m_time += dt;
    }

    return EXIT_SUCCESS;
}


/*
    Задание:
    Найти спрайтовую анимацию и нарисовать её.
    Можно использовать анимацию из папки animation или просто самим найти в интернете
*/