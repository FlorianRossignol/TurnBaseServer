

#include <naval_battle_client.h>
#include "engine.h"


int main()
{
    navalbattle::NavalBattleClient navalclient;
    navalbattle::NavalBattleView view(navalclient);
    Engine engine;
    engine.AddSystem(&navalclient);
    engine.AddDrawImGuiSystem(&view);
    engine.Run();
    //view.DrawSfml();
    return 0;
}

