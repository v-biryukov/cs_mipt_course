#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player_states.hpp"

class PlayerState;

class Player
{
public:

    Player(sf::Vector2f position);

    sf::Vector2f getCenter() const;
    void applyVelocity(sf::Vector2f velocity);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void handleEvents(const sf::Event& event);
    bool handleCollision(const sf::FloatRect& rect);
    void handleAllCollisions(const std::vector<sf::FloatRect>& blocks);

    ~Player();

    friend class PlayerState;
    friend class Idle;
    friend class Running;
    friend class Falling;
    friend class Sliding;
    friend class Hooked;


private:

    sf::Vector2f    mPosition           {0, 0};
    sf::Vector2f    mVelocity           {0, 0};

    bool            mIsColliding        {false};     
    sf::FloatRect   mCollisionRect      {-40, -60, 80, 120};

    PlayerState*    mpState             {nullptr};
    sf::Texture     mTexture            {};
    sf::Sprite      mSprite             {}; 
    float           mScaleFactor        {1};
    bool            mIsFacedRight       {true};
    
    
    void setState(PlayerState* pNewState);
};