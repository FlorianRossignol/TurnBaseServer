#include <boat.h>
#include <naval_battle_client.h>

namespace navalbattle {
	Boat Boat::boat()
	{
		Boat boatobj;
		boatobj.lengt = boatobj.lengt;
		boatobj.position = boatobj.position;
		return boatobj;
	}

	void Boat::Littleboat()
	{
		Boat littleboat;
		littleboat.lengt = 1;
		BoatPos::vertical;
		littleboat.position.x = rand() % 325;
		littleboat.position.y = rand() % 325;
	}

	void Boat::Mediumboat()
	{
		Boat mediumboat;
		mediumboat.lengt = 2;
		BoatPos::vertical;
		mediumboat.position.x = rand() % 325;
		mediumboat.position.y = rand() % 325;
	}

	void Boat::Hightboat()
	{
		Boat hightboat;
		hightboat.lengt = 3;
		hightboat.position.x = rand() % 325;
		hightboat.position.y = rand() % 325;
		BoatPos::horizontlal;
	}

	void Boat::CheckIntersect()
	{
		Boat boat;
		NavalBattleClient client;
			if (boat.position.x && boat.position.y == boat.position.x && boat.position.y)
			{
				std::cerr << "[Error]Cant load position";
				while (boat.position.x && boat.position.y == boat.position.x && boat.position.y)
				{
					client.PlaceBoat();
				}
			}
	}
}
