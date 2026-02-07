#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "animation.hpp"
#include "player.hpp"

class Player;

class PlayerState
{
public:
    PlayerState();
    
    virtual void update(Player* player, float dt) = 0;
    virtual void handleEvents(Player* player, const sf::Event& event) = 0;
    virtual void hook(Player* player) = 0;
    virtual void startFalling(Player* player) = 0;
    virtual void hitGround(Player* player) = 0;
    virtual ~PlayerState();

    void updateSprite(sf::Sprite& sprite, bool isFacedRight, float scaleFactor);

protected:
    Animation mAnimation;

    static constexpr float kJumpingVelocity = 1500;
    void jump(Player* player);
};


class Idle : public PlayerState
{
public:
    Idle(Player* player);
    
    void update(Player* player, float dt);
    void handleEvents(Player* player, const sf::Event& event);
    void hook(Player* player);
    void startFalling(Player* player);
    void hitGround(Player* player);

private:
};


class Running : public PlayerState
{
public:
    Running(Player* player);
    void update(Player* player, float dt);
    void handleEvents(Player* player, const sf::Event& event);
    void hook(Player* player);
    void startFalling(Player* player);
    void hitGround(Player* player);

private:
    float mRunningSpeed;
};


class Sliding : public PlayerState
{

public:

    Sliding(Player* player);
    void update(Player* player, float dt);
    void handleEvents(Player* player, const sf::Event& event);
    void hook(Player* player);
    void startFalling(Player* player);
    void hitGround(Player* player);

private:

    float mCurrentTime;
    static constexpr float kSlidingTime = 0.50;
    static constexpr float kSlidingVelocity = 2000;
    static constexpr float kVelocityDecay = 0.99;
};


class Falling : public PlayerState
{
public:
    Falling(Player* player);
    void update(Player* player, float dt);
    void handleEvents(Player* player, const sf::Event& event);
    void hook(Player* player);
    void startFalling(Player* player);
    void hitGround(Player* player);

private:

    static constexpr float kHorizontalVelocity = 800;
};



class Hooked : public PlayerState
{
public:

    static constexpr float kMaxHookOffset = 15;

    Hooked(Player* player);
    void update(Player* player, float dt);
    void handleEvents(Player* player, const sf::Event& event);
    void hook(Player* player);
    void startFalling(Player* player);
    void hitGround(Player* player);
};