#pragma once

#include <iostream>
#include <echo_settings.h>
#include <array>
#include <SFML/Network.hpp>

namespace navalbattle 
{
	class NavalBattleServer
	{
	public:
		int Run();
		int GetNextSocket();
	private:
		std::array<sf::TcpSocket, maxClientNmb > sockets_;
		sf::SocketSelector selector_;
		sf::TcpListener listener_;
	};

}