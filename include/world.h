#pragma once
#include <iostream>
#include <array>

	class world
	{
	public:
		world();
		void PlaceBoat();
		void ViewMap();
	private:
		std::string map1 =
			"#########"
			"#12345678"
			"Axxxxxxxx"
			"Bxxxxxxxx"
			"Cxxxxxxxx"
			"Dxxxxxxxx"
			"Exxxxxxxx"
			"Fxxxxxxxx"
			"Gxxxxxxxx"
			"Hxxxxxxxx"
			"#########";
		std::string map2 =
			"#########"
			"#12345678"
			"Axxxxxxxx"
			"Bxxxxxxxx"
			"Cxxxxxxxx"
			"Dxxxxxxxx"
			"Exxxxxxxx"
			"Fxxxxxxxx"
			"Gxxxxxxxx"
			"Hxxxxxxxx"
			"#########";
	};