#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	enum class AnimationType {Repeat, OneIteration};
private:
	sf::IntRect texture_rect;

	int number_of_frames;
	float animation_speed;

	float time;

	
	AnimationType type;

public:

	Animation() {}

	Animation(sf::IntRect texture_rect, int number_of_frames, float animation_speed, AnimationType type = AnimationType::Repeat) :
			  number_of_frames(number_of_frames), animation_speed(animation_speed), texture_rect(texture_rect),
			  type(type), time(0)
	{
	}

	sf::Vector2i get_size()
	{
		sf::Vector2i result = {texture_rect.width, texture_rect.height};
		return result;
	}

	void update(float dt)
	{
		time += dt;
		if (time > number_of_frames / animation_speed)
		{
			if (type == AnimationType::Repeat)
				time -= number_of_frames / animation_speed;
			else if (type == AnimationType::OneIteration)
				time = (number_of_frames - 0.5) / animation_speed;
		}
	}

	void set_sprite(sf::Sprite& sprite, bool is_faced_right)
	{
		int current_frame = (int)(animation_speed * time) % number_of_frames;
		if (is_faced_right)
		{
			texture_rect.left = current_frame * texture_rect.width;
			sprite.setTextureRect(texture_rect);
		}
		else
		{
			texture_rect.left = (current_frame + 1) * texture_rect.width;
			texture_rect.width *= -1;
			sprite.setTextureRect(texture_rect);
			texture_rect.width *= -1;
		}
	}
};