#pragma once
#include <iostream>
#include <array>


namespace world
{
	class world
	{
	public:
		void PlaceBoat();
		void ViewMap();
	private:
		std::array<char, 32> map1;
		std::array<char, 16> map2;
	};
}