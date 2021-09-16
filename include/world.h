#pragma once
#include <iostream>
#include <array>

	class World
	{

	public:
		World();
		int Draw();
		void PlaceBoat();
		void ViewMap();
		bool CheckImpact();
	private:
		std::array<std::array<char,9>,9> map{};
	};