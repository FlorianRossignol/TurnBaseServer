#pragma once 
#include <iostream>
#include <vector>
#include <imgui-SFML.h>

class Boat
{
	enum BoatPos
	{
		horizontlal,
		vertical
	};

public:
	void Littleboat();
	void Mediumboat();
	void Hightboat();
	void CheckIntersect();
	Boat boat();
private:
	int lengt = lengt;
	sf::Vector2i position = position;
};