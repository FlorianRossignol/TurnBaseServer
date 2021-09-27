#pragma once 
#include <iostream>
#include <vector>
#include <imgui-SFML.h>

namespace navalbattle {
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
		int x, y;
		int lengt = lengt;
		sf::Vector2i position = position;
	};
}