

#include "echo_client.h"
#include "engine.h"
#include "world.h"

int main()
{
    echo::EchoClient client;
    Engine engine;
    engine.AddSystem(&client);
    engine.AddDrawImGuiSystem(&client);
    engine.Run();
    World world;
    world.Draw();
    return 0;
}

