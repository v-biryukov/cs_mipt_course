#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "tileworld.h"

int main () 
{
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Platformer");
	window.setFramerateLimit(60);

	float time = 0;
	float dt = 1.0 / 60;

	TileWorld world(40, 40, false);

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
		}
		window.clear(sf::Color::Black);
		world.update(dt);
		world.draw(window);

		window.display();

		time += 1.0 / 60;
	}

	return EXIT_SUCCESS;
}