#include "world.h"
#include <iostream>
#include <echo_client.h>
#include <boat.h>
#include <SFML/Graphics.hpp>

World::World::World()
{
	map = map;
}

int World::Draw()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Naval battle");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		};
		
		window.display();
	}
	return EXIT_SUCCESS;
}

void World::World::PlaceBoat()
{
	
}

void World::World::ViewMap()
{
		
}

bool World::CheckImpact()
{
	return false;
}

