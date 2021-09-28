#include <naval_battle_server.h>
#include <echo_server.h>
#include <naval_battle_packet.h>
#include <SFML/Network/TcpSocket.hpp>
#include <random>

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
		switch (phase_)
		{
		case navalbattle::NavalBattlePhase::CONNECTION:
			ReceivedPacket();
			UpdateConnectionPhase();
			break;
		case navalbattle::NavalBattlePhase::GAME:
			ReceivedPacket();
			break;
		case navalbattle::NavalBattlePhase::END:
			return EXIT_SUCCESS;
			break;
		default:;
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

void NavalBattleServer::ReceivedPacket()
{
	if (selector_.wait(sf::milliseconds(20)))
	{
		for (auto& socket : sockets_)
		{
			if (selector_.isReady(socket))
			{
				sf::Packet receivedPacket;
				sf::Socket::Status receivedStatus{};
				do
				{
					receivedStatus = socket.receive(receivedPacket);

				} while (receivedStatus == sf::Socket::Partial);
				Packet statusPacket;
				receivedPacket >> statusPacket;
				switch (static_cast<PacketType>(statusPacket.packetype))
				{
				case PacketType::MOVE:
				{
					MovePacket movePacket;
					receivedPacket >> movePacket;
					ManageMovePacket(movePacket);
					BoatPlacePacket boatPlacePacket;
					receivedPacket >> boatPlacePacket;
					break;
				}
				
				}
			}
		}
	}
}

void NavalBattleServer::ManageMovePacket(const MovePacket& movepacket)
{
	
}

void NavalBattleServer::UpdateConnectionPhase()
{
	const auto nextIndex = GetNextSocket();

	if (nextIndex != -1)
	{
		auto& newSocket = sockets_[nextIndex];
		if (listener_.accept(newSocket) == sf::Socket::Done)
		{
			std::cout << "New connection from " << ":" << newSocket.getRemoteAddress().toString() << "\n";
			newSocket.setBlocking(false);
			selector_.add(newSocket);
			if (nextIndex == 1)
			{
				StartNewGame();
			}
			else 
			{
				std::cout << "waiting for 2nd player !";
			}
		}
	}
}

void NavalBattleServer::StartNewGame()
{
	phase_ = NavalBattlePhase::GAME;

	std::cout << "Two player connected !\n";

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distrib(0, 1);
	int dice_roll = distrib(generator);

	for (unsigned char i = 0; i < sockets_.size(); i++)
	{
		GameInitPacket gameInitPacket{};
		gameInitPacket.packetype = PacketType::GAME_INIT; 
		gameInitPacket.playerNumber = i != dice_roll;
		sf::Packet sentPacket;
		sentPacket << gameInitPacket;
		sf::Socket::Status sentStatus;
		do
		{
			sentStatus = sockets_[i].send(sentPacket);

		} while (sentStatus == sf::Socket::Partial);
	}
}

}
