

#include <naval_battle_client.h>
#include "engine.h"
#include "world.h"

int main()
{
    navalbattle::NavalBattleClient navalclient;
    navalbattle::NavalBattleView view(navalclient);
    view.DrawSfml();
    Engine engine;
    engine.AddSystem(&navalclient);
    //engine.AddDrawImGuiSystem(&view);
    engine.Run();
    return 0;
}

