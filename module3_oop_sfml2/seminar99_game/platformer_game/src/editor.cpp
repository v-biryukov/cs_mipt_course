#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "tileworld.h"

int main(int argc, char** argv) 
{
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Platformer");
	window.setFramerateLimit(60);

	float time = 0;
	float dt = 1.0 / 60;

	int world_width = 40;
	int world_height = 40;

	TileWorld world(world_width, world_height, true);
	Tile current_tile = Tile::GroundTop;
	Tile current_decoration_tile = Tile::GrassCenter;
	sf::RectangleShape tile_choosing_rectangle;
	tile_choosing_rectangle.setSize({world.get_tile_world_size() * 2.2f, world.get_tile_world_size() * 1.1f});
	tile_choosing_rectangle.setPosition({0, 0});
	tile_choosing_rectangle.setFillColor(sf::Color::White);

	world.load_from_file("../savefiles/default.lvl");

	while (window.isOpen()) 
	{
		sf::Event event;
		while(window.pollEvent(event)) 
		{
			if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
			{
				window.close();
			}
			world.handle_events(window, event);
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::E)
				{
					current_tile = (Tile)((int)current_tile + 1);
				}
				if (event.key.code == sf::Keyboard::Q)
				{
					current_tile = (Tile)((int)current_tile - 1);
				}

				if (event.key.code == sf::Keyboard::C)
				{
					current_decoration_tile = (Tile)((int)current_decoration_tile + 1);
				}
				if (event.key.code == sf::Keyboard::Z)
				{
					current_decoration_tile = (Tile)((int)current_decoration_tile - 1);
				}
				if (event.key.code == sf::Keyboard::Tab)
				{
					world.switch_camera_mode();
				}
				

				if (event.key.code == sf::Keyboard::F5)
				{
					world.save_to_file("savefile.lvl");
				}
			}
		}

		sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
		sf::Vector2f world_pos = window.mapPixelToCoords(pixel_pos) / world.get_tile_world_size();
		sf::Vector2i tile_pos = {(int)world_pos.x, (int)world_pos.y};
		if (tile_pos.x < 0)            tile_pos.x = 0;
		if (tile_pos.x > world_width)  tile_pos.x = world_width;
		if (tile_pos.y < 0)            tile_pos.y = 0;
		if (tile_pos.y > world_height) tile_pos.y = world_height;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				world.set_tile(tile_pos.x, tile_pos.y, Tile::None);
			else
				world.set_tile(tile_pos.x, tile_pos.y, current_tile);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				world.set_decoration_tile(tile_pos.x, tile_pos.y, Tile::None);
			else
				world.set_decoration_tile(tile_pos.x, tile_pos.y, current_decoration_tile);
		}


		window.clear(sf::Color::Black);
		world.update(dt);
		world.draw(window);
		world.set_window_view(window);
		window.draw(tile_choosing_rectangle);
		world.draw_single_tile(window, current_tile, {0, 0});
		world.draw_single_tile(window, current_decoration_tile, {world.get_tile_world_size(), 0});
		world.set_world_view(window);
		window.display();

		time += 1.0 / 60;
	}

	return EXIT_SUCCESS;
}