#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "player.h"

class Player;

class PlayerState
{
protected:
	Animation animation;
public:
	PlayerState();

	sf::Vector2i get_size();
	void set_sprite(sf::Sprite& sprite, bool is_faced_right);

	virtual void handle_events(Player* player, const sf::Event& event);
	virtual void update(Player* player, float dt);

	virtual void hook(Player* player, sf::Vector2f position) = 0;
	virtual void attacked(Player* player) = 0;
	virtual void start_falling(Player* player) = 0;
	virtual void hit_ground(Player* player) = 0;
	virtual ~PlayerState();
};

class Idle : public PlayerState
{
public:
	Idle(Player* player);
	
	void update(Player* player, float dt);
	void handle_events(Player* player, const sf::Event& event);
	void hook(Player* player, sf::Vector2f position);
	void attacked(Player* player);
	void start_falling(Player* player);
	void hit_ground(Player* player);
};

class Running : public PlayerState
{
private:
	static float running_speed;
public:
	Running(Player* player);
	void update(Player* player, float dt);
	void handle_events(Player* player, const sf::Event& event);
	void hook(Player* player, sf::Vector2f position);
	void attacked(Player* player);
	void start_falling(Player* player);
	void hit_ground(Player* player);
};

class Sliding : public PlayerState
{
private:
	static float sliding_time;
	float current_time;

	static float velocity_multiplier;
	static float velocity_decay;
public:
	Sliding(Player* player);
	void update(Player* player, float dt);
	void handle_events(Player* player, const sf::Event& event);
	void hook(Player* player, sf::Vector2f position);
	void attacked(Player* player);
	void start_falling(Player* player);
	void hit_ground(Player* player);
};

class Falling : public PlayerState
{
	float initial_velocity_x;
	static float acceleration_x;
	static float max_velocity_x;
	static float max_velocity_y;
public:
	Falling(Player* player);
	void update(Player* player, float dt);
	void handle_events(Player* player, const sf::Event& event);
	void hook(Player* player, sf::Vector2f position);
	void attacked(Player* player);
	void start_falling(Player* player);
	void hit_ground(Player* player);
};

class Hooked : public PlayerState
{
public:

	static float max_hook_offset;
	static float hook_displacement;

	Hooked(Player* player);
	void update(Player* player, float dt);
	void handle_events(Player* player, const sf::Event& event);
	void hook(Player* player, sf::Vector2f position);
	void attacked(Player* player);
	void start_falling(Player* player);
	void hit_ground(Player* player);
};