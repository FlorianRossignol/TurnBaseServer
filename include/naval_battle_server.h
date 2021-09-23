#pragma once

#include <iostream>
#include <echo_settings.h>
#include <array>
#include <SFML/Network.hpp>
#include <naval_battle_packet.h>

namespace navalbattle 
{
	class NavalBattleServer
	{
	public:
		int Run();
		int GetNextSocket();
	private:
		NavalBattlePhase phase_ = NavalBattlePhase::CONNECTION;
		std::array<sf::TcpSocket, maxClientNmb > sockets_;
		sf::SocketSelector selector_;
		sf::TcpListener listener_;
		void ReceivedPacket();
		void ManageMovePacket(const MovePacket& movepacket);
		void UpdateConnectionPhase();
		void StartNewGame();
	};

}