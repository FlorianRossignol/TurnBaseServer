#include <naval_battle_server.h>
#include <echo_server.h>

namespace navalbattle {
	
int navalbattle::NavalBattleServer::Run()
{
	listener_.setBlocking(false);
	if (listener_.listen(serverPortNumber) != sf::Socket::Done)
	{
		std::cerr << "[Error] cant bind port: " << serverPortNumber << '\n';
	}
	std::cout << "[Sucess] server bound to port " << serverPortNumber << '\n';
	while (true)
	{
		const auto nextIndex = GetNextSocket();

		if (nextIndex != -1)
		{
			auto& newSocket = sockets_[nextIndex];
			if (listener_.accept(newSocket) == sf::Socket::Done)
			{
				newSocket.setBlocking(false);
				selector_.add(newSocket);
			}
		}
	}
	return SERVER_FINISH_OK;
}

int NavalBattleServer::GetNextSocket()
{
	for (int i = 0; i < maxClientNmb; i++)
	{
		if (sockets_[i].getLocalPort() == 0)
		{
			return i;
		}
	}
	return -1;
}

}
