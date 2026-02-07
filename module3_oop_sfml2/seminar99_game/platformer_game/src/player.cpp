#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.h"
#include "player_states.h"
#include "tiles.h"




void Player::set_state(PlayerState* new_state)
{
	delete state;
	state = new_state;
}

Player::Player(sf::Vector2f position)
{
	if (!texture.loadFromFile("../textures/hero.png"))
	{
		std::cout << "Can't load image ./hero.png for Player class" << std::endl;
		exit(1);
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);

	scale_factor = 3;
	sprite.setScale(scale_factor, scale_factor);
	state = new Idle(this);
}

sf::Vector2f Player::get_center() const
{
	return {sprite.getPosition().x + state->get_size().x * scale_factor / 2,
			sprite.getPosition().y + state->get_size().y * scale_factor / 2};
}

void Player::update(float dt)
{
	state->update(this, dt);
	sprite.move(velocity * dt);
}

void Player::draw(sf::RenderWindow& window)
{
	sf::FloatRect player_rect = {sprite.getPosition().x, sprite.getPosition().y, 
							     state->get_size().x * scale_factor, state->get_size().y * scale_factor};

	sf::RectangleShape test({player_rect.width, player_rect.height});
	test.setPosition({player_rect.left, player_rect.top});
	test.setFillColor(sf::Color(0, 255, 0, 150));
	state->set_sprite(sprite, is_faced_right);
	window.draw(sprite);
}

void Player::jump()
{
	sprite.move({0, -10});
	velocity.y = -jumping_velocity;
	state = new Falling(this);
}

void Player::handle_events(const sf::Event& event) 
{
	state->handle_events(this, event);
}

bool Player::handle_collision(const sf::FloatRect& rect, bool is_hookable)
{
	sf::FloatRect player_rect = {sprite.getPosition().x, sprite.getPosition().y, 
							     state->get_size().x * scale_factor, state->get_size().y * scale_factor};
	float overlapx1 = player_rect.left + player_rect.width - rect.left;
	float overlapx2 = rect.left + rect.width - player_rect.left;
	float overlapy1 = player_rect.top + player_rect.height - rect.top;
	float overlapy2 = rect.top + rect.height - player_rect.top;

	if (overlapx1 > 0 && overlapx2 > 0 && overlapy1 > 0 && overlapy2 > 0)
	{
		int min_overlap_direction = 0;
		float min_ovelap = overlapx1;
		if (overlapx2 < min_ovelap) {min_overlap_direction = 1; min_ovelap = overlapx2;}
		if (overlapy1 < min_ovelap) {min_overlap_direction = 2; min_ovelap = overlapy1;}
		if (overlapy2 < min_ovelap) {min_overlap_direction = 3; min_ovelap = overlapy2;}

		switch (min_overlap_direction)
		{
			case 0:
				sprite.move({-overlapx1, 0});
				velocity.x = 0;
				if (is_hookable && velocity.y > 0 && player_rect.top < rect.top + Hooked::max_hook_offset 
								   				  && player_rect.top > rect.top - Hooked::max_hook_offset)
				{
					state->hook(this, {rect.left - player_rect.width, rect.top - Hooked::hook_displacement});
					is_faced_right = true;
				}
				break;
			case 1:
				sprite.move({overlapx2, 0});
				velocity.x = 0;
				if (is_hookable && velocity.y > 0 && player_rect.top < rect.top + Hooked::max_hook_offset 
								   				  && player_rect.top > rect.top - Hooked::max_hook_offset)
				{
					state->hook(this, {rect.left + rect.width, rect.top - Hooked::hook_displacement});
					is_faced_right = false;
				}
				break;
			case 2:
				sprite.move({0, -overlapy1});
				velocity.y = 0;
				state->hit_ground(this);
				break;
			case 3:
				sprite.move({0, overlapy2});
				if (velocity.y < 0)
					velocity.y = 0;
				break;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Player::handle_all_collisions(sf::Vector2i tile_counts, sf::Vector2f tile_sizes, const std::vector<Tile>& tilemap)
{
	bool is_colided = false;
	sf::Vector2i player_tile_coordinates_topleft;
	player_tile_coordinates_topleft.x = (int)sprite.getPosition().x / tile_sizes.x;
	player_tile_coordinates_topleft.y = (int)sprite.getPosition().y / tile_sizes.y;

	sf::Vector2i player_tile_coordinates_bottomright;
	player_tile_coordinates_bottomright.x = (int)(sprite.getPosition().x + state->get_size().x * scale_factor) / tile_sizes.x;
	player_tile_coordinates_bottomright.y = (int)(sprite.getPosition().y + state->get_size().y * scale_factor) / tile_sizes.y;

	for (int i = player_tile_coordinates_topleft.x; i <= player_tile_coordinates_bottomright.x; i++)
	{
		for (int j = player_tile_coordinates_topleft.y; j <= player_tile_coordinates_bottomright.y; j++)
		{
			if (tilemap[i + tile_counts.x * j] != Tile::None)
			{
				bool is_hookable = false;
				if (j != 0 && tilemap[i + tile_counts.x * (j - 1)] == Tile::None)
					is_hookable = true;
				handle_collision({tile_sizes.x * i, tile_sizes.y * j, tile_sizes.x, tile_sizes.y}, is_hookable);
				is_colided = true;
			}
		}
		
	}

	if (!is_colided)
	{
		state->start_falling(this);
	}
}


Player::~Player()
{
	delete state;
}