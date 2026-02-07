#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "animation.h"
#include "player.h"
#include "player_states.h"

using namespace std;

PlayerState::PlayerState() {};
void PlayerState::handle_events(Player* player, const sf::Event& event)
{
}
void PlayerState::update(Player* player, float dt)
{
	animation.update(dt);
}

sf::Vector2i PlayerState::get_size()
{
	return animation.get_size();
}
void PlayerState::set_sprite(sf::Sprite& sprite, bool is_faced_right)
{
	animation.set_sprite(sprite, is_faced_right);
}
PlayerState::~PlayerState() {};




Idle::Idle(Player* player) : PlayerState()
{
	player->velocity = {0, 0};
	animation = Animation({4, 0, 19, 34}, 12, 12);
	cout << "Creating Idle state" << endl;
}

void Idle::attacked(Player* player)
{
}

void Idle::hook(Player* player, sf::Vector2f position) {}
void Idle::update(Player* player, float dt)
{
	animation.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player->set_state(new Running(player));
		return;
	}
}

void Idle::handle_events(Player* player, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
		{
			player->set_state(new Running(player));
		}
		else if (event.key.code == sf::Keyboard::Space)
		{
			player->jump();
		}
	}
}

void Idle::start_falling(Player* player)
{
	player->set_state(new Falling(player));
}
void Idle::hit_ground(Player* player)
{
}


float Running::running_speed = 600;

Running::Running(Player* player) : PlayerState()
{
	animation = Animation({0, 64, 21, 34}, 8, 12);
	cout << "Creating Running state" << endl;
}

void Running::hook(Player* player, sf::Vector2f position)
{
}

void Running::attacked(Player* player)
{
}

void Running::update(Player* player, float dt)
{
	animation.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player->velocity.x = -running_speed;
		player->is_faced_right = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player->velocity.x = running_speed;
		player->is_faced_right = true;
	}
}
void Running::handle_events(Player* player, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			player->jump();
			return;
		}
		if (event.key.code == sf::Keyboard::LShift)
		{
			player->set_state(new Sliding(player));
		}

	}
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Left && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->set_state(new Idle(player));
			player->velocity.x = 0;
		}
		if (event.key.code == sf::Keyboard::Right && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->set_state(new Idle(player));
			player->velocity.x = 0;
		}
	}
}

void Running::start_falling(Player* player)
{
	player->set_state(new Falling(player));
}

void Running::hit_ground(Player* player)
{
}


float Sliding::sliding_time = 1.2;
float Sliding::velocity_multiplier = 2.0;
float Sliding::velocity_decay = 0.99;

Sliding::Sliding(Player* player) : PlayerState()
{
	player->velocity.x *= velocity_multiplier;
	animation = Animation({0, 268, 40, 24}, 1, 12);
	player->sprite.move({0, 12});
	cout << "Creating Sliding state" << endl;
	current_time = sliding_time;	
}

void Sliding::hook(Player* player, sf::Vector2f position)
{
}

void Sliding::attacked(Player* player)
{
}

void Sliding::update(Player* player, float dt)
{
	player->velocity.y += 60;
	animation.update(dt);
	player->velocity.x *= velocity_decay;
	current_time -= dt;
	if (current_time < 0 || fabs(player->velocity.x) < 0.1)
	{
		player->sprite.move({0, -12});
		player->set_state(new Idle(player));
		return;
	}
}
void Sliding::handle_events(Player* player, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			player->jump();
		}

		if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
		{
			player->set_state(new Running(player));
		}
	}
}

void Sliding::start_falling(Player* player)
{
}

void Sliding::hit_ground(Player* player)
{
}


float Falling::max_velocity_x = 600;
float Falling::max_velocity_y = 2000;
float Falling::acceleration_x = 3200;

Falling::Falling(Player* player) : PlayerState()
{
	animation = Animation({0, 192, 20, 34}, 2, 12);
	initial_velocity_x = player->velocity.x;
	cout << "Creating Falling state" << endl;
}

void Falling::hook(Player* player, sf::Vector2f position)
{
	player->sprite.setPosition(position);
	player->set_state(new Hooked(player));
}

void Falling::attacked(Player* player)
{
}

void Falling::update(Player* player, float dt)
{
	player->velocity.y += 60;
	animation.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player->velocity.x += -acceleration_x * dt;
		player->is_faced_right = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player->velocity.x += +acceleration_x * dt;
		player->is_faced_right = true;
	}
	if (player->velocity.x < - max_velocity_x)
			player->velocity.x = -max_velocity_x;
	if (player->velocity.x > max_velocity_x)
			player->velocity.x = +max_velocity_x;

	if (player->velocity.y > max_velocity_y)
		player->velocity.y = max_velocity_y;
}
void Falling::handle_events(Player* player, const sf::Event& event)
{
}

void Falling::start_falling(Player* player)
{
}

void Falling::hit_ground(Player* player)
{
	player->set_state(new Idle(player));
}



float Hooked::max_hook_offset = 20;
float Hooked::hook_displacement = 24;

Hooked::Hooked(Player* player) : PlayerState()
{
	animation = Animation({2, 124, 20, 38}, 6, 12, Animation::AnimationType::OneIteration);
	cout << "Creating Hooked state" << endl;
}

void Hooked::hook(Player* player, sf::Vector2f position)
{
}

void Hooked::attacked(Player* player)
{
}

void Hooked::update(Player* player, float dt)
{
	player->velocity = {0, 0};
	animation.update(dt);
}
void Hooked::handle_events(Player* player, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			player->jump();
			return;
		}
		if (event.key.code == sf::Keyboard::Down)
		{
			player->set_state(new Falling(player));
			return;
		}
	}
}

void Hooked::start_falling(Player* player)
{
}

void Hooked::hit_ground(Player* player)
{
	player->set_state(new Idle(player));
}
